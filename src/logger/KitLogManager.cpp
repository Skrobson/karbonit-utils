#include "KitLogManager.hpp"
#include <spdlog/async.h>

using namespace kit::logger;

LogManager::LogManager()
{
    spdlog::init_thread_pool(8192, 1);
}

void LogManager::initDefaultLogger()
{
    std::vector<spdlog::sink_ptr> tmpV;
    std::transform(sinks.begin(), sinks.end(), std::back_inserter(tmpV), [](auto &p){return p.second;});

    defaultLogger = std::make_shared<spdlog::async_logger>("DEFAULT", std::begin(tmpV), std::end(tmpV), spdlog::thread_pool());
    //defaultLogger->flush_on(spdlog::level::err); 

    spdlog::set_default_logger(defaultLogger);
    initialized = true;
}

void LogManager::configureDefaultConsoleSink()
{
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
    sinks.insert_or_assign(consoleSinkName.data(), console_sink);
    console_sink->set_level(log_level::info);
}

void LogManager::configureDefaultFileSink(std::string_view logFilename)
{
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt> (logFilename.data(), 1024*1024, 5, false);
    sinks.insert_or_assign(fileSinkName.data(), file_sink);
    file_sink->set_level(log_level::info);
}

// bool kit::logger::LogManager::addCustomSink(std::string sinkName, spdlog::sink_ptr)
// {
//     if(initialized)
//         return false;

//     return false;
// }

void LogManager::setSinkLevel(std::string_view sinkName, log_level l)
{
    if(auto s = sinks.find(sinkName.data()); s != sinks.end())
        s->second->set_level(l);
}

std::shared_ptr<spdlog::async_logger> kit::logger::LogManager::getLogger(std::string_view loggerName)
{
    std::shared_ptr<spdlog::async_logger> retLog;

    if(auto l = loggers.find(loggerName.data()); l != loggers.end())
        retLog = l->second;
    else
    {
        std::vector<spdlog::sink_ptr> tmpV;
        std::transform(sinks.begin(), sinks.end(), std::back_inserter(tmpV), [](auto &p){return p.second;});

        retLog = std::make_shared<spdlog::async_logger>(loggerName.data(), std::begin(tmpV), std::end(tmpV), spdlog::thread_pool());
    }
    
    return retLog;
}

#include "Logger.hpp"
#include <spdlog/async.h>

using namespace skr::logger;

LogManager::LogManager()
{
    spdlog::init_thread_pool(8192, 1);
}

void LogManager::init()
{
    std::vector<spdlog::sink_ptr> tmpV;
    std::transform(sinks.begin(), sinks.end(), std::back_inserter(tmpV), [](auto &p){return p.second;});

    defaultLogger = std::make_shared<spdlog::async_logger>("DEFAULT", std::begin(tmpV), std::end(tmpV), spdlog::thread_pool());

    spdlog::set_default_logger(defaultLogger);
}

void LogManager::configureDefaultConsoleSink()
{
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
    sinks.insert_or_assign(Sink::CONSOLE, console_sink);
}

void LogManager::configureDefaultFileSink(std::string_view logFilename)
{
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt> (logFilename.data(), 1024*1024, 5, false);
    sinks.insert_or_assign(Sink::FILE, file_sink);
}

void LogManager::setSinkLevel(LogManager::Sink sink, log_level l)
{
    if(auto s = sinks.find(sink); s != sinks.end())
        s->second->set_level(l);
}
#include "KitLogger/spdlogEngine/spdlogEngine.hpp"
#include <spdlog/async_logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async.h>

using namespace kit::logger;
using namespace kit::logger::detail;

spdlogEngine::spdlogEngine()
{
    sinkLevel = spdlog::level::level_enum::info;
    spdlog::init_thread_pool(8192, 1);
}

void spdlogEngine::setSinkLevel(std::string_view sinkName, LogLevel l)
{
    const std::lock_guard<std::mutex> lock(sinksMtx);
    auto sink = sinksMap.find(sinkName.data());
    if (sink != sinksMap.end())
    {
        sink->second->set_level(static_cast<spdlog::level::level_enum>(l));
    }
}

void spdlogEngine::setLoggerLevel(std::string_view loggerName, LogLevel l)
{
    const std::lock_guard<std::recursive_mutex> lock(loggersMtx);
    auto logger = loggers.find(loggerName.data());
    if (logger != loggers.end())
    {
        logger->second->set_level(static_cast<spdlog::level::level_enum>(l));
    }
}

void spdlogEngine::configureDefaultFileSink(std::string_view logFilename)
{
    const std::lock_guard<std::mutex> lock(sinksMtx);
    auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logFilename.data(), 1024 * 100 , 10, true);
    fileSink->set_level(static_cast<spdlog::level::level_enum>(sinkLevel));
    sinksMap[std::string(fileSinkName)] = fileSink;
    sinks.push_back(fileSink);
}

void spdlogEngine::configureDefaultConsoleSink()
{
    const std::lock_guard<std::mutex> lock(sinksMtx);
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    consoleSink->set_level(static_cast<spdlog::level::level_enum>(sinkLevel));
    sinksMap[std::string(consoleSinkName)] = consoleSink;
    sinks.push_back(consoleSink);
}

void spdlogEngine::init()
{
    const std::lock_guard<std::mutex> sinksLock(sinksMtx);
    const std::lock_guard<std::recursive_mutex> loggersLock(loggersMtx);

    if (!initialized)
    {
        defaultLogger = std::make_shared<spdlog::async_logger>("DEFAULT", std::begin(sinks), std::end(sinks), spdlog::thread_pool());
        defaultLogger->set_level(static_cast<spdlog::level::level_enum>(sinkLevel));
        loggers["DEFAULT"] = defaultLogger;
        defaultLogger->set_pattern("%^>>[%D-%H:%M:%S.%f][%n][%l]%$ %v");
        initialized = true;
    }
}
spdlogEngine::~spdlogEngine()
{
    const std::lock_guard<std::recursive_mutex> lock(loggersMtx);
    for (auto &logger : loggers)
    {
        logger.second->flush();
    }
    spdlog::shutdown();
}

void spdlogEngine::createLogger(std::string_view name)
{
    const std::lock_guard<std::recursive_mutex> lock(loggersMtx);
    if (loggers.find(name.data()) == loggers.end())
    {
        auto logger = defaultLogger->clone(name.data());
        logger->set_level(static_cast<spdlog::level::level_enum>(sinkLevel));
        loggers[name.data()] = logger;
    }
}

std::shared_ptr<spdlog::logger> spdlogEngine::getLogger(std::string_view name)
{
    const std::lock_guard<std::recursive_mutex> lock(loggersMtx);
    auto logger = loggers.find(name.data());
    if (logger != loggers.end())
    {
        return logger->second;
    }
    else
    {
        createLogger(name);
        return loggers[name.data()];
    }
}

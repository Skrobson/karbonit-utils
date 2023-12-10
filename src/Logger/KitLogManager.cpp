#include "KitLogger/KitLogManager.hpp"

#include <spdlog/async.h>

#include <iostream>

using namespace kit::logger;

LogManager::LogManager()
{
    spdlog::init_thread_pool(8192, 1);
}

void LogManager::initDefaultLogger()
{
    defaultLogger =
        std::make_shared<spdlog::async_logger>("DEFAULT", sinks.begin(), sinks.end(), spdlog::thread_pool());
    defaultLogger->flush_on(spdlog::level::warn);
    spdlog::initialize_logger(defaultLogger);
    spdlog::set_default_logger(defaultLogger);

    initialized = true;
}

void LogManager::configureDefaultConsoleSink()
{
    std::lock_guard<std::mutex> lock(sinksMtx);
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    sinksMap.insert_or_assign(consoleSinkName.data(), console_sink);
    sinks.emplace_back(std::move(console_sink));
}

void LogManager::configureDefaultFileSink(std::string_view logFilename)
{
    std::lock_guard<std::mutex> lock(sinksMtx);
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logFilename.data(), 1024 * 1024, 5, false);
    sinksMap.insert_or_assign(fileSinkName.data(), file_sink);
    sinks.emplace_back(std::move(file_sink));
}

void LogManager::setSinkLevel(std::string_view sinkName, LogLevel l)
{
    std::lock_guard<std::mutex> lock(sinksMtx);
    if (auto s = sinksMap.find(sinkName.data()); s != sinksMap.end())
        s->second->set_level(l);
}

void LogManager::setLoggerLevel(std::string_view loggerName, LogLevel l)
{
    getLogger(loggerName)->set_level(l);
}

std::shared_ptr<spdlog::async_logger> kit::logger::LogManager::getLogger(std::string_view loggerName)
{
    std::shared_ptr<spdlog::async_logger> logger;
    std::lock_guard<std::mutex> lock(loggersMtx);

    if (auto l = loggers.find(loggerName.data()); l != loggers.end())
        logger = l->second;
    else
    {
        std::lock_guard<std::mutex> lock(sinksMtx);

        logger = std::make_shared<spdlog::async_logger>(loggerName.data(), sinks.begin(), sinks.end(),
                                                        spdlog::thread_pool());
        loggers.insert(std::make_pair(loggerName.data(), logger));
        spdlog::initialize_logger(logger);
    }

    return logger;
}

LogManager::~LogManager()
{
    spdlog::shutdown();
    std::cout << "Endlife of logger" << std::endl;
}

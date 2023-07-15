#pragma once
#include "Singleton.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/async_logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include <vector>
#include <map>
#include <memory>

namespace kit::logger
{
    // inline void basicLogConfiguration(){

    // }
    using log_level = spdlog::level::level_enum;
    class LogManager: public kit::Singleton<LogManager>
    {
    public:

        enum SinkType
        {
            CONSOLE,
            FILE,
            MULTICAST
        };

        LogManager();

        void configureDefaultConsoleSink();
        void configureDefaultFileSink(std::string_view logFilename = "Log.txt");

        void setSinkLevel(LogManager::SinkType sink, log_level l);
        
        //should be called after configure sinks
        void init();
        //TODO: returning some kind of token
        //LogToken registerAdditionalLogger();

    private:
        std::shared_ptr<spdlog::async_logger> defaultLogger;
        std::map<LogManager::SinkType,spdlog::sink_ptr> sinks;
        
        //std::map<LogToken, spdlog::async_logger> loggersMap;
    };
}

#ifndef DONT_USE_KIT_LOG
#define KIT_LOG_T(...) spdlog::trace(__VA_ARGS__) 
#define KIT_LOG_D(...) spdlog::debug(__VA_ARGS__)
#define KIT_LOG_I(...) spdlog::info(__VA_ARGS__)
#define KIT_LOG_W(...) spdlog::warn(__VA_ARGS__)
#define KIT_LOG_E(...) spdlog::error(__VA_ARGS__)
#define KIT_LOG_C(...) spdlog::critical(__VA_ARGS__)
#endif
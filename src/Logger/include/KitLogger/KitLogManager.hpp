#pragma once
#include "Singleton.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/async_logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include <vector>
#include <map>
#include <mutex>
#include <memory>
#include <string_view>

namespace kit::logger
{
    using LogLevel = spdlog::level::level_enum;

    using namespace std::string_view_literals;



    class LogManager: public kit::Singleton<LogManager>
    {
    public:

        LogManager();

        //void log(LogLevel level, std::string_view msg);
        //void log(std::string_view channel, LogLevel level, std::string_view msg);

        void configureDefaultConsoleSink();
        void configureDefaultFileSink(std::string_view logFilename = "Log.txt");

        void setSinkLevel(std::string_view sinkName, LogLevel l);
        void setLoggerLevel(std::string_view loggerName, LogLevel l);

        //If logger dont exist, create and return
        std::shared_ptr<spdlog::async_logger> getLogger(std::string_view loggerName);

        //should be called after configure sinks
        void initDefaultLogger();
        void deinitialize();

        static constexpr std::string_view consoleSinkName = "console"sv; 
        static constexpr std::string_view fileSinkName = "file"sv;
        
        ~LogManager();
    private:
        bool initialized = false;
        
        std::mutex sinksMtx;
        std::shared_ptr<spdlog::async_logger> defaultLogger;
        std::unordered_map<std::string,spdlog::sink_ptr> sinksMap;
        std::vector<spdlog::sink_ptr> sinks;

        std::mutex loggersMtx;
        std::unordered_map<std::string,std::shared_ptr<spdlog::async_logger>> loggers;
        
        //return false if is to late for register new sinks
        //bool addCustomSink(std::string sinkName, spdlog::sink_ptr);
    };
    
    inline void signal_handler(int signal)
    {
        LogManager::getInstance().deinitialize();
    }
}
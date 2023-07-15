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
    // inline void basicLogConfiguration(){

    // }
    using log_level = spdlog::level::level_enum;

    using namespace std::string_view_literals;

    class LogManager: public kit::Singleton<LogManager>
    {
    public:

        LogManager();

        void configureDefaultConsoleSink();
        void configureDefaultFileSink(std::string_view logFilename = "Log.txt");

        //return false if is to late for register new sinks
        //bool addCustomSink(std::string sinkName, spdlog::sink_ptr);

        void setSinkLevel(std::string_view sinkName, log_level l);
        
        //If logger dont exist, creatye and return
        std::shared_ptr<spdlog::async_logger> getLogger(std::string_view loggerName);

        //should be called after configure sinks
        void initDefaultLogger();
        

        static constexpr std::string_view consoleSinkName = "console"sv; 
        static constexpr std::string_view fileSinkName = "file"sv;
    private:
        bool initialized = false;
        
        std::shared_ptr<spdlog::async_logger> defaultLogger;
        std::map<std::string,spdlog::sink_ptr> sinks;

        std::mutex loggersMtx;
        std::map<std::string,std::shared_ptr<spdlog::async_logger>> loggers;
        //std::map<LogToken, spdlog::async_logger> loggersMap;
    };
}
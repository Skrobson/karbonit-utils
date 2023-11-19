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
        template<typename... Args>
        void log(LogLevel level, fmt::format_string<Args...> fmt, Args &&...args)
        {
            spdlog::log(level, fmt, std::forward<Args>(args)...);
        }

        template<typename T>
        void log(LogLevel level, const T &msg)
        {
            spdlog::log(level, msg);
        }

        template<typename... Args>
        void log(std::string_view channel, LogLevel level, fmt::format_string<Args...> fmt, Args &&...args)
        {
            this->getLogger(channel)->log(level, fmt, std::forward<Args>(args)...);
        }

        template<typename T>
        void log(std::string_view channel, LogLevel level, const T &msg)
        {
            this->getLogger(channel)->log(level, msg);
        }

        void configureDefaultConsoleSink();
        void configureDefaultFileSink(std::string_view logFilename = "Log.txt");

        void setSinkLevel(std::string_view sinkName, LogLevel l);
        void setLoggerLevel(std::string_view loggerName, LogLevel l);

        //should be called after configure sinks
        void initDefaultLogger();

        static constexpr std::string_view consoleSinkName = "console"sv;
        static constexpr std::string_view fileSinkName = "file"sv;

        ~LogManager();
    private:
        bool initialized = false;

        //If logger dont exist, create and return
        std::shared_ptr<spdlog::async_logger> getLogger(std::string_view loggerName);

        std::mutex sinksMtx;
        std::shared_ptr<spdlog::async_logger> defaultLogger;
        std::unordered_map<std::string,spdlog::sink_ptr> sinksMap;
        std::vector<spdlog::sink_ptr> sinks;

        std::mutex loggersMtx;
        std::unordered_map<std::string,std::shared_ptr<spdlog::async_logger>> loggers;

    };
}

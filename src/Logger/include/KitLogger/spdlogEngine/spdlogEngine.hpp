/**
 * Karbonit Utils
 *
 * Author:    Bartłomiej Skrobol
 * Created:   13.01.2024
 *
 * (c) Copyright by Karbonit.
 *
 * License: MIT
 **/

#pragma once
#include "KitLogger/ILoggerEngine.hpp"

#include <spdlog/async_logger.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace kit::logger
{
    namespace detail
    {
        class spdlogEngine : public ILoggerEngine
        {
        public:
            typedef spdlog::logger LoggerType;

            spdlogEngine();

            template <typename... Args>
            void log(std::string_view channel, LogLevel level, fmt::format_string<Args...> fmt, Args &&...args);

            template <typename... Args>
            void log( LogLevel level, fmt::format_string<Args...> fmt, Args &&...args);

            template <typename T>
            void log(std::string_view channel, LogLevel level, const T &msg);

            template <typename T>
            void log(LogLevel level, const T &msg);
            // //todo add some configuration for multicast sink
            // virtual void configureMulticastSink();

            void setSinkLevel(std::string_view sinkName, LogLevel l) override;
            void setLoggerLevel(std::string_view loggerName, LogLevel l)override;


            void configureDefaultConsoleSink() override;
            void configureDefaultFileSink(std::string_view logFilename = "Log.txt") override;

            void init() override;

            static constexpr std::string_view consoleSinkName = "console"sv;
            static constexpr std::string_view fileSinkName = "file"sv;

            ~spdlogEngine();

        private:
            void createLogger(std::string_view name);
            std::shared_ptr<spdlog::logger> getLogger(std::string_view name);

            bool initialized = false;

            spdlog::level::level_enum sinkLevel;
            std::shared_ptr<spdlog::async_logger> defaultLogger;

            std::mutex sinksMtx;
            std::unordered_map<std::string, spdlog::sink_ptr> sinksMap;
            std::vector<spdlog::sink_ptr> sinks;

            std::recursive_mutex loggersMtx;
            std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> loggers;
        };

        template <typename... Args>
        void spdlogEngine::log(std::string_view channel, LogLevel level, fmt::format_string<Args...> fmt, Args &&...args)
        {
            const std::unique_lock<std::recursive_mutex> lock(loggersMtx);
            auto logger = getLogger(channel);
            logger->log(static_cast<spdlog::level::level_enum>(level), fmt, std::forward<Args>(args)...);
        }

        template <typename... Args>
        void spdlogEngine::log( LogLevel level, fmt::format_string<Args...> fmt, Args &&...args)
        {
            defaultLogger->log(static_cast<spdlog::level::level_enum>(level), fmt, std::forward<Args>(args)...);
        }

        template <typename T>
        void spdlogEngine::log(std::string_view channel, LogLevel level, const T &msg)
        {
            const std::unique_lock<std::recursive_mutex> lock(loggersMtx);
            auto logger = getLogger(channel);
            logger->log(static_cast<spdlog::level::level_enum>(level), msg);
        }

        template <typename T>
        void spdlogEngine::log(LogLevel level, const T &msg)
        {
            defaultLogger->log(static_cast<spdlog::level::level_enum>(level), msg);
        }
    }
}

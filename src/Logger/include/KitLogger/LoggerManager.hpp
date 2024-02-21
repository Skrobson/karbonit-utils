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
#include "ILoggerEngine.hpp"

#include <map>
#include <memory>
#include <mutex>
#include <string_view>
#include <sstream>
#include <vector>

namespace kit::logger
{
    namespace detail
    {
        template <detail::LogTemplateInterface L>
        class LoggerManager : public ILoggerEngine
        {
        public:
            typedef L::LoggerType  Logger;

            template <typename... Args>
            void log(std::string_view channel, LogLevel level, fmt::format_string<Args...> fmt, Args &&...args)
            {
                getInstance().log(channel, level, fmt, std::forward<Args>(args)...);
            }

            template <typename... Args>
            void log(LogLevel level, fmt::format_string<Args...> fmt, Args &&...args)
            {
                getInstance().log(level, fmt, std::forward<Args>(args)...);
            }

            template <typename T>
            void log(std::string_view channel, LogLevel level, const T &msg)
            {
                getInstance().log(channel, level, msg);
            }

            template <typename T>
            void log(LogLevel level, const T &msg)
            {
                getInstance().log(level, msg);
            }

            void setSinkLevel(std::string_view sinkName, LogLevel l) override
            {
                getInstance().setSinkLevel(sinkName, l);
            }

            void setLoggerLevel(std::string_view loggerName, LogLevel l) override
            {
                getInstance().setLoggerLevel(loggerName, l);
            }

            void configureDefaultFileSink(std::string_view logFilename = "Log.txt") override
            {
                getInstance().configureDefaultFileSink(logFilename);
            }

            void configureDefaultConsoleSink() override
            {
                getInstance().configureDefaultConsoleSink();
            }

            void init() override
            {
                getInstance().init();
            }

            // void configureMulticastSink() override
            // {
            //     getInstance()->configureMulticastSink();
            // }

        private:
            L &getInstance()
            {
                static L instance;
                return instance;
            }
        };
    } // namespace detail
} // namespace kit::logger

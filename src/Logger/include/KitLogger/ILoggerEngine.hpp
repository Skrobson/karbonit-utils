#pragma once
#include "fmt/format.h"
#include <string_view>

namespace kit::logger
{
    enum class LogLevel
    {
        TRACE = 0,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        CRITICAL,
        OFF
    };

    namespace detail
    {
        using namespace std::string_view_literals;

        template <typename T>
        concept LoggableWithMsg = requires(T t) {
            {
                t.log(std::declval<std::string_view>(), std::declval<LogLevel>(), std::declval<std::string_view>())
            }
            -> std::same_as<void>;
            {
                t.log(std::declval<LogLevel>(), std::declval<std::string>())
            }
            -> std::same_as<void>;
        };

        template <typename T>
        concept LoggableWithFormat = requires(T t) {
            {
                t.log(std::declval<std::string_view>(), std::declval<LogLevel>(), std::declval<fmt::format_string<>>(),
                      std::declval<fmt::format_args>())
            }
            -> std::same_as<void>;
            {
                t.log(std::declval<LogLevel>(), std::declval<fmt::format_string<>>(),
                      std::declval<fmt::format_args>())
            }
            -> std::same_as<void>;
        };

        template <typename T>
        concept LogTemplateInterface = LoggableWithMsg<T> && LoggableWithFormat<T>;

        class ILoggerEngine
        {
        public:
            template <typename... Args>
            void log(std::string_view channel, LogLevel level, fmt::format_string<Args...> fmt, Args &&...args){};

            template <typename... Args>
            void log( LogLevel level, fmt::format_string<Args...> fmt, Args &&...args){};

            template <typename T>
            void log(std::string_view channel, LogLevel level, const T &msg){};

            template <typename T>
            void log(LogLevel level, const T &msg){};

            virtual void configureDefaultFileSink(std::string_view logFilename) = 0;
            virtual void configureDefaultConsoleSink() = 0;
            // //todo add some configuration for multicast sink
            // virtual void configureMulticastSink() = 0;
            virtual void init() = 0;

            virtual void setSinkLevel(std::string_view sinkName, LogLevel l) = 0;
            virtual void setLoggerLevel(std::string_view loggerName, LogLevel l) = 0;

            ~ILoggerEngine() = default;

        private:

        };
    } // namespace detail
}

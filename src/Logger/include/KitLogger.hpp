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
#include "KitLogger/LoggerManager.hpp"


//#ifdef
#include "KitLogger/spdlogEngine/spdlogEngine.hpp"

namespace kit
{
   inline kit::logger::detail::LoggerManager<kit::logger::detail::spdlogEngine> KitLogger;
}


#ifndef DONT_USE_KIT_LOG

#define KIT_LOG_T(...) kit::KitLogger.log(kit::logger::LogLevel::TRACE, __VA_ARGS__);
#define KIT_LOG_D(...) kit::KitLogger.log(kit::logger::LogLevel::DEBUG, __VA_ARGS__);
#define KIT_LOG_I(...) kit::KitLogger.log(kit::logger::LogLevel::INFO, __VA_ARGS__);
#define KIT_LOG_W(...) kit::KitLogger.log(kit::logger::LogLevel::WARN, __VA_ARGS__);
#define KIT_LOG_E(...) kit::KitLogger.log(kit::logger::LogLevel::ERROR, __VA_ARGS__);
#define KIT_LOG_C(...) kit::KitLogger.log(kit::logger::LogLevel::CRITICAL, __VA_ARGS__);

#define KIT_LOG_C_T(CHANNEL, ...)                                                                                      \
    kit::KitLoggerlog(CHANNEL, kit::logger::LogLevel::TRACE, __VA_ARGS__);
#define KIT_LOG_C_D(CHANNEL, ...)                                                                                      \
    kit::KitLogger.log(CHANNEL, kit::logger::LogLevel::DEBUG, __VA_ARGS__);
#define KIT_LOG_C_I(CHANNEL, ...)                                                                                      \
    kit::KitLogger.log(CHANNEL, kit::logger::LogLevel::INFO, __VA_ARGS__);
#define KIT_LOG_C_W(CHANNEL, ...)                                                                                      \
    kit::KitLogger.log(CHANNEL, kit::logger::LogLevel::WARN, __VA_ARGS__);
#define KIT_LOG_C_E(CHANNEL, ...)                                                                                      \
    kit::KitLogger.log(CHANNEL, kit::logger::LogLevel::ERROR, __VA_ARGS__);
#define KIT_LOG_C_C(CHANNEL, ...)                                                                                      \
    kit::KitLogger.log(CHANNEL, kit::logger::LogLevel::CRITICAL, __VA_ARGS__);

#define KIT_LOG_T_IF(CONDITION, ...)                                                                                   \
    if (CONDITION)                                                                                                     \
    KIT_LOG_T(__VA_ARGS__)
#define KIT_LOG_D_IF(CONDITION, ...)                                                                                   \
    if (CONDITION)                                                                                                     \
    KIT_LOG_D(__VA_ARGS__)
#define KIT_LOG_I_IF(CONDITION, ...)                                                                                   \
    if (CONDITION)                                                                                                     \
    KIT_LOG_I(__VA_ARGS__)
#define KIT_LOG_W_IF(CONDITION, ...)                                                                                   \
    if (CONDITION)                                                                                                     \
    KIT_LOG_W(__VA_ARGS__)
#define KIT_LOG_E_IF(CONDITION, ...)                                                                                   \
    if (CONDITION)                                                                                                     \
    KIT_LOG_E(__VA_ARGS__)
#define KIT_LOG_C_IF(CONDITION, ...)                                                                                   \
    if (CONDITION)                                                                                                     \
    KIT_LOG_C(__VA_ARGS__)

#define KIT_LOG_C_T_IF(CONDITION, CHANNEL, ...)                                                                        \
    if (CONDITION)                                                                                                     \
    KIT_LOG_C_T(CHANNEL, __VA_ARGS__)
#define KIT_LOG_C_D_IF(CONDITION, CHANNEL, ...)                                                                        \
    if (CONDITION)                                                                                                     \
    KIT_LOG_C_D(CHANNEL, __VA_ARGS__)
#define KIT_LOG_C_I_IF(CONDITION, CHANNEL, ...)                                                                        \
    if (CONDITION)                                                                                                     \
    KIT_LOG_C_I(CHANNEL, __VA_ARGS__)
#define KIT_LOG_C_W_IF(CONDITION, CHANNEL, ...)                                                                        \
    if (CONDITION)                                                                                                     \
    KIT_LOG_C_W(CHANNEL, __VA_ARGS__)
#define KIT_LOG_C_E_IF(CONDITION, CHANNEL, ...)                                                                        \
    if (CONDITION)                                                                                                     \
    KIT_LOG_C_E(CHANNEL, __VA_ARGS__)
#define KIT_LOG_C_C_IF(CONDITION, CHANNEL, ...)                                                                        \
    if (CONDITION)                                                                                                     \
    KIT_LOG_C_C(CHANNEL, __VA_ARGS__)

namespace{
#define _LOG_EVERY_N(N)                                                                                                \
    { static int _COUNT_ = 0;                                                                                          \
    if (_COUNT_ ++ % N == 0)
}

#define KIT_LOG_T_EVERY_N(N, ...) _LOG_EVERY_N(N) KIT_LOG_T(__VA_ARGS__) }
#define KIT_LOG_D_EVERY_N(N, ...) _LOG_EVERY_N(N) KIT_LOG_D(__VA_ARGS__) }
#define KIT_LOG_I_EVERY_N(N, ...) _LOG_EVERY_N(N) KIT_LOG_I(__VA_ARGS__) }
#define KIT_LOG_W_EVERY_N(N, ...) _LOG_EVERY_N(N) KIT_LOG_W(__VA_ARGS__) }
#define KIT_LOG_E_EVERY_N(N, ...) _LOG_EVERY_N(N) KIT_LOG_E(__VA_ARGS__) }
#define KIT_LOG_C_EVERY_N(N, ...) _LOG_EVERY_N(N) KIT_LOG_C(__VA_ARGS__) }

#define KIT_LOG_C_T_EVERY(N, CHANNEL, ...) _LOG_EVERY_N(N) KIT_LOG_C_T(CHANNEL, __VA_ARGS__) }
#define KIT_LOG_C_D_EVERY(N, CHANNEL, ...) _LOG_EVERY_N(N) KIT_LOG_C_D(CHANNEL, __VA_ARGS__) }
#define KIT_LOG_C_I_EVERY(N, CHANNEL, ...) _LOG_EVERY_N(N) KIT_LOG_C_I(CHANNEL, __VA_ARGS__) }
#define KIT_LOG_C_W_EVERY(N, CHANNEL, ...) _LOG_EVERY_N(N) KIT_LOG_C_W(CHANNEL, __VA_ARGS__) }
#define KIT_LOG_C_E_EVERY(N, CHANNEL, ...) _LOG_EVERY_N(N) KIT_LOG_C_E(CHANNEL, __VA_ARGS__) }
#define KIT_LOG_C_C_EVERY(N, CHANNEL, ...) _LOG_EVERY_N(N) KIT_LOG_C_C(CHANNEL, __VA_ARGS__) }

#endif

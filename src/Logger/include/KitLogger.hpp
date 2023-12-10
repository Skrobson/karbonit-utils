#pragma once
#include "KitLogger/KitLogManager.hpp"

#ifndef DONT_USE_KIT_LOG

#define KIT_LOG_T(...) kit::logger::LogManager::getInstance().log(kit::logger::LogLevel::trace, __VA_ARGS__);
#define KIT_LOG_D(...) kit::logger::LogManager::getInstance().log(kit::logger::LogLevel::debug, __VA_ARGS__);
#define KIT_LOG_I(...) kit::logger::LogManager::getInstance().log(kit::logger::LogLevel::info, __VA_ARGS__);
#define KIT_LOG_W(...) kit::logger::LogManager::getInstance().log(kit::logger::LogLevel::warn, __VA_ARGS__);
#define KIT_LOG_E(...) kit::logger::LogManager::getInstance().log(kit::logger::LogLevel::err, __VA_ARGS__);
#define KIT_LOG_C(...) kit::logger::LogManager::getInstance().log(kit::logger::LogLevel::critical, __VA_ARGS__);

#define KIT_LOG_C_T(CHANNEL, ...)                                                                                      \
    kit::logger::LogManager::getInstance().log(CHANNEL, kit::logger::LogLevel::trace, __VA_ARGS__);
#define KIT_LOG_C_D(CHANNEL, ...)                                                                                      \
    kit::logger::LogManager::getInstance().log(CHANNEL, kit::logger::LogLevel::debug, __VA_ARGS__);
#define KIT_LOG_C_I(CHANNEL, ...)                                                                                      \
    kit::logger::LogManager::getInstance().log(CHANNEL, kit::logger::LogLevel::info, __VA_ARGS__);
#define KIT_LOG_C_W(CHANNEL, ...)                                                                                      \
    kit::logger::LogManager::getInstance().log(CHANNEL, kit::logger::LogLevel::warn, __VA_ARGS__);
#define KIT_LOG_C_E(CHANNEL, ...)                                                                                      \
    kit::logger::LogManager::getInstance().log(CHANNEL, kit::logger::LogLevel::err, __VA_ARGS__);
#define KIT_LOG_C_C(CHANNEL, ...)                                                                                      \
    kit::logger::LogManager::getInstance().log(CHANNEL, kit::logger::LogLevel::critical, __VA_ARGS__);

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

#define _LOG_EVERY_N(N)                                                                                                \
    { static int _COUNT_ = 0;                                                                                          \
    if (_COUNT_ ++ % N == 0)

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

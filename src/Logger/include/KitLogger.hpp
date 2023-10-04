#pragma once
#include "KitLogManager.hpp"


#ifndef DONT_USE_KIT_LOG
#define KIT_LOG_T(...) spdlog::trace(__VA_ARGS__) 
#define KIT_LOG_D(...) spdlog::debug(__VA_ARGS__)
#define KIT_LOG_I(...) spdlog::info(__VA_ARGS__)
#define KIT_LOG_W(...) spdlog::warn(__VA_ARGS__)
#define KIT_LOG_E(...) spdlog::error(__VA_ARGS__)
#define KIT_LOG_C(...) spdlog::critical(__VA_ARGS__)

#define KIT_LOG_C_T(CHANNEL, ...) kit::logger::LogManager::getInstance().getLogger(CHANNEL)->trace(__VA_ARGS__) 
#define KIT_LOG_C_D(CHANNEL, ...) kit::logger::LogManager::getInstance().getLogger(CHANNEL)->debug(__VA_ARGS__)
#define KIT_LOG_C_I(CHANNEL, ...) kit::logger::LogManager::getInstance().getLogger(CHANNEL)->info(__VA_ARGS__)
#define KIT_LOG_C_W(CHANNEL, ...) kit::logger::LogManager::getInstance().getLogger(CHANNEL)->warn(__VA_ARGS__)
#define KIT_LOG_C_E(CHANNEL, ...) kit::logger::LogManager::getInstance().getLogger(CHANNEL)->error(__VA_ARGS__)
#define KIT_LOG_C_C(CHANNEL, ...) kit::logger::LogManager::getInstance().getLogger(CHANNEL)->critical(__VA_ARGS__)
#endif

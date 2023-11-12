#pragma once
#include "KitLogger/KitLogManager.hpp"


#ifndef DONT_USE_KIT_LOG

#define KIT_LOG_T(...) kit::logger::LogManager::getInstance().log(kit::logger::LogLevel::trace, __VA_ARGS__ )
#define KIT_LOG_D(...) kit::logger::LogManager::getInstance().log(kit::logger::LogLevel::debug, __VA_ARGS__)
#define KIT_LOG_I(...) kit::logger::LogManager::getInstance().log(kit::logger::LogLevel::info, __VA_ARGS__)
#define KIT_LOG_W(...) kit::logger::LogManager::getInstance().log(kit::logger::LogLevel::warn, __VA_ARGS__)
#define KIT_LOG_E(...) kit::logger::LogManager::getInstance().log(kit::logger::LogLevel::error, __VA_ARGS__)
#define KIT_LOG_C(...) kit::logger::LogManager::getInstance().log(kit::logger::LogLevel::critical, __VA_ARGS__)

#define KIT_LOG_C_T(CHANNEL, ...) kit::logger::LogManager::getInstance().log(CHANNEL, kit::logger::LogLevel::trace, __VA_ARGS__) 
#define KIT_LOG_C_D(CHANNEL, ...) kit::logger::LogManager::getInstance().log(CHANNEL, kit::logger::LogLevel::debug, __VA_ARGS__)
#define KIT_LOG_C_I(CHANNEL, ...) kit::logger::LogManager::getInstance().log(CHANNEL, kit::logger::LogLevel::info, __VA_ARGS__)
#define KIT_LOG_C_W(CHANNEL, ...) kit::logger::LogManager::getInstance().log(CHANNEL, kit::logger::LogLevel::warn, __VA_ARGS__)
#define KIT_LOG_C_E(CHANNEL, ...) kit::logger::LogManager::getInstance().log(CHANNEL, kit::logger::LogLevel::error, __VA_ARGS__)
#define KIT_LOG_C_C(CHANNEL, ...) kit::logger::LogManager::getInstance().log(CHANNEL, kit::logger::LogLevel::critical, __VA_ARGS__)

#endif
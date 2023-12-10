#include <thread>

#include "KitLogger.hpp"

int main()
{
    kit::logger::LogManager::getInstance().configureDefaultConsoleSink();
    kit::logger::LogManager::getInstance().initDefaultLogger();

    std::thread t = std::thread([]() { KIT_LOG_W("THREAD"); });

    for (auto i = 0; i < 100000; i++)
    {
        KIT_LOG_W("Logg {}", i);
        KIT_LOG_C_I("CTest", "llll {}", i);
        KIT_LOG_E_EVERY_N(20, "Log every {}", i);
        KIT_LOG_C_IF(i % 2 == 0, "CTest", "IF {}", i);
    }

    if (t.joinable())
        t.join();
}

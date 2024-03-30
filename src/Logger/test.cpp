#include <thread>

#include "KitLogger.hpp"

using namespace kit;
int main()
{
    kit::KitLogger.configureDefaultConsoleSink();
    kit::KitLogger.init();
    kit::KitLogger.log(kit::logger::LogLevel::INFO, "Test log");
    kit::KitLogger.log(kit::logger::LogLevel::WARN, "Float log: {}", 3.14f);
    std::thread t = std::thread([]() { for (auto i = 0; i < 100000; i++)
    {
        kit::KitLogger.log(kit::logger::LogLevel::INFO, "Thread log");
        kit::KitLogger.log(kit::logger::LogLevel::WARN, "Thread log: {}", i);
    }});

    for (auto i = 0; i < 100000; i++)
    {
        kit::KitLogger.log(kit::logger::LogLevel::INFO, "Test log");
        kit::KitLogger.log(kit::logger::LogLevel::CRITICAL, "Test log {}", i);
        kit::KitLogger.log(kit::logger::LogLevel::WARN, "Test log {}", i);
        KIT_LOG_C_C_IF(i%2, "CONDITIONAL", "Conditional {}", i);
    }

    if (t.joinable())
      t.join();

    KitLogger.log("SecondLogger", kit::logger::LogLevel::ERROR, "Second logger log");
}

#include "KitLogger.hpp"


int main(){
    
    kit::logger::LogManager::getInstance().configureDefaultConsoleSink();
    kit::logger::LogManager::getInstance().initDefaultLogger();

    for(auto i = 0; i <1000000; i++){
        KIT_LOG_I("Logg {}", i);
        KIT_LOG_C_I("CTest", "llll {}", i);
    }
}
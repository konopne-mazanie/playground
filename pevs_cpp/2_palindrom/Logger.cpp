#include "Logger.h"

namespace pevs
{
    Logger::Logger()
    {
        logfile.open("palindrom.log");
    }

    Logger::~Logger()
    {
        logfile.close();
    }

    auto Logger::getInstance() -> Logger&
    {
        static Logger instance;
        return instance;
    }

    void Logger::log(const char* text)
    {
        std::cout << text << std::endl;
        logfile << text << std::endl;;
    }
}
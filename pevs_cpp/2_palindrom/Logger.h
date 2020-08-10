#pragma once

#include <fstream>
#include <memory>
#include <iostream>

namespace pevs
{
    class Logger
    {
    private:
        std::ofstream logfile;

        Logger();
    public:
        Logger(const Logger&) = delete;
        void operator=(const Logger&) = delete;
        ~Logger();

        static Logger& getInstance();
        void log(const char* text);
    };
}
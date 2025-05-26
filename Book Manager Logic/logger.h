#pragma once
#pragma once
#include <string>
#include <fstream>
#include <mutex>

class Logger {
public:
    static void log(const std::string& message, const std::string& logFile = "log.txt");

private:
    static std::mutex logMutex;
};

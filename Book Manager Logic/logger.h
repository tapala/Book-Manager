#pragma once
#include "pch.h"
#include <string>
#include <fstream>
#include <mutex>

class Logger {
public:
    static void log(const std::string& message, const std::string& logFile = "../data/log.txt");

private:
    static std::mutex logMutex;
};

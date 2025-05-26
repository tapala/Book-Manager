#include "pch.h"
#include "Logger.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

std::mutex Logger::logMutex;

void Logger::log(const std::string& message, const std::string& logFile) {
    std::lock_guard<std::mutex> lock(logMutex);

    std::ofstream file(logFile, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Logger Error: Could not open log file: " << logFile << std::endl;
        return;
    }

    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
    localtime_s(&tm, &time);

    file << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] " << message << std::endl;
}

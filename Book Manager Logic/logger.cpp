#include "Logger.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#pragma warning(disable:4996)

std::mutex Logger::logMutex;

void Logger::log(const std::string& message, const std::string& logFile) {
    std::lock_guard<std::mutex> lock(logMutex);

    std::ofstream file(logFile, std::ios::app);  // append mode
    if (!file.is_open()) {
        std::cerr << "Logger Error: Could not open log file: " << logFile << std::endl;
        return;
    }

    // Get current time
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm timeInfo;
    localtime_s(&timeInfo, &time);  // Secure version
    file << "[" << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S") << "] ";
    file << message << std::endl;
}

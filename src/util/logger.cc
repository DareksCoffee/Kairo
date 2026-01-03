/*
    * @file util/logger.cc
    * @author Coffee Games Studio
    * @date 1/2/2026
    * @brief 
    * Implementation of the logging system for the Kairo engine
    *
*/

#include <util/logger.hh>
#include <chrono>
#include <iomanip>
#include <sstream>

Logger* Logger::instance = nullptr;

Logger::Logger() : file_enabled(false)
{
}

Logger::~Logger()
{
    if (log_file.is_open())
    {
        log_file.close();
    }
}

Logger* Logger::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Logger();
    }
    return instance;
}

std::string Logger::getTimestamp() const
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    
    return ss.str();
}

std::string Logger::getLogTypeString(LOG_TYPE type) const
{
    switch (type)
    {
        case LOG_TYPE::LOG_INFO:
            return "[INFO]";
        case LOG_TYPE::LOG_WARNING:
            return "[WARNING]";
        case LOG_TYPE::LOG_DEBUG:
            return "[DEBUG]";
        case LOG_TYPE::LOG_ERROR:
            return "[ERROR]";
        case LOG_TYPE::LOG_CRASH:
            return "[CRASH]";
        default:
            return "[UNKNOWN]";
    }
}

void Logger::log(const std::string& message, LOG_TYPE type)
{
    std::string timestamp = getTimestamp();
    std::string type_str = getLogTypeString(type);
    std::string formatted = timestamp + " " + type_str + " " + message;
    
    // Console output
    std::cout << formatted << std::endl;
    
    // File output
    if (file_enabled && log_file.is_open())
    {
        log_file << formatted << std::endl;
        log_file.flush();
    }
}

void Logger::logInfo(const std::string& message)
{
    log(message, LOG_TYPE::LOG_INFO);
}

void Logger::logWarning(const std::string& message)
{
    log(message, LOG_TYPE::LOG_WARNING);
}

void Logger::logDebug(const std::string& message)
{
    log(message, LOG_TYPE::LOG_DEBUG);
}

void Logger::logError(const std::string& message)
{
    log(message, LOG_TYPE::LOG_ERROR);
}

void Logger::logCrash(const std::string& message)
{
    log(message, LOG_TYPE::LOG_CRASH);
}

void Logger::enableFileLogging(const std::string& filename)
{
    if (log_file.is_open())
    {
        log_file.close();
    }
    
    log_file.open(filename, std::ios::app);
    if (log_file.is_open())
    {
        file_enabled = true;
        logInfo("File logging enabled: " + filename);
    }
    else
    {
        file_enabled = false;
        logError("Failed to open log file: " + filename);
    }
}

void Logger::disableFileLogging()
{
    if (log_file.is_open())
    {
        logInfo("File logging disabled");
        log_file.close();
    }
    file_enabled = false;
}

void Logger::clear()
{
    if (log_file.is_open())
    {
        log_file.close();
        log_file.open("", std::ios::trunc);
    }
}

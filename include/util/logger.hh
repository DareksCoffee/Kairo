/*
    * @file util/logger.hh
    * @author Coffee Games Studio
    * @date 12/9/2025
    * @brief 
    * Logging system for the Kairo engine
    *
*/

#ifndef LOGGER_HH
#define LOGGER_HH

#include <iostream>
#include <fstream>
#include <string>
#include <util/types.hh>
#include <util/log_type.hh>

class Logger
{
private:
    static Logger* instance;
    std::ofstream log_file;
    bool file_enabled;
    
    Logger();
    
public:
    ~Logger();
    
    // Singleton accessor
    static Logger* getInstance();
    
    // Core logging methods
    void log(const std::string& message, LOG_TYPE type = LOG_TYPE::LOG_INFO);
    void logInfo(const std::string& message);
    void logWarning(const std::string& message);
    void logDebug(const std::string& message);
    void logError(const std::string& message);
    void logCrash(const std::string& message);
    
    // File operations
    void enableFileLogging(const std::string& filename);
    void disableFileLogging();
    
    // Utility
    void clear();
    
private:
    std::string getLogTypeString(LOG_TYPE type) const;
    std::string getTimestamp() const;
};

#endif
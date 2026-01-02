/*
    * @file util/log_type.hh
    * @author Coffee Games Studio
    * @date 12/9/2025
    * @brief 
    * The log type of the logger
    *
*/

#ifndef LOG_TYPE_HH
#define LOG_TYPE_HH

enum class LOG_TYPE
{
    LOG_INFO    =      0x0000A,
    LOG_WARNING =      0x0000B,
    LOG_DEBUG   =      0x0000C,
    LOG_ERROR   =      0x0000D,
    LOG_CRASH   =      0x0000F
};

#endif
#ifndef CLOGGER_H
#define CLOGGER_H

#include <iostream>
#include <fstream>

class Logger
{
private:
    enum LogLevel
    {
        debug,
        info,
        warn,
        error,
        fatal
    };
    std::ofstream fout;
    bool new_line;
    LogLevel last_level;
    LogLevel level;
    bool logging;
    int to_level(std::string log_level, LogLevel &lv);
    int log(LogLevel lv, const std::string &s);
    int print(const std::string &s);

public:
    Logger();
    Logger(const std::string &log_file);
    int set_level(const std::string &log_level);
    int open(const std::string &log_file);
    int close();
    int start();
    int stop();
    int log(const std::string &log_type, const std::string &format, ...);
};

#include "clogger.cpp"

#endif
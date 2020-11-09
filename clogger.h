#ifndef CLOGGER_H
#define CLOGGER_H

#include <iostream>
#include <fstream>

class Logger
{
private:
    std::ofstream fout;
    bool new_line;
    std::string last_tag;
    std::string level;
    int print(char *s);

public:
    Logger();
    Logger(const std::string &log_file);
    int open(const std::string &log_file);
    int close();
    int log(const std::string &log_type, const std::string &format, ...);
};

#include "clogger.cpp"

#endif
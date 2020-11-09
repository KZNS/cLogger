#ifndef CLOGGER_CPP
#define CLOGGER_CPP

#include "clogger.h"

Logger::Logger()
{
    new_line = true;
}
Logger::Logger(const std::string &log_file)
{
    fout.open(log_file);
    new_line = true;
}
int Logger::open(const std::string &log_file)
{
    if (fout.is_open())
    {
        fout.close();
    }
    fout.open(log_file);
    new_line = true;
    return 0;
}
int Logger::close()
{
    if (fout.is_open())
    {
        fout.close();
        new_line = true;
    }
    return 0;
}
int Logger::log(const std::string &log_type, const std::string &format, ...)
{
    va_list ap;
    va_start(ap, format);

    int num;
    char tmp[100];
    num = sprintf(tmp, format.c_str(), ap);

    va_end(ap);

    return num;
}

#endif
#ifndef CLOGGER_CPP
#define CLOGGER_CPP

#include "clogger.h"
#include <cstring>
#include <algorithm>

int Logger::to_level(std::string log_level, LogLevel &lv)
{
    std::transform(log_level.begin(), log_level.end(),
                   log_level.begin(), ::tolower);
    if (log_level == "debug")
    {
        lv = debug;
    }
    else if (log_level == "info")
    {
        lv = info;
    }
    else if (log_level == "warn")
    {
        lv = warn;
    }
    else if (log_level == "error")
    {
        lv = error;
    }
    else if (log_level == "fatal")
    {
        lv = fatal;
    }
    else
    {
        log(fatal, "Warn log level.\n");
        return -1;
    }
    return 0;
}
int Logger::log(LogLevel lv, const std::string &s)
{
    if (lv >= level)
    {
        switch (lv)
        {
        case debug:
            print("debug: ");
            break;
        case info:
            print("info: ");
            break;
        case warn:
            print("warn: ");
            break;
        case error:
            print("error: ");
            break;
        case fatal:
            print("fatal: ");
            break;
        }
        print(s);
        return 0;
    }
    return 1;
}
int Logger::print(const std::string &s)
{
    if (fout.is_open())
    {
        fout << s;
    }
    else
    {
        std::cout << s;
    }
    return 0;
}
Logger::Logger()
{
    new_line = true;
    level = error;
}
Logger::Logger(const std::string &log_file) : Logger()
{
    fout.open(log_file);
}
int Logger::set_level(const std::string &log_level)
{
    LogLevel lv;
    if (to_level(log_level, lv))
    {
        return -1;
    }
    level = lv;
    return 0;
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
int Logger::log(const std::string &log_level, const std::string &format, ...)
{
    va_list ap;
    va_start(ap, format);

    int num;
    char tmp[100];
    num = sprintf(tmp, format.c_str(), ap);

    va_end(ap);

    int len;
    len = strlen(tmp);
    if (len == 0)
    {
        log(fatal, "Empty log message.\n");
        return -1;
    }
    if (tmp[len - 1] == '\n')
    {
        if (len - 1 > 80)
        {
            log(fatal, "Log message is to long.\n");
            return -1;
        }
    }
    else
    {
        if (len > 80)
        {
            log(fatal, "log message is to long.\n");
            return -1;
        }
        tmp[len] = '\n';
        tmp[len + 1] = '\0';
    }

    LogLevel lv;
    if (to_level(log_level, lv))
    {
        return -1;
    }

    log(lv, tmp);

    return 0;
}

#endif
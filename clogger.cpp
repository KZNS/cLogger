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
        lv = lldebug;
    }
    else if (log_level == "info")
    {
        lv = llinfo;
    }
    else if (log_level == "warn")
    {
        lv = llwarn;
    }
    else if (log_level == "error")
    {
        lv = llerror;
    }
    else if (log_level == "fatal")
    {
        lv = llfatal;
    }
    else
    {
        log(llfatal, "Warn log level.\n");
        return -1;
    }
    return 0;
}
int Logger::log(LogLevel lv, const std::string &s)
{
    if (!logging)
    {
        return 0;
    }
    if (lv >= level)
    {
        switch (lv)
        {
        case lldebug:
            print("debug: ");
            break;
        case llinfo:
            print("info: ");
            break;
        case llwarn:
            print("warn: ");
            break;
        case llerror:
            print("error: ");
            break;
        case llfatal:
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
    level = llerror;
    logging = true;
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
int Logger::start()
{
    logging = true;
    return 0;
}
int Logger::stop()
{
    logging = false;
    return 0;
}
int Logger::log(const std::string &log_level, const std::string &format, ...)
{
    va_list ap;
    va_start(ap, format);

    int num;
    char tmp[100];
    num = vsprintf(tmp, format.c_str(), ap);

    va_end(ap);

    int len;
    len = strlen(tmp);
    if (len == 0)
    {
        log(llfatal, "Empty log message.\n");
        return -1;
    }
    if (tmp[len - 1] == '\n')
    {
        if (len - 1 > 80)
        {
            log(llfatal, "Log message is to long.\n");
            return -1;
        }
    }
    else
    {
        if (len > 80)
        {
            log(llfatal, "log message is to long.\n");
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
int Logger::debug(const std::string &format, ...)
{
    va_list ap;
    va_start(ap, format);

    log("debug", format, ap);

    va_end(ap);
    return 0;
}
int Logger::info(const std::string &format, ...)
{
    va_list ap;
    va_start(ap, format);

    log("info", format, ap);

    va_end(ap);
    return 0;
}
int Logger::warn(const std::string &format, ...)
{
    va_list ap;
    va_start(ap, format);

    log("warn", format, ap);

    va_end(ap);
    return 0;
}
int Logger::error(const std::string &format, ...)
{
    va_list ap;
    va_start(ap, format);

    log("error", format, ap);

    va_end(ap);
    return 0;
}
int Logger::fatal(const std::string &format, ...)
{
    va_list ap;
    va_start(ap, format);

    log("fatal", format, ap);

    va_end(ap);
    return 0;
}

#endif
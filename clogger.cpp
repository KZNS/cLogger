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
int Logger::try_log(const std::string &log_level, const std::string format, va_list &ap)
{
    int len;
    vsnprintf(buffer, 500, format.c_str(), ap);
    len = strlen(buffer);

    if (len == 0 || (len == 1 && buffer[0] == '\n'))
    {
        log(llfatal, "Empty log message.\n");
        return -1;
    }
    if (buffer[len - 1] != '\n')
    {
        buffer[len++] = '\n';
        buffer[len] = '\0';
    }

    LogLevel lv;
    if (to_level(log_level, lv))
    {
        return -1;
    }

    return log(lv, buffer);
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
            debuged = true;
            print("debug: ");
            break;
        case llinfo:
            infoed = true;
            print("info: ");
            break;
        case llwarn:
            warned = true;
            print("warn: ");
            break;
        case llerror:
            errored = true;
            print("error: ");
            break;
        case llfatal:
            fataled = true;
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
    *out << s;
    return 0;
}
Logger::Logger()
{
    level = llerror;
    logging = true;
    out = &std::cout;
    using_new_stream = false;
    reset_log();
}
Logger::Logger(const std::string &log_file) : Logger()
{
    open(log_file);
}
Logger::Logger(std::ostream &out_stream) : Logger()
{
    open(out_stream);
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
    close();
    out = new std::ofstream(log_file);
    using_new_stream = true;
    return 0;
}
int Logger::open(std::ostream &out_stream)
{

    close();
    out = &out_stream;
    using_new_stream = false;
    return 0;
}
int Logger::close()
{
    if (out)
    {
        if (using_new_stream)
        {
            delete out;
        }
        out = &std::cout;
        using_new_stream = false;
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
int Logger::log(const std::string &log_level, const std::string format, ...)
{
    int e;
    va_list ap;
    va_start(ap, format);

    e = try_log(log_level, format, ap);

    va_end(ap);
    return e;
}
int Logger::debug(const std::string format, ...)
{
    int e;
    va_list ap;
    va_start(ap, format);

    e = try_log("debug", format, ap);

    va_end(ap);
    return e;
}
int Logger::info(const std::string format, ...)
{
    int e;
    va_list ap;
    va_start(ap, format);

    e = try_log("info", format, ap);

    va_end(ap);
    return e;
}
int Logger::warn(const std::string format, ...)
{
    int e;
    va_list ap;
    va_start(ap, format);

    e = try_log("warn", format, ap);

    va_end(ap);
    return e;
}
int Logger::error(const std::string format, ...)
{
    int e;
    va_list ap;
    va_start(ap, format);

    e = try_log("error", format, ap);

    va_end(ap);
    return e;
}
int Logger::fatal(const std::string format, ...)
{
    int e;
    va_list ap;
    va_start(ap, format);

    e = try_log("fatal", format, ap);

    va_end(ap);
    return e;
}

bool Logger::has_log() { return (debuged || infoed || warned || errored || fataled); }
bool Logger::has_debug() { return debuged; }
bool Logger::has_info() { return infoed; }
bool Logger::has_warn() { return warned; }
bool Logger::has_error() { return errored; }
bool Logger::has_fatal() { return fataled; }

void Logger::reset_log() { debuged = infoed = warned = errored = fataled = false; }
void Logger::reset_debug() { debuged = false; }
void Logger::reset_info() { infoed = false; }
void Logger::reset_warn() { warned = false; }
void Logger::reset_error() { errored = false; }
void Logger::reset_fatal() { fataled = false; }

#endif
#include "clogger.h"
#include <cstdio>

int main()
{
    Logger logger;
    logger.log("debug", "debug message.");
    logger.log("info", "info message.");
    logger.log("warn", "warn message.");
    logger.log("error", "error message.");
    logger.log("fatal", "fatal message.");

    logger.set_level("debug");

    logger.log("debug", "debug message 2.");
    logger.log("info", "info message 2.");
    logger.log("warn", "warn message 2. \n");
    logger.log("error", "error message 2.");
    logger.log("fatal", "fatal message 2.");

    logger.set_level("fATal");

    logger.log("debug", "debug message 3.");
    logger.log("info", "info message 3.");
    logger.log("warn", "warn message 3. \n");
    logger.log("error", "error message 3.");
    logger.log("fatal", "fatal message 3.");

    logger.open("example_log.txt");
    logger.set_level("info");

    logger.log("debug", "debug message 4.");
    logger.log("info", "info message 4.");
    logger.log("warn", "warn message 4. \n");
    logger.log("error", "error message 4.");
    logger.log("fatal", "fatal message 4.");

    return 0;
}
#include "clogger.h"
#include <cstdio>
using namespace std;
int main()
{
    Logger logger;
    logger.log("debug", "debug message.");
    logger.log("info", "info message.");
    logger.log("warn", "warn message.");
    logger.log("error", "error message.");
    logger.log("fatal", "fatal message.");

    logger.set_level("debug");

    int a = 1;
    logger.log("debug", "%d %s", a, "2333");

    logger.log("debug", "debug message 2.");
    logger.log("info", "info message 2.");
    logger.log("warn", "warn message 2. \n");
    logger.log("error", "error message 2.");
    logger.log("fatal", "fatal message 2.");

    logger.stop();
    logger.log("debug", "debug message 5.");
    logger.log("info", "info message 5.");
    logger.log("warn", "warn message 5. \n");
    logger.start();
    logger.log("error", "error message 5.");
    logger.log("fatal", "fatal message 5.");

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

    logger.close();

    logger.debug("debug message 6. %d", 1);
    logger.info("info message 6. %d", 1);
    logger.warn("warn message 6. %d\n", 1);
    logger.error("error message 6. %d", 1);
    logger.fatal("fatal message 6. %d", 1);

    if (logger.has_log())
    {
        printf("has log\n");
    }
    if (logger.has_error())
    {
        printf("has error\n");
    }
    logger.reset_error();
    if (logger.has_error())
    {
        printf("has error\n");
    }
    else
    {
        printf("has not error\n");
    }

    return 0;
}
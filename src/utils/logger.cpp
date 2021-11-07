#include "logger.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <stdarg.h>

namespace mrld
{
    FILE* Logger::_output = stdout;
    LogLevel Logger::_log_level = LogLevel::INF;

    void Logger::log(LogLevel log_level, const char *format, ...)
    {
        if (static_cast<int>(_log_level) > static_cast<int>(log_level)) {
            return;
        }

        char msg[LOGGER_MESSAGE_MAX_LENGTH];
        va_list arg_q;
        va_start(arg_q, format);
        vsnprintf_s(msg, sizeof(msg), format, arg_q);
        va_end(arg_q);

        log_time();
        switch (log_level) {
            case DBG:
                log_debug(msg);
                break;
            case INF:
                log_info(msg);
                break;
            case WRN:
                log_warning(msg);
                break;
            case ERR:
                log_error(msg);
                break;
        }
        fprintf(_output, "\n");
    }

    void Logger::log_time()
    {
        std::chrono::time_point const now = std::chrono::system_clock::now();
        std::time_t now_tt = std::chrono::system_clock::to_time_t(now);
        tm tm;
        gmtime_s(&tm, &now_tt);

        /* Format datetime as 24-hour yyyy-mm-dd hh:mm:ss */
        char buffer[LOGGER_DATETIME_BUFFER_SIZE];
        sprintf_s(buffer, sizeof(buffer), "[%04d-%02d-%02d %02d:%02d:%02d] ",
                  1900 + tm.tm_year,
                  tm.tm_mon,
                  tm.tm_mday,
                  tm.tm_hour,
                  tm.tm_min,
                  tm.tm_sec);
        fprintf(_output, "%s", buffer);
    }
}

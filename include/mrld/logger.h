#pragma once

#include <string>

namespace mrld
{
    constexpr uint16_t LOGGER_MESSAGE_MAX_LENGTH = 256;
    constexpr uint16_t LOGGER_DATETIME_BUFFER_SIZE = 32;
    constexpr uint16_t LOGGER_SHADER_ERR_MSG_MAX_LENGTH = 32;

    enum LogLevel
    {
        DBG,
        INF,
        WRN,
        ERR
    };

    class Logger
    {
    private:
        Logger() = default;

    public:
        static void log(LogLevel log_level, const char *format, ...);
        static inline void set_output_file(FILE *output) { _output = output; }
        static inline void set_log_level(LogLevel level) { _log_level = level; }
    private:
        static void log_time();
        static inline void log_debug(const std::string &msg) { fprintf(_output, "DBG: %s", msg.c_str()); }
        static inline void log_info(const std::string &msg) { fprintf(_output, "INF: %s", msg.c_str()); }
        static inline void log_warning(const std::string &msg) { fprintf(_output, "WRN: %s", msg.c_str()); }
        static inline void log_error(const std::string &msg) { fprintf(_output, "ERR: %s", msg.c_str()); }

        static FILE* _output;
        static LogLevel _log_level;
    };
}

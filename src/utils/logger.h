#pragma once

#include <string>

namespace mrld
{
    constexpr uint16_t LOGGER_MESSAGE_MAX_LENGTH = 512;
    constexpr uint16_t LOGGER_DATETIME_BUFFER_SIZE = 32;
    constexpr uint16_t LOGGER_SHADER_ERR_MSG_MAX_LENGTH = 512;

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
        // TODO this function is pretty bad, it should rather return than write
        static void log_time();
        // TODO remove this, parametrize better
        static inline void log_debug(const std::string &msg) { fprintf(_output, "DBG: %s", msg.c_str()); }
        static inline void log_info(const std::string &msg) { fprintf(_output, "INF: %s", msg.c_str()); }
        static inline void log_warning(const std::string &msg) { fprintf(_output, "WRN: %s", msg.c_str()); }
        // TODO include __FILE__ and __LINE__ from caller
        static inline void log_error(const std::string &msg) { fprintf(_output, "ERR: %s", msg.c_str()); }

        static FILE* _output;
        static LogLevel _log_level;
    };
}

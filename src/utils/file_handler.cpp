#include <fstream>
#include <sstream>

#include "file_handler.h"
#include "logger.h"

std::string mrld::FileHandler::read_file_contents(const char *filepath)
{
    std::ifstream file;
    try {
        file.open(filepath);
        if (!file.is_open()) {
            char msg[LOGGER_MESSAGE_MAX_LENGTH];
            int sprintf_res = sprintf_s(msg,
                                        LOGGER_MESSAGE_MAX_LENGTH,
                                        "Error reading file %s. Cannot be opened for reading", filepath);
            if (sprintf_res == -1) {
                Logger::log(LogLevel::ERR, "%s", "Error reading file. Could not retrieve error message.");
            } else {
                Logger::log(LogLevel::ERR, "%s", msg);
            }
        }
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        return stream.str();
    }
    catch (std::ifstream::failure &e) {
        char msg[LOGGER_MESSAGE_MAX_LENGTH];
        int sprintf_res = sprintf_s(msg, LOGGER_MESSAGE_MAX_LENGTH, "Error reading file %s - %s", filepath, e.what());
        if (sprintf_res == -1) {
            Logger::log(LogLevel::ERR, "%s", "Error reading file. Could not retrieve error message.");
        } else {
            Logger::log(LogLevel::ERR, "%s", msg);
        }
    }
    return std::string();
}

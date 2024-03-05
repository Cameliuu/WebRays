#ifndef LOGGER_H
#define LOGGER_H
#include <FS>
class Logger{
    public:
        void logError(const char* error_message);
        void logInfo(const char* info_message);
        void logSuccess(const char* success_message);
        static const char* log_file;
    private:

};
#endif
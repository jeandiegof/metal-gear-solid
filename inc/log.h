#ifndef LOG_H
#define LOG_H

#include <stdint.h>

// All Log(); messages will be appended to this file
#define LOGFILE	"game.log"

// Flag for LOGFILE existence check.
uint8_t log_created;


// Logs a message to LOGFILE.
void Log (char *message);

// Logs a message and exit the application.
void LogErr (char *message);

#endif // LOG_H

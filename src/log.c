#include <stdlib.h>
#include <stdio.h>

#include "inc/log.h"

#define TRUE 1
#define FALSE 0

uint8_t log_created = FALSE;

void Log (char *message)
{
  FILE *file;

  if (!log_created)
  {
    file = fopen(LOGFILE, "w");
    log_created = TRUE;
  }
  else
    file = fopen(LOGFILE, "a");

  if (file == NULL)
  {
    if (log_created)
      log_created = FALSE;
    return;
  }
  else
  {
    fputs(message, file);
    fclose(file);
  }

  if (file)
    fclose(file);
}

void LogErr (char *message)
{
  Log(message);
  Log("\n");
  exit(1);
}

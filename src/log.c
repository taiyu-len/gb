/* log.c */
# include "log.h"

bool  LOGGING = 0;
FILE *LOGFILE = NULL;

static void init(void) __attribute__((constructor));
void init(void) {
  LOGFILE = stdout;
}


/*!@file   log.h */
# ifndef  _LOG_H
# define  _LOG_H
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <errno.h>

extern bool  LOGGING;
extern FILE *LOGFILE;

#define logf(fmt, ...)                                 \
  do{ if(LOGGING) fprintf(LOGFILE, fmt, ##__VA_ARGS__);\
      fflush(LOGFILE); } while(0)

#define errf(fmt, ...) \
  do{ fprintf(stderr,"\033[91m"__FILE__ ":%u\033[39m\n",__LINE__);  \
      if(errno){ perror(NULL); errno = 0;}        \
      fprintf(stderr, fmt "\n", ##__VA_ARGS__);     \
      fflush(stderr); } while(0)

# endif /*_LOG_H*/


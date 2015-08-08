/* gb_player.c */
#include "gb.h"

# include <stdlib.h>
# include <getopt.h>
# include <errno.h>

int main(int argc, char **argv)
{
  char *gamefile = NULL;
  int  c;
  struct gb gb;

  //Scan for options
  while((c = getopt(argc, argv, "l::g:")) != -1)
    switch(c) {
      case 'l':
        LOGGING = true;
        if(optarg) {
          //-l -
          if(optarg[0] == '-' && optarg[1] == '\0') {
            LOGFILE = stdout;
          }
          else if((LOGFILE = fopen(optarg, "wx")) == NULL) {
            errf();
            goto fail;
          }
        }
        break;
      case 'g':
        gamefile = optarg;
        break;
    }
  if(!gamefile) {
      gamefile = argv[optind];
    }
  if(!gamefile) {
    errf("Requires a gameboy rom to play\n");
    goto fail;
  }

  gb_loadfile(&gb, gamefile);

  while(gb_update(&gb) == RET_SUCCESS) {
    if( gb.mem.mbc.read(&gb,gb.reg.PC) == 0
        ||gb.reg.SP == 0xCFFF) getchar();
  };

  return EXIT_SUCCESS;
fail:
  return EXIT_FAILURE;
}



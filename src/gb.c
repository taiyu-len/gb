/* gb.c */
# include "gb.h"
# include "gb_exec.h"

# include <stdlib.h>
# include <stdio.h>
# include <time.h>

struct gb *gb_loadfile(struct gb *gb, char const filename[])
{
  FILE *file;
  void *rm = NULL; /* Used to free gameboy on failure if we need to */

  logf("Loading File %s\n", filename);
  //openfile
  if((file = fopen(filename, "r")) == NULL) {
    errf();
    goto fopen_fail;
  }
  //allocate memory if requested
  if(gb == NULL && (gb = rm = malloc(sizeof(*gb))) == NULL) {
    errf();
    goto malloc_fail;
  }
  //Rom files should be a multiple of 0x4000
  if(fread(gb->mem.rom, 1, 0x80 * 0x4000, file) % 0x4000 != 0) {
    errf("Invalid Rom file\n");
    goto read_fail;
  }

  gb_register_init(gb);
  gb_memory_init(gb);

  logf("Finished loading gameboy\n");
  logf("gameboy type: %sGB_MODE\n",gb->mode?"":"C");
  logf("title       : %.16s\n",gb->title);
  fclose(file);
  return gb;

/* cleanup on failure */
read_fail:

  free(rm);
malloc_fail:

  fclose(file);
fopen_fail:

  return NULL;
}

int        gb_update(struct gb *gb)
{
  struct timespec delay = {0, 0};
  if(gb == NULL) {
    errf("invalid argument\n");
    abort();
  }
  //Logging
    logf("PC:%.4x|", REG(PC));
  //TMP
  //Get opcode
  byte opcode = READ(REG(PC)++);
  //Execute opcode
  if(gb_exec(gb, opcode)) {
    errf("Invalid opcode, %x",opcode);
    return RET_FAILURE;
  }
  //delay for 0.5 ms per cycle used
  //TODO made 100 times slower for debugging
  delay.tv_nsec = gb->cycle * 5000;
  gb->cycle = 0;
  nanosleep(&delay, NULL);
  return RET_SUCCESS;
}


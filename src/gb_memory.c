/* gb_memory.c */
# include "gb_memory.h"
# include "gb_io.h"
# include "gb_mbc.h"
# include "gb.h"

void gb_memory_init(struct gb *gb)
{
  //Set gameboy mode
  byte gb_type = gb->mem.rom[0][ADDR_GAMEBOY_TYPE];
  if(gb_type == 0xC0) { gb_type = 0x80; }
  if(gb_type == 0x80) { gb->mode = CGB_MODE; }
  else                { gb->mode = GB_MODE; }
  //set title
  gb->title = (char(*)[16])&gb->mem.rom[0][ADDR_GAME_TITLE];

  gb_io_init (gb);
  gb_mbc_init(gb);
}


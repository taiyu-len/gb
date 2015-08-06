/* gb_rom.c */
# include "gb_rom.h"
# include "gb.h"

void gb_rom_init(struct gb *gb)
{
  //Set gameboy mode
  if( gb->mem.rom[0][ADDR_GAMEBOY_TYPE - 0x100] == 0x80
      || gb->mem.rom[0][ADDR_GAMEBOY_TYPE - 0x100] == 0xC0) {
    gb->mode = CGB_MODE;
  }
  else {
    gb->mode = GB_MODE;
  }
}



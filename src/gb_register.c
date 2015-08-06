/* gb_register.c */
# include "gb_register.h"
# include "gb.h"

void gb_register_init(struct gb *gb)
{
  REG(AF) = 0x11;
  REG( F) = 0xB0;
  REG(BC) = 0x0013;
  REG(DE) = 0x00D8;
  REG(HL) = 0x014D;
  REG(SP) = 0xFFFE;
  REG(PC) = 0x0100;
}



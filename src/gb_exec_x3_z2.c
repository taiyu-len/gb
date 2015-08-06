/* exec_x3_z2.c */
#include "gb_exec_x3_z2.h"

int gb_exec_x3_z2(struct gb *gb, byte op)
{
  //Get 16bit immediate values
  addr address = READ16(REG(PC)++);

  byte y = OPCODE_Y(op);

  //y>4 are invalid on gb cpu
  if(y > 4) return RET_FAILURE;

  //Check condition and jmp to addr if true
  if(TABLE_CC[y](gb)) {
    REG(PC) = address;
    gb->cycle += 4;
  }
  logf("JP %s,0x%x",STR_CC[y], address);

  gb->cycle += 12;
  return RET_SUCCESS;
}


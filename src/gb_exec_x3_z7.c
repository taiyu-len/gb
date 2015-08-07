/* exec_x3_z7.c */
#include "gb_exec_x3_z7.h"
//RST y*8
int gb_exec_x3_z7(struct gb *gb, byte op)
{
  //Store pc value
  PUSH(REG(PC));
  //Disable intterupts
  gb->mem.ime = 0x00;
  //jump to interrupt
  REG(PC) = OPCODE_Y(op) * 0x08;

  gb->cycle += 12;
  logf("RST 0x%.2x",OPCODE_Y(op));

  return RET_SUCCESS;
}



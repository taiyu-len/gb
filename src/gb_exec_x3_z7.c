/* exec_x3_z7.c */
#include "gb_exec_x3_z7.h"
//RST y*8
int gb_exec_x3_z7(struct gb *gb, byte op)
{
  PUSH(REG(PC));
  REG(PC) = OPCODE_Y(op) * 0x08;

  logf("RST 0x%x",OPCODE_Y(op));

  return RET_SUCCESS;
}



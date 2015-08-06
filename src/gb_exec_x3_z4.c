/* exec_x3_z4.c */
#include "gb_exec_x3_z4.h"

//call cc[y], nn
int gb_exec_x3_z4(struct gb *gb, byte op)
{
  addr address = READ16(REG(PC));
  byte y = OPCODE_Y(op);
  if(y < 4) {
    if(TABLE_CC[y](gb)) {
      PUSH(REG(PC));
      REG(PC) = address;
      gb->cycle += 12;
    }
    logf("CALL %s,0x%x",STR_CC[y], address);
    gb->cycle += 12;
  }
  else {
    return RET_FAILURE;
  }
  return RET_SUCCESS;
}



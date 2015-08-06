/* exec_05.c */
#include "gb_exec_x0_z5.h"

//Dec r[y]
int gb_exec_x0_z5(struct gb *gb, byte op)
{
  byte y = OPCODE_Y(op)
     , val;
  logf("DEC %s",STR_R[y]);
  //Set byte to given register or special case (HL)
  if(y==6) {
    val = READ(REG(HL));
    gb->cycle += 8;
  }
  else {
    val = REG(r8[TABLE_R[y]]);
  }

  //Clear Subtract flag
  SET_FLAG(FLAG_N);
  //Set HalfCarry flag
  CND_FLAG(FLAG_H, (val&0xF0)-1 < 0xF0);

  //decriment byte
  logf("|%u -> ", val);
  --val;
  logf("%u", val);
  if(y==6) { WRITE(REG(HL), val); }
  else     { REG(r8[TABLE_R[y]]) = val; }

  //Set Zero Flag
  CND_FLAG(FLAG_Z,val==0);

  gb->cycle += 4;
  return RET_SUCCESS;
}


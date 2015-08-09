/* exec_01.c */
#include "gb_exec_x0_z1.h"

//!LD rp[p], NN
/** Put 16 bit immediate value into TABLE_RP[p] register */
static int gb_exec_x0_z1_q0(struct gb*, byte);

//!ADD HL, n: where n = {BC, DE, HL, SP}
/**Add n to HL */
static int gb_exec_x0_z1_q1(struct gb*, byte);

int gb_exec_x0_z1(struct gb *gb, byte op)
{
  byte q = OPCODE_Q(op);
  logf("q%d|",q);
  switch(q) {
    case 0:return gb_exec_x0_z1_q0(gb,op);
    case 1:return gb_exec_x0_z1_q1(gb,op);
  }
  return RET_FAILURE;
}

//LD rp[p] nn
int gb_exec_x0_z1_q0(struct gb *gb, byte op)
{
  byte p = OPCODE_P(op);
  addr address = READ16(REG(PC));
  REG(PC) += 2;
  REG(r16[TABLE_RP[p]]) = address;

  logf("LD %s,0x%.4X", STR_RP[p], address);
  gb->cycle += 8;

  return RET_SUCCESS;
}

//ADD HL, rp[p]
int gb_exec_x0_z1_q1(struct gb *gb, byte op)
{
  byte p = OPCODE_P(op);
  //Clear Subtract flag
  CLR_FLAG(FLAG_N);
  addr *hl = &REG(HL),
       *rp = &REG(r16[TABLE_RP[p]]);
  //Set lower carry
  CND_FLAG(FLAG_H,(*hl&0x0FFF)+(*rp&0x0FFF) > 0x0FFF);
  //Set Upper carry
  CND_FLAG(FLAG_C,*hl+*rp > 0xFFFF);
  //Add values
  *hl += *rp;

  logf("ADD HL,%s",STR_RP[p]);

  gb->cycle += 8;
  return RET_SUCCESS;
}



/* exec_x3_z5.c */
# include "gb_exec_x3_z5.h"
//!PUSH rp2[p]
static int gb_exec_x3_z5_q0(struct gb*, byte);
//!Call a16
static int gb_exec_x3_z5_q1(struct gb*);

int gb_exec_x3_z5(struct gb *gb, byte opcode)
{
  if(OPCODE_Q(opcode) == 0)
    return gb_exec_x3_z5_q0(gb, opcode);
  if(OPCODE_P(opcode) == 0)
    return gb_exec_x3_z5_q1(gb);
  return RET_FAILURE;
}
//PUSH rp2[p]
int gb_exec_x3_z5_q0(struct gb *gb, byte opcode)
{
  byte p = OPCODE_P(opcode);

  PUSH(REG(r16[TABLE_RP2[p]]));

  logf("PUSH %s",STR_RP2[p]);

  gb->cycle += 16;
  return RET_SUCCESS;
}
//CALL a16
int gb_exec_x3_z5_q1(struct gb *gb)
{
  PUSH(REG(PC));
  addr address = READ16(REG(PC));
  REG(PC) = address;

  logf("CALL 0x%x",address);

  gb->cycle += 24;
  return RET_SUCCESS;
}

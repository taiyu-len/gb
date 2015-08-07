/* exec_x3_z1.c */
#include "gb_exec_x3_z1.h"

//!POP rp2[p]
static int gb_exec_x3_z1_q0(struct gb*, byte);
//!Switch for child functions
static int gb_exec_x3_z1_q1(struct gb*, byte);
//!C9: RET: Pop two bytes from stack & jump to that address
static int gb_exec_x3_z1_q1_p0(struct gb *gb);
//!D9: RETI: Same as RET, but enable interrupts
static int gb_exec_x3_z1_q1_p1(struct gb *gb);
//!E9: JP (HL) : jump to address contained in HL
static int gb_exec_x3_z1_q1_p2(struct gb *gb);
//!F9: LD SP,HL
static int gb_exec_x3_z1_q1_p3(struct gb *gb);


//Switch for child functions
int gb_exec_x3_z1(struct gb *gb, byte op)
{
  byte q = OPCODE_Q(op);

  logf("q%d|",q);

  switch(q) {
    case 0: return gb_exec_x3_z1_q0(gb,op);
    case 1: return gb_exec_x3_z1_q1(gb,op);
  }
  return RET_FAILURE;
}
//POP rp2[p]
int gb_exec_x3_z1_q0(struct gb *gb, byte op)
{
  byte p = OPCODE_P(op);

  logf("POP %s",STR_RP2[p]);

  REG(r16[TABLE_RP2[p]]) = POP();

  gb->cycle += 12;
  return RET_SUCCESS;
}
//Switch for child functions
int gb_exec_x3_z1_q1(struct gb *gb, byte op)
{
  byte p = OPCODE_P(op);

  logf("p%d|",p);
  switch(p) {
    case 0: return gb_exec_x3_z1_q1_p0(gb);
    case 1: return gb_exec_x3_z1_q1_p1(gb);
    case 2: return gb_exec_x3_z1_q1_p2(gb);
    case 3: return gb_exec_x3_z1_q1_p3(gb);
  }
  return RET_FAILURE;
}
//C9: RET
int gb_exec_x3_z1_q1_p0(struct gb *gb)
{
  logf("RET");
  REG(PC) = POP();
  gb->cycle += 16;
   return RET_SUCCESS;
}
//D9: RETI
int gb_exec_x3_z1_q1_p1(struct gb *gb)
{
  logf("RETI");
  gb->mem.ime = 0xFF;
  REG(PC) = POP();
  gb->cycle += 16;
  return RET_SUCCESS;
}
//E9: JP HL
int gb_exec_x3_z1_q1_p2(struct gb *gb)
{
  logf("JP HL");
  REG(PC) = REG(HL);
  gb->cycle += 4;
  return RET_SUCCESS;
}
//F9: LD SP,HL
int gb_exec_x3_z1_q1_p3(struct gb *gb)
{
  logf("LD SP,HL");
  REG(SP) = REG(HL);
  gb->cycle += 8;
  return RET_SUCCESS;
}


/* exec_x0_z2.c */
#include "gb_exec_x0_z2.h"

int gb_exec_x0_z2(struct gb *gb,byte op)
{
  logf("q%d|p%d|",OPCODE_Q(op),OPCODE_P(op));
  switch(OPCODE_Q(op)) {
    case 0:
      switch(OPCODE_P(op)) {
        case 0: return gb_exec_x0_z2_q0_p0(gb);
        case 1: return gb_exec_x0_z2_q0_p1(gb);
        case 2: return gb_exec_x0_z2_q0_p2(gb);
        case 3: return gb_exec_x0_z2_q0_p3(gb);
      }
    case 1:
      switch(OPCODE_P(op)){
        case 0: return gb_exec_x0_z2_q1_p0(gb);
        case 1: return gb_exec_x0_z2_q1_p1(gb);
        case 2: return gb_exec_x0_z2_q1_p2(gb);
        case 3: return gb_exec_x0_z2_q1_p3(gb);
      }
  }
  return RET_FAILURE;
}
//LD (BC), A
int gb_exec_x0_z2_q0_p0(struct gb *gb)
{
  logf("LD (BC),A");

  WRITE(REG(BC), REG(A));

  gb->cycle += 8;
  return RET_SUCCESS;
}
//LD (DE), A
int gb_exec_x0_z2_q0_p1(struct gb *gb)
{
  logf("LD (DE),A");

  WRITE(REG(DE), REG(A));

  gb->cycle += 8;
  return RET_SUCCESS;
}
//LDI (HL), A
int gb_exec_x0_z2_q0_p2(struct gb *gb)
{
  logf("LDI (HL),A");

  WRITE(REG(HL), REG(A));
  ++REG(HL);

  gb->cycle += 8;
  return RET_SUCCESS;
}
//LDD (HL),A
int gb_exec_x0_z2_q0_p3(struct gb *gb)
{
  logf("LDD (HL),A");

  WRITE(REG(HL), REG(A));
  --REG(HL);

  gb->cycle += 8;
  return RET_SUCCESS;
}
//LD A,(BC)
int gb_exec_x0_z2_q1_p0(struct gb *gb)
{
  logf("LD A, (BC)");

  REG(A) = READ(REG(BC));

  gb->cycle += 8;
  return RET_SUCCESS;
}
//LD A,(DE)
int gb_exec_x0_z2_q1_p1(struct gb *gb)
{
  logf("LD A,(DE)");

  REG(A) = READ(REG(DE));

  gb->cycle += 8;
  return RET_SUCCESS;
}
//LDI A,(HL)
int gb_exec_x0_z2_q1_p2(struct gb *gb)
{
  logf("LDI A,(HL)");

  REG(A) = READ(REG(HL));
  ++REG(HL);

  gb->cycle += 8;
  return RET_SUCCESS;
}
//LDD A,(HL)
int gb_exec_x0_z2_q1_p3(struct gb *gb)
{
  logf("LDD A,(HL)");

  REG(A) = READ(REG(HL)--);

  gb->cycle += 8;
  return RET_SUCCESS;
}


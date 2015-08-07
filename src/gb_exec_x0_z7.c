/* exec_07.c */
#include "gb_exec_x0_z7.h"
//!0xx0_z7:RLCA: rotate A left, old bit 7 to carry flag
static int gb_exec_x0_z7_y0(struct gb *gb);

//!0x0F:RRCA: rotate A right, old bit 0 to carry flag
static int gb_exec_x0_z7_y1(struct gb *gb);

//!0x17:RLA: rotate A left through carry flag
static int gb_exec_x0_z7_y2(struct gb *gb);

//!0x1F:RRA: rotate A right through carry flag
static int gb_exec_x0_z7_y3(struct gb *gb);

//!0x27:DAA: Decimal adjust register A.This instruction adjusts register A so
///     that the correct representation of binary coded decimal is obtained
static int gb_exec_x0_z7_y4(struct gb *gb);

//!0x2F:CPL: Complement A register (flip bits)
static int gb_exec_x0_z7_y5(struct gb *gb);

//!0x37:SCF: Set Carry Flag
static int gb_exec_x0_z7_y6(struct gb *gb);

//!0x3F:CCF: Complement Carry Flag
static int gb_exec_x0_z7_y7(struct gb *gb);

int gb_exec_x0_z7(struct gb *gb, byte op)
{
  byte y = OPCODE_Y(op);
  logf("y%d",y);
  switch(y) {
    case 0: return gb_exec_x0_z7_y0(gb);
    case 1: return gb_exec_x0_z7_y1(gb);
    case 2: return gb_exec_x0_z7_y2(gb);
    case 3: return gb_exec_x0_z7_y3(gb);
    case 4: return gb_exec_x0_z7_y4(gb);
    case 5: return gb_exec_x0_z7_y5(gb);
    case 6: return gb_exec_x0_z7_y6(gb);
    case 7: return gb_exec_x0_z7_y7(gb);
  }
  return RET_FAILURE;
}
//0x07:RLCA
int gb_exec_x0_z7_y0(struct gb *gb)
{
  logf("RLCA");

  CLR_FLAG(FLAG_H);
  CLR_FLAG(FLAG_N);
  CLR_FLAG(FLAG_Z);
  CND_FLAG(FLAG_C, REG(A) >> 7);
  __asm__ __volatile__(
      "rolb $1, %0"
    : "=r" (REG(A))
    : "r"  (REG(A)));

  gb->cycle += 4;
  return RET_SUCCESS;
}
//0x0F:RRCA
int gb_exec_x0_z7_y1(struct gb *gb)
{
  logf("RRCA");
  CLR_FLAG(FLAG_H);
  CLR_FLAG(FLAG_N);
  CLR_FLAG(FLAG_Z);
  //Store 0th bit in Carry flag
  CND_FLAG(FLAG_C, REG(A) & 1);
  //ror register A
  __asm__ __volatile__(
      "rorb $0x01, %0"
      : "=r" (REG(A))
      : "r"  (REG(A))
  );

  gb->cycle += 4;
  return RET_SUCCESS;
}
//0x17:RLA
int gb_exec_x0_z7_y2(struct gb *gb)
{
  logf("RLA");

  byte carry_flag = GET_FLAG(FLAG_C);
  CLR_FLAG(FLAG_H);
  CLR_FLAG(FLAG_N);
  CLR_FLAG(FLAG_Z);
  //Store 7th bit in Carry flag
  CND_FLAG(FLAG_C, REG(A) >> 7);
  //Roll and add back old carry flag into it
  REG(A) <<= 1;
  REG(A) |= carry_flag;
  gb->cycle += 4;
  return RET_SUCCESS;
}
//0x1F:RRA
int gb_exec_x0_z7_y3(struct gb *gb)
{
  logf("RRA");

  byte carry_flag = GET_FLAG(FLAG_C);
  CLR_FLAG(FLAG_H);
  CLR_FLAG(FLAG_N);
  CLR_FLAG(FLAG_Z);
  //Store 7th bit in Carry flag
  CND_FLAG(FLAG_C,REG(A) & 1);
  //Roll and add back old carry flag into it
  REG(A) >>= 1;
  REG(A) |= carry_flag << 7;

  gb->cycle += 4;
  return RET_SUCCESS;
}
//0x27:DAA
int gb_exec_x0_z7_y4(struct gb *gb)
{
  logf("DAA");

  if((REG(A)& 0xF) > 9 || GET_FLAG(FLAG_H)) {
    REG(A) += 0x06;
  }
  //Check for second Carry
  if((REG(A) >> 4) > 9 || GET_FLAG(FLAG_C)) {
    REG(A) += 0x60;
    SET_FLAG(FLAG_C);
  }
  else {
    CLR_FLAG(FLAG_C);
  }
  //Set flag Z to 1 if zero
  CND_FLAG(FLAG_Z,REG(A) == 0);

  //Print binary encoded value
  logf("%d%d",REG(A)>>4,REG(A)&0xF);

  gb->cycle += 4;
  return RET_SUCCESS;
}
//0x2F:CPL
int gb_exec_x0_z7_y5(struct gb *gb)
{
  logf("CPL");

  REG(A) = ~REG(A);
  SET_FLAG(FLAG_N);
  SET_FLAG(FLAG_H);

  gb->cycle += 4;
  return RET_SUCCESS;
}
//0x37:SCF
int gb_exec_x0_z7_y6(struct gb *gb)
{
  logf("SCF");

  SET_FLAG(FLAG_C);
  CLR_FLAG(FLAG_N);
  CLR_FLAG(FLAG_H);

  gb->cycle += 4;
  return RET_SUCCESS;
}
//0x3F:CCF
int gb_exec_x0_z7_y7(struct gb *gb)
{
  logf("CCF");
  //Flip C flag
  CPL_FLAG(FLAG_C);
  CLR_FLAG(FLAG_N);
  CLR_FLAG(FLAG_H);

  gb->cycle += 4;
  return RET_SUCCESS;
}


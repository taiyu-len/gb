/* exec_x3_z0.c */
# include "gb_exec_x3_z0.h"
# include "gb_io.h"

//!E0:LDH (a8), A
static int gb_exec_x3_z0_y4(struct gb *);
//!E8:ADD SP, r8
static int gb_exec_x3_z0_y5(struct gb *);
//!F0:LDH A,(a8)
static int gb_exec_x3_z0_y6(struct gb *);
//!F8:LD HL, SP+r8
static int gb_exec_x3_z0_y7(struct gb *);

int gb_exec_x3_z0(struct gb *gb, byte op)
{
  byte y = OPCODE_Y(op);

  //Conditional
  if(y < 4) {
    logf("RET %s",STR_CC[y]);

    gb->cycle += 8;
    //Return if condition is true
    if(TABLE_CC[y](gb)) {
      //Pop 2 bytes from address for stackpointer and jump to it
      REG(PC) = POP();
      gb->cycle += 12;
    }
  }
  //GAMEBOY Specific functions
  else {
    logf("y%d|",y);
    switch(y - 4) {
      case 0: return gb_exec_x3_z0_y4(gb);
      case 1: return gb_exec_x3_z0_y5(gb);
      case 2: return gb_exec_x3_z0_y6(gb);
      case 3: return gb_exec_x3_z0_y7(gb);
    }
  }
  return RET_SUCCESS;
}

//E0:LDH (a8), A
//Put A into memory address 0xFF00 + 8bit immediate value
int gb_exec_x3_z0_y4(struct gb *gb)
{
  byte addr = READ(REG(PC)++);
  logf("LDH (0xFF%.2x),A|A=%.2x|IO : %s", addr, REG(A), gb_io_str[addr]);

  WRITE(0xFF00 + addr, REG(A));

  gb->cycle += 12;
  return RET_SUCCESS;
}
//E8:ADD SP, r8
int gb_exec_x3_z0_y5(struct gb *gb)
{
  signed char offset = READ(REG(PC)++);
  //Set Half and full carry flag
  CLR_FLAG(FLAG_Z);
  CLR_FLAG(FLAG_N);
  CND_FLAG(FLAG_H,(REG(SP)&0x0FFF) + offset > 0x0FFF);
  CND_FLAG(FLAG_C,(REG(SP)+offset > 0xFFFF));
  REG(SP) += offset;

  logf("ADD SP,%d",offset);
  gb->cycle += 16;
  return RET_SUCCESS;
}
//F0:LDH A,(a8)
int gb_exec_x3_z0_y6(struct gb *gb)
{
  byte addr = READ(REG(PC)++);
  REG(A) = READ(0xFF00 + addr);

  logf("LDH A,(0xFF%.2x)|A=%.2x|IO : %s",addr,REG(A)
      , gb_io_str[addr] ? gb_io_str[addr]
        : addr > 0x80   ? "stack"
        :                 "unknown io_port");

  gb->cycle += 12;
  return RET_SUCCESS;
}
//F8:LD HL, SP+r8
int gb_exec_x3_z0_y7(struct gb *gb)
{
  signed char offset = READ(REG(PC)++);
  CLR_FLAG(FLAG_Z);
  CLR_FLAG(FLAG_N);
  //Set Carry bits
  CND_FLAG(FLAG_H,(REG(SP)&0x0FFF) + offset > 0x0FFF);
  CND_FLAG(FLAG_C,(REG(SP)+offset > 0xFFFF));
  REG(HL) = REG(SP) + offset;

  logf("LD HL,SP+%d",offset);

  gb->cycle += 12;
  return RET_SUCCESS;
}


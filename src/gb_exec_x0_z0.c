/* exec_x0_z0.c */
#include "gb_exec_x0_z0.h"

//!0x00:NOP
/**Do nothing for this cycle */
static int gb_exec_x0_z0_y0(struct gb*);

//!0x08:LD (a16), SP
/**Put stack pointer at address nn */
static int gb_exec_x0_z0_y1(struct gb*);

//!0x10:STOP
/**Halt processor & screen until button press.*/
static int gb_exec_x0_z0_y2(struct gb*);

//!0x18: JR r8
/** Add n to current address and jump to it*/
static int gb_exec_x0_z0_y3(struct gb*);

//!0x20|28|30|38:JR (NZ|Z|NC|C) r8
/** Add immediate byte to address if condition is true */
static int gb_exec_x0_z0_y47(struct gb *, byte op);


int gb_exec_x0_z0(struct gb *gb, byte op)
{
  byte y = OPCODE_Y(op);
  logf("y%d|",y);
  switch(y)
  {
    case 0 : return gb_exec_x0_z0_y0 (gb);
    case 1 : return gb_exec_x0_z0_y1 (gb);
    case 2 : return gb_exec_x0_z0_y2 (gb);
    case 3 : return gb_exec_x0_z0_y3 (gb);
    default: return gb_exec_x0_z0_y47(gb,op);
  }
}

//0x00:NOP
int gb_exec_x0_z0_y0(struct gb *gb)
{
  //Logging
  logf("NOP");
  gb->cycle += 4;
  return RET_SUCCESS;
}
//0x08:LD (a16), SP
int gb_exec_x0_z0_y1(struct gb *gb)
{
  addr im = READ16(REG(PC));
  REG(PC) += 2;

  logf("LD (%4x),SP | SP=%.4x", im, REG(SP));
  WRITE16(im, REG(SP));
  gb->cycle += 20;
  return RET_SUCCESS;
}
//0x10:STOP
int gb_exec_x0_z0_y2(struct gb *gb)
{
  logf("STOP");
  gb->stop   = 1;
  gb->cycle += 4;
  return RET_SUCCESS;
}
//0x18: JR r8
int gb_exec_x0_z0_y3(struct gb *gb)
{
  signed char offset = READ(REG(PC));
  ++REG(PC);

  logf("JR %d",offset);
  //jump relative to initial PC.
  REG(PC) += offset;
  gb->cycle += 12;
  return RET_SUCCESS;
}
//0x20|28|30|38: JR cc r8
int gb_exec_x0_z0_y47(struct gb *gb, byte op)
{
  signed char offset = READ(REG(PC));
  ++REG(PC);

  byte y = OPCODE_Y(op) - 4;
  logf("JR %s,%d", STR_CC[y], offset);
  //Jump if condition is true
  if(TABLE_CC[y](gb)) {
    //jump relative to initial PC.
    REG(PC) += offset;
    gb->cycle += 4;
  }
  gb->cycle += 8;
  return RET_SUCCESS;
}


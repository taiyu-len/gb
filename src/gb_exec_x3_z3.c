/* exec_x3_z3.c */
#include "gb_exec_x3_z3.h"
#include "gb_exec_cb.h"

//Switch for child functions
int gb_exec_x3_z3(struct gb *gb, byte op)
{
  byte y = OPCODE_Y(op);
  logf("y%d|",y);
  switch(y) {
    case 0: return gb_exec_x3_z3_y0(gb);
    case 1: return gb_exec_x3_z3_y1(gb);
    case 2: //Invalid opcode
    case 3: //Invalid opcode
    case 4: //invalid opcode
    case 5: return RET_FAILURE;
    case 6: return gb_exec_x3_z3_y6(gb);
    case 7: return gb_exec_x3_z3_y7(gb);
  }
  return RET_FAILURE;
}
//C3:JP a16: Jump to immiate 16 bit address
int gb_exec_x3_z3_y0(struct gb *gb)
{
  REG(PC) = READ16(REG(PC));

  logf("JP 0x%x", REG(PC));

  gb->cycle += 16;
  return RET_SUCCESS;
}
//CB:Prefix:  Prefix Call for doing bitwise operators
int gb_exec_x3_z3_y1(struct gb *gb)
{
  byte opcode = READ(REG(PC)++);

  logf("CB|");

  gb->cycle += 4;
  return gb_exec_cb(gb,opcode);
}
//F3:DI:
int gb_exec_x3_z3_y6(struct gb *gb)
{
  //Disable interrupts. clear bits
  logf("DI");

  WRITE(IO_IE, 0);

  gb->cycle += 4;
  return RET_SUCCESS;
}
//F8:EI
int gb_exec_x3_z3_y7(struct gb *gb)
{
  //Inable Interrupts. 0,1,2,3,4 bits set
  logf("EI");

  WRITE(IO_IE, 0x1F);

  gb->cycle += 4;
  return RET_SUCCESS;
}



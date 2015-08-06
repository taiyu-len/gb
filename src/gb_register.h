/**\file   gb_register.h */
# ifndef  _GB_REGISTER_H
# define  _GB_REGISTER_H
# include "gb_common.h"

//!Register union type.
union gb_register {
  //!8Bit registers
  byte r8[12];
  //!16Bit registers
  addr r16[6];
  //!Named 8bit registers, dependent on byte ordering
  struct {
    byte
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
      F, A,
      C, B,
      E, D,
      L, H;
#else
      A, F,
      B, C,
      D, E,
      H, L;
#endif
  };
  //!Named 16Bit registers
  struct {
    addr
      AF, BC,
      DE, HL,
      SP, PC;
  };
};

/**initialize registers.
 * @param gb*/
void gb_register_init (struct gb*);

//!Register index
enum REG_INDEX
{
//8Bit registers
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  REG_F  = 0x00, REG_A  = 0x01,
  REG_C  = 0x02, REG_B  = 0x03,
  REG_E  = 0x04, REG_D  = 0x05,
  REG_L  = 0x06, REG_H  = 0x07,
#elif
  REG_A  = 0x00, REG_F  = 0x01,
  REG_B  = 0x02, REG_C  = 0x03,
  REG_D  = 0x04, REG_E  = 0x05,
  REG_H  = 0x06, REG_L  = 0x07
#endif
//16Bit registers
  REG_AF = 0x00,
  REG_BC = 0x01,
  REG_DE = 0x02,
  REG_HL = 0x03,
  REG_SP = 0x04,
  REG_PC = 0x05,
};

enum REG_FLAG
{
  FLAG_Z = 0x07,
  FLAG_N = 0x06,
  FLAG_H = 0x05,
  FLAG_C = 0x04
};
//Macros
//Read register
# define REG(NAME) gb->reg.NAME
# define SET_FLAG(FLAG) (REG(F) |=  (1 << (FLAG)))
# define CLR_FLAG(FLAG) (REG(F) &= ~(1 << (FLAG)))
# define CPL_FLAG(FLAG) (REG(F) ^=  (1 << (FLAG)))
# define GET_FLAG(FLAG) (REG(F) &   (1 << (FLAG)))
# define CND_FLAG(FLAG,BOOL) ((BOOL)?SET_FLAG(FLAG):CLR_FLAG(FLAG))


# endif /*_GB_REGISTER_H*/


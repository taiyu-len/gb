/*!@file   gb_exec_tables.h */
# ifndef  _GB_EXEC_TABLES_H
# define  _GB_EXEC_TABLES_H
# include "gb_common.h"
# include "gb_register.h"

//! Returns register location for table
/** Usage:
 *  ~~~~~~~~~~~~~~~~~~~~~~~~
 *  byte *b;
 *  if(n==6) b = MEM_byte(REG(HL));
 *  else     b = REG(r16[TABLE_R[n]]);
 *  ~~~~~~~~~~~~~~~~~~~~~~~~
 *  0:B, 1:C, 2:D   , 3:E
 *  4:H, 5:L, 6:(HL), 7:A*/
extern enum REG_INDEX const TABLE_R[8];
extern char const *STR_R[8];

//! Register Pairs featuring SP
/** Usage
 *  ~~~~~~~~
 *  REG(r16[TABLE_RP[n]]);
 *  ~~~~~~~~*/
extern enum REG_INDEX const TABLE_RP[4];
extern char const *STR_RP[4];

//! Register Pairs features AF
/** Usage
 *  ~~~~~~~~
 *  REG(r16[TABLE_RP2[n]]);
 *  ~~~~~~~~
 *  TABLE_RP2[0] = REG_BC
 *  TABLE_RP2[1] = REG_DE
 *  TABLE_RP2[2] = REG_HL
 *  TABLE_RP2[3] = REG_AF */
extern enum REG_INDEX const TABLE_RP2[4];
extern char const *STR_RP2[4];

//! Conditions table
/** Usage:
 *  ~~~~~~~~~~~~~~~~~~~~~~~
 *  if(TABLE_CC[y](gb)) do_whatever();
 *  ~~~~~~~~~~~~~~~~~~~~~~~
 *  TABLE_CC[0] = NZ;
 *  TABLE_CC[1] = Z;
 *  TABLE_CC[2] = NC;
 *  TABLE_CC[3] = C; */
extern int (*const TABLE_CC[4])(struct gb*);
extern char const *STR_CC[4];

//! Arithmetic/Logic Operation Table
/**Usage:
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~
 * TABLE_ALU[n](gb, byte);
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~
 * TABLE_ALU[0] = ADD A, byte
 * TABLE_ALU[1] = ADC A, byte
 * TABLE_ALU[2] = SUB byte
 * TABLE_ALU[3] = SBC A, byte
 * TABLE_ALU[4] = AND byte
 * TABLE_ALU[5] = XOR byte
 * TABLE_ALU[6] = OR byte
 * TABLE_ALU[7] = CP byte */
extern void (*const TABLE_ALU[8])(struct gb*, byte);
extern char const *STR_ALU[8];

//! Rotation table
/**~~~~~~~~~~~~~~~~~~~~~~~~
 * TABLE_ROT[y](gb, opcode);
 * ~~~~~~~~~~~~~~~~~~~~~~~~
 * TABLE_ROT[0] = RLC
 * TABLE_ROT[1] = RRC
 * TABLE_ROT[2] = RL
 * TABLE_ROT[3] = RR
 * TABLE_ROT[4] = SLA
 * TABLE_ROT[5] = SRA
 * TABLE_ROT[6] = SWAP
 * TABLE_ROT[7] = SRL */
extern void (*const TABLE_ROT[8])(struct gb*, byte);
extern char const *STR_ROT[8];

# endif /*_GB_EXEC_TABLES_H*/


/*!@file   gb_exec.h
 * for executing opcodes */
# ifndef  _GB_EXEC_H
# define  _GB_EXEC_H
# include "gb_common.h"
# include "gb_exec_tables.h"
# include "gb.h"

/**execute opcode onto gameboy.
 * @param gb
 * @param opcode to execute */
int gb_exec(struct gb *,byte);

#define OPCODE_X(OP) ((OP & 0b11000000) >> 6)
#define OPCODE_Y(OP) ((OP & 0b00111000) >> 3)
#define OPCODE_Z(OP) ((OP & 0b00000111) >> 0)
#define OPCODE_P(OP) ((OP & 0b00110000) >> 4)
#define OPCODE_Q(OP) ((OP & 0b00001000) >> 3)

# endif /*_GB_EXEC_H*/


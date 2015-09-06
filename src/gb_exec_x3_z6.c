/* exec_x3_z6.c */
#include "gb_exec_x3_z6.h"

//ALU[y] a8
int gb_exec_x3_z6(struct gb *gb, byte op)
{
	byte y = OPCODE_Y(op);
	byte b = READ(REG(PC)++);

	logf("%s 0x%x",STR_ALU[y], b);

	gb->cycle += 8;

	TABLE_ALU[y](gb, b);
	return RET_SUCCESS;
}



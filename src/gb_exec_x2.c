/* exec_x2.c */
#include "gb_exec_x2.h"

//alu[y] r[z]
int gb_exec_x2(struct gb *gb, byte op)
{
	byte y = OPCODE_Y(op),
			 z = OPCODE_Z(op);

	logf("%s %s",STR_ALU[y], STR_R[z]);

	//Special case of (HL)
	if(z==6) {
		TABLE_ALU[y](gb, READ(REG(HL)));
		gb->cycle += 4;
	}
	else {
		TABLE_ALU[y](gb, REG(r8[TABLE_R[z]]));
	}

	gb->cycle += 4;
	return RET_SUCCESS;
}


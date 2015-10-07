/* exec_06.c */
#include "gb_exec_x0_z6.h"

//LD r[y], a8
int gb_exec_x0_z6(struct gb *gb, byte op)
{
	byte a8 = READ(REG(PC)++)
		 , y = OPCODE_Y(op);

	logf("LD %s,0x%x",STR_R[y], a8);
	//Special case of loading into memory (HL)
	if (y==6) {
		 WRITE(REG(HL), a8);
		 gb->cycle += 4;
	}
	else {
		REG(r8[TABLE_R[y]]) = a8;
	}
	//Set memory
	gb->cycle += 8;
	return RET_SUCCESS;
}


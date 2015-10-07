/* exec_04.c */
#include "gb_exec_x0_z4.h"
#include "gb_exec_tables.h"

//INC r[y]
int gb_exec_x0_z4(struct gb *gb, byte op)
{
	byte y = OPCODE_Y(op)
		 , val;

	logf("INC %s",STR_R[y]);

	//Set byte to given register or special case (HL)
	if (y==6) {
		val = READ(REG(HL));
		gb->cycle += 8;
	}
	else {
		val = REG(r8[TABLE_R[y]]);
	}
	//Clear Subtract flag
	CLR_FLAG(FLAG_N);

	//Set HalfCarry flag
	CND_FLAG(FLAG_H, (val & 0xF) + 1 > 0xF);
	//Set FullCarry flag
	CND_FLAG(FLAG_C, val + 1 > 0xFF);

	//Increment byte
	++val;
	if (y == 6){ WRITE(REG(HL), val); }
	else      { REG(r8[TABLE_R[y]]) = val; }

	CND_FLAG(FLAG_Z,val == 0);

	gb->cycle += 4;
	return RET_SUCCESS;
}


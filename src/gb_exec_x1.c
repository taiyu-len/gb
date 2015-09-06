/* exec_x1.c */
#include "gb_exec_x1.h"

static
int gb_exec_x1_z6(struct gb*);

//LD r[y], r[z]; 8bit load
int gb_exec_x1(struct gb *gb, byte op)
{
	//All operations use at least 4, (HL) uses 8
	gb->cycle += 4;

	byte y = OPCODE_Y(op),
			 z = OPCODE_Z(op);

	logf("LD %s,%s", STR_R[y], STR_R[z]);

	//in case of y=z=6, call HALT. otherwise NOP
	if(y==z) return z==6 ? gb_exec_x1_z6(gb)
											 : RET_SUCCESS;
	//Case|LD (HL),R
	if(y == 6) {
		WRITE(REG(HL), REG(r8[TABLE_R[z]]));
		gb->cycle += 4;
	}
	//Case|LD R,(HL)
	else if(z == 6) {
		REG(r8[TABLE_R[y]]) = READ(REG(HL));
		gb->cycle += 4;
	}
	//Case LD, R,R
	else {
		REG(r8[TABLE_R[y]]) = REG(r8[TABLE_R[z]]);
	}

	return RET_SUCCESS;
}

//0x76:HALT
int gb_exec_x1_z6(struct gb *gb)
{
	gb->halt = 1;
	logf("|HALT");
	return RET_SUCCESS;
}


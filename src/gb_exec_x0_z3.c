/* exec_03.c */
#include "gb_exec_x0_z3.h"
//!INC rp[p]
/** Increment 16bit Register p */
static int gb_exec_x0_z3_q0(struct gb*, byte);

//!DEC rp[p]
/** Decrement 16bit Register p */
static int gb_exec_x0_z3_q1(struct gb*, byte);

int gb_exec_x0_z3(struct gb *gb, byte op)
{
	logf("q%d|",OPCODE_Q(op));
	switch(OPCODE_Q(op)) {
		case 0:return gb_exec_x0_z3_q0(gb, op);
		case 1:return gb_exec_x0_z3_q1(gb, op);
	}
	return RET_FAILURE;
}

//INC rp[p]
int gb_exec_x0_z3_q0(struct gb *gb, byte op)
{
	op = OPCODE_P(op);
	logf("INC %s",STR_RP[op]);

	++REG(r16[TABLE_RP[op]]);

	gb->cycle += 8;
	return RET_SUCCESS;
}
//Dec rp[p]
int gb_exec_x0_z3_q1(struct gb *gb, byte op)
{
	op = OPCODE_P(op);
	logf("DEC %s",STR_RP[op]);

	--REG(r16[TABLE_RP[op]]);

	gb->cycle += 8;
	return RET_SUCCESS;
}


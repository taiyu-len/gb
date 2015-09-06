/* exec_x3.c */
#include "gb_exec_x3.h"
#include "gb_exec_x3_z0.h"
#include "gb_exec_x3_z1.h"
#include "gb_exec_x3_z2.h"
#include "gb_exec_x3_z3.h"
#include "gb_exec_x3_z4.h"
#include "gb_exec_x3_z5.h"
#include "gb_exec_x3_z6.h"
#include "gb_exec_x3_z7.h"

int gb_exec_x3(struct gb *gb, byte op)
{
	byte z = OPCODE_Z(op);
	logf("z%d|",z);
	switch(z)
	{
		case 0: return gb_exec_x3_z0(gb, op);
		case 1: return gb_exec_x3_z1(gb, op);
		case 2: return gb_exec_x3_z2(gb, op);
		case 3: return gb_exec_x3_z3(gb, op);
		case 4: return gb_exec_x3_z4(gb, op);
		case 5: return gb_exec_x3_z5(gb, op);
		case 6: return gb_exec_x3_z6(gb, op);
		case 7: return gb_exec_x3_z7(gb, op);
	}
	return RET_FAILURE;
}



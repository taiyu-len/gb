/* gb_exec.c */
# include "gb_exec.h"
# include "gb_exec_x0.h"
# include "gb_exec_x1.h"
# include "gb_exec_x2.h"
# include "gb_exec_x3.h"

int gb_exec(struct gb *gb,byte opcode)
{
	int retval = RET_FAILURE;
	logf("op=%.2x|x%u|",opcode, OPCODE_X(opcode));
	switch (OPCODE_X(opcode)) {
		case 0: retval = gb_exec_x0(gb, opcode); break;
		case 1: retval = gb_exec_x1(gb, opcode); break;
		case 2: retval = gb_exec_x2(gb, opcode); break;
		case 3: retval = gb_exec_x3(gb, opcode); break;
	}
	logf("\n");
	return retval;
}


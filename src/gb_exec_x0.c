/* gb_exec_x0.c */
# include "gb_exec_x0.h"
# include "gb_exec_x0_z0.h"
# include "gb_exec_x0_z1.h"
# include "gb_exec_x0_z2.h"
# include "gb_exec_x0_z3.h"
# include "gb_exec_x0_z4.h"
# include "gb_exec_x0_z5.h"
# include "gb_exec_x0_z6.h"
# include "gb_exec_x0_z7.h"

int gb_exec_x0(struct gb *gb,byte opcode)
{
	logf("z%d|",OPCODE_Z(opcode));
	switch (OPCODE_Z(opcode))
	{
		case 0: return gb_exec_x0_z0(gb,opcode);
		case 1: return gb_exec_x0_z1(gb,opcode);
		case 2: return gb_exec_x0_z2(gb,opcode);
		case 3: return gb_exec_x0_z3(gb,opcode);
		case 4: return gb_exec_x0_z4(gb,opcode);
		case 5: return gb_exec_x0_z5(gb,opcode);
		case 6: return gb_exec_x0_z6(gb,opcode);
		case 7: return gb_exec_x0_z7(gb,opcode);
	}
	return RET_FAILURE;
}



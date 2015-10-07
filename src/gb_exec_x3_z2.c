/* exec_x3_z2.c */
#include "gb_exec_x3_z2.h"

int gb_exec_x3_z2(struct gb *gb, byte op)
{
	//Get 16bit immediate values
	addr address = READ16(REG(PC));

	byte y = OPCODE_Y(op);
	logf("y%d|",y);
	switch (y) {
	case 0:
	case 1:
	case 2:
	case 3:
		logf("JP %s,0x%x",STR_CC[y], address);
		REG(PC) += 2;
		gb->cycle += 12;
		if (TABLE_CC[y](gb)) {
			REG(PC) = address;
			gb->cycle += 4;
		}
		break;

	case 4:
		logf("LD (C),A");
		WRITE(REG(C), REG(A));
		gb->cycle += 8;
		break;

	case 5:
		logf("LD (%.4x),A",address);
		REG(PC) += 2;
		WRITE(address, REG(A));
		gb->cycle += 16;
		break;

	case 6:
		logf("LD A,(C)");
		REG(A) = READ(REG(C));
		gb->cycle += 8;
		break;

	case 7:
		logf("LD A,(%.4x)",address);
		REG(PC) += 2;
		REG(A) = READ(address);
		gb->cycle += 8;
		break;
	}
	return RET_SUCCESS;
}


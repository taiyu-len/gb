/* exec_cb.c */
#include "gb_exec_cb.h"
int gb_exec_cb(struct gb *gb, byte opcode)
{
	byte x = OPCODE_X(opcode);
	logf("x%d|",x);
	switch(x) {
		case 0: return gb_exec_cb_x0(gb, opcode);
		case 1: return gb_exec_cb_x1(gb, opcode);
		case 2: return gb_exec_cb_x2(gb, opcode);
		case 3: return gb_exec_cb_x3(gb, opcode);
	}
	return RET_FAILURE;
}
//rot[y] r[z]
int gb_exec_cb_x0(struct gb *gb, byte op)
{
	logf("%s %s",STR_ROT[OPCODE_Y(op)], STR_R[OPCODE_Z(op)]);

	gb->cycle += 8;
	if(OPCODE_Z(op) == 6)
		gb->cycle += 8;

	TABLE_ROT[OPCODE_Y(op)](gb, op);
	return RET_SUCCESS;
}
# define GETVAL(V)\
	if(z==6) {V=READ(REG(HL));}\
	else     {V=REG(r8[TABLE_R[z]]);}
# define SETVAL(V)\
	if(z==6) {WRITE(REG(HL), V);}\
	else     {REG(r8[TABLE_R[z]])=V;}
//BIT y, r[z]
int gb_exec_cb_x1(struct gb *gb, byte op)
{
	byte val
		 , y = OPCODE_Y(op)
		 , z = OPCODE_Z(op);
	GETVAL(val);
	CLR_FLAG(FLAG_N);
	SET_FLAG(FLAG_H);
	CND_FLAG(FLAG_Z, val & (1 << y));

	logf("BIT %d,%s",y,STR_R[z]);

	gb->cycle += 8;
	if(z==6) gb->cycle += 8;

	return RET_SUCCESS;
}
//RES y, r[z]
int gb_exec_cb_x2(struct gb *gb, byte op)
{
	byte val
		 , y = OPCODE_Y(op)
		 , z = OPCODE_Z(op);
	GETVAL(val);
	//clear yth bit
	val &= ~(1 << y);
	SETVAL(val);

	logf("RES %d,%s",y,STR_R[z]);

	gb->cycle += 8;
	if(z==6) gb->cycle += 8;

	return RET_SUCCESS;
}
//SET y, r[z]
int gb_exec_cb_x3(struct gb *gb, byte op)
{
	byte val
		 , y = OPCODE_Y(op)
		 , z = OPCODE_Z(op);
	GETVAL(val);
	//set yth bit
	val |= 1 << y;
	SETVAL(val);

	logf("SET %d,%s",y,STR_R[z]);

	gb->cycle += 8;
	if(z==6) gb->cycle += 8;

	return RET_SUCCESS;
}



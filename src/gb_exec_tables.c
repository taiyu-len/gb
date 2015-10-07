/* exec_opcode_tables.c */
# include "gb.h"

enum REG_INDEX const TABLE_R[8] =
{
	REG_B, REG_C,
	REG_D, REG_E,
	REG_H, REG_L,
	REG_H, REG_A
};
char const *STR_R[8] = {"B", "C", "D", "E", "H", "L", "(HL)", "A"};

enum REG_INDEX const TABLE_RP[4] =
{
	REG_BC, REG_DE,
	REG_HL, REG_SP
};
char const *STR_RP[4] = { "BC", "DE", "HL", "SP" };


enum REG_INDEX const TABLE_RP2[4] =
{
	REG_BC,
	REG_DE,
	REG_HL,
	REG_AF
};
char const *STR_RP2[4] = { "BC", "DE", "HL", "AF" };


int TABLE_CC_NZ(struct gb *gb) { return !GET_FLAG(FLAG_Z); }
int TABLE_CC_Z (struct gb *gb) { return  GET_FLAG(FLAG_Z); }
int TABLE_CC_NC(struct gb *gb) { return !GET_FLAG(FLAG_C); }
int TABLE_CC_C (struct gb *gb) { return  GET_FLAG(FLAG_C); }

int (*const TABLE_CC[])(struct gb *) =
{
	TABLE_CC_NZ,
	TABLE_CC_Z,
	TABLE_CC_NZ,
	TABLE_CC_C
};
char const *STR_CC[4] = {"NZ","Z","NC","C"};

void TABLE_ALU_ADD(struct gb *gb, byte b)
{
	//Clear Subtraction Flag
	CLR_FLAG(FLAG_N);

	//Set Half Carry flag
	CND_FLAG(FLAG_H, (REG(A) & 0xF) + (b & 0xF) > 0xF);

	//Set Full Carry flag
	CND_FLAG(FLAG_C, REG(A) + b > 0xFF);

	//add n to register A
	REG(A) += b;

	//Set if result is zero
	CND_FLAG(FLAG_Z, REG(A)==0);
}
void TABLE_ALU_ADC(struct gb *gb, byte b)
{
	//get carry flag
	byte cf = GET_FLAG(FLAG_C);

	//Clear Subtraction Flag
	CLR_FLAG(FLAG_N);

	//Set Half Carry flag
	CND_FLAG(FLAG_H, (REG(A)&0xF) + b + cf > 0xF);

	//Set Full Carry flag
	CND_FLAG(FLAG_C, REG(A) + b + cf > 0xFF);

	//add n to register A
	REG(A) += b + cf;

	//Set if result is zero
	CND_FLAG(FLAG_Z, REG(A)==0);
}
void TABLE_ALU_SUB(struct gb *gb, byte b)
{
	//set Subtraction Flag
	SET_FLAG(FLAG_N);

	//Set Half Carry flag
	CND_FLAG(FLAG_H, (REG(A) & 0xF) < (b & 0xF));

	//Set Full Carry flag
	CND_FLAG(FLAG_C, REG(A) < b);

	//subtract n to register A
	REG(A) -= b;

	//Set if result is zero
	CND_FLAG(FLAG_Z, REG(A) == 0);
}
void TABLE_ALU_SBC(struct gb *gb, byte b)
{
	byte fc = GET_FLAG(FLAG_C);

	//set Subtraction Flag
	SET_FLAG(FLAG_N);

	//Set Half Carry flag
	CND_FLAG(FLAG_H, (REG(A) & 0xF) < (b & 0xF) + fc);

	//Set Full Carry flag
	CND_FLAG(FLAG_C, REG(A) < b + fc);

	//subtract n from register A
	REG(A) -= b + fc;

	//Set if result is zero
	CND_FLAG(FLAG_Z, REG(A) == 0);
}
void TABLE_ALU_AND(struct gb *gb, byte b)
{
	REG(A) &= b;
	//Set flags
	CND_FLAG(FLAG_Z, REG(A) == 0);
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_C);
	SET_FLAG(FLAG_H);
}
void TABLE_ALU_XOR(struct gb *gb, byte b)
{
	REG(A) ^= b;
	//Set flags
	CND_FLAG(FLAG_Z, REG(A) == 0);
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_C);
	CLR_FLAG(FLAG_H);
}
void TABLE_ALU_OR (struct gb *gb, byte b)
{
	REG(A) |= b;
	//Set flags
	CND_FLAG(FLAG_Z,REG(A) == 0);
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_C);
	CLR_FLAG(FLAG_H);
}
void TABLE_ALU_CP (struct gb *gb, byte b)
{
	//Set Subtraction Flag
	SET_FLAG(FLAG_N);

	//Set Half Carry flag
	CND_FLAG(FLAG_H,(REG(A)&0xF) < b);

	//Set Full Carry flag
	CND_FLAG(FLAG_C, REG(A) < b);

	//Set Zero flag if REG_A==byte
	CND_FLAG(FLAG_Z, REG(A) == b);
}

void(*const TABLE_ALU[8])(struct gb *,byte) =
{
	TABLE_ALU_ADD,
	TABLE_ALU_ADC,
	TABLE_ALU_SUB,
	TABLE_ALU_SBC,
	TABLE_ALU_AND,
	TABLE_ALU_XOR,
	TABLE_ALU_OR,
	TABLE_ALU_CP
};
char const *STR_ALU[8] = {"ADD A,","ADC A,","SUB","SBC A,","AND","XOR","OR","CP"};

# define GETVAL(V)\
	if (z==6) {V=READ(REG(HL));}\
	else     {V=REG(r8[TABLE_R[z]]);}
# define SETVAL(V)\
	if (z==6) {WRITE(REG(HL), V);}\
	else     {REG(r8[TABLE_R[z]])=V;}

void TABLE_ROT_RLC (struct gb *gb, byte op)
{
	//Clear flags
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_H);

	//get opcode z and byte value
	byte z = OPCODE_Z(op);
	byte val;
	GETVAL(val);

	//get carry flag
	CND_FLAG(FLAG_C, val >> 7);

	//Rotate byte
	__asm__("rolb $1, %0" : "=r" (val) : "r"  (val));
	CND_FLAG(FLAG_Z, val == 0);

	//store value back in
	SETVAL(val);
}
void TABLE_ROT_RRC (struct gb *gb, byte op)
{
	//Clear flags
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_H);

	//Get byte
	byte val;
	byte z = OPCODE_Z(op);
	GETVAL(val);

	//put 1st bit in carry flag
	CND_FLAG(FLAG_C, val & 1);
	//Rotate byte
	__asm__("rorb $1, %0" : "=r" (val) : "r"  (val));
	CND_FLAG(FLAG_Z, val == 0);

	SETVAL(val);
}
void TABLE_ROT_RL  (struct gb *gb, byte op)
{
	byte cflag = GET_FLAG(FLAG_C);
	//Clear flags
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_H);
	//Get byte
	byte val;
	byte z = OPCODE_Z(op);
	GETVAL(val);
	//put 7th bit in carry flag
	CND_FLAG(FLAG_C, val >> 7);
	//shift val
	val <<= 1;
	val |= cflag;
	//Set if zero
	CND_FLAG(FLAG_Z, val == 0);

	SETVAL(val);
}
void TABLE_ROT_RR  (struct gb *gb, byte op)
{
	byte cflag = GET_FLAG(FLAG_C);
	//Clear flags
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_H);
	//Get byte
	byte val;
	byte z = OPCODE_Z(op);
	GETVAL(val);
	//put 1st bit in carry flag
	CND_FLAG(FLAG_C, val & 1);
	//shift byte
	val >>= 1;
	val |= cflag << 7;
	//set if zero
	CND_FLAG(FLAG_Z, val == 0);

	SETVAL(val);
}
void TABLE_ROT_SLA (struct gb *gb, byte op)
{
	//Clear flags
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_H);
	//Get byte
	byte   val;
	byte z = OPCODE_Z(op);
	GETVAL(val);
	//put 7th bit in carry flag
	CND_FLAG(FLAG_C, val >> 7);
	//Rotate byte
	val <<= 1;
	CND_FLAG(FLAG_Z, val == 0);

	SETVAL(val);
}
void TABLE_ROT_SRA (struct gb *gb, byte op)
{
	//Clear flags
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_H);
	//Get byte
	byte   val;
	byte z = OPCODE_Z(op);
	GETVAL(val);
	//put 7th bit in carry flag
	CND_FLAG(FLAG_C, val & 7);
	//Get msb
	byte msb = val & (1 << 7);
	//shift byte
	val >>= 1;
	val |= msb;
	//set if 0
	CND_FLAG(FLAG_Z, val == 0);

	SETVAL(val);
}
void TABLE_ROT_SWAP(struct gb *gb, byte op)
{
	//Clear flags
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_H);
	CLR_FLAG(FLAG_Z);
	//Get byte
	byte   val;
	byte z = OPCODE_Z(op);
	GETVAL(val);
	//Swap upper and lower 4bit parts
	__asm__ __volatile__(
			"rolb $4, %0"
		: "=r" (val)
		: "r"  (val));
	//set zeroflag
	CND_FLAG(FLAG_Z, val == 0);

	SETVAL(val);
}
void TABLE_ROT_SRL (struct gb *gb, byte op)
{
	//Clear flags
	CLR_FLAG(FLAG_N);
	CLR_FLAG(FLAG_H);
	//Get byte
	byte   val;
	byte z = OPCODE_Z(op);
	GETVAL(val);
	//put 7th bit in carry flag
	CND_FLAG(FLAG_C, val & 7);
	//shift byte
	val >>= 1;
	//set if 0
	CND_FLAG(FLAG_Z, val == 0);
	SETVAL(val);
}

# undef SETVAL
# undef GETVAL

void (*const TABLE_ROT[8])(struct gb *gb, byte op) =
{
	TABLE_ROT_RLC,
	TABLE_ROT_RRC,
	TABLE_ROT_RL,
	TABLE_ROT_RR,
	TABLE_ROT_SLA,
	TABLE_ROT_SRA,
	TABLE_ROT_SWAP,
	TABLE_ROT_SRL
};
char const *STR_ROT[8] = {"RLC","RRC","RL","RR","SLA","SRA","SWAP","SRL"};


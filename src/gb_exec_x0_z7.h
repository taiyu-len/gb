/* exec_x0_z7.h */
#pragma once
#include "gb_exec.h"

//!Switch for child functions
int gb_exec_x0_z7(struct gb *gb, byte op);

//!0xx0_z7:RLCA: rotate A left, old bit 7 to carry flag
int gb_exec_x0_z7_y0(struct gb *gb);

//!0x0F:RRCA: rotate A right, old bit 0 to carry flag
int gb_exec_x0_z7_y1(struct gb *gb);

//!0x17:RLA: rotate A left through carry flag
int gb_exec_x0_z7_y2(struct gb *gb);

//!0x1F:RRA: rotate A right through carry flag
int gb_exec_x0_z7_y3(struct gb *gb);

//!0x27:DAA: Decimal adjust register A.This instruction adjusts register A so
///     that the correct representation of binary coded decimal is obtained
int gb_exec_x0_z7_y4(struct gb *gb);

//!0x2F:CPL: Complement A register (flip bits)
int gb_exec_x0_z7_y5(struct gb *gb);

//!0x37:SCF: Set Carry Flag
int gb_exec_x0_z7_y6(struct gb *gb);

//!0x3F:CCF: Complement Carry Flag
int gb_exec_x0_z7_y7(struct gb *gb);

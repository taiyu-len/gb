/* exec_x3_z1.h */
#pragma once
#include "gb_exec.h"

//!Switch for child functions
int gb_exec_x3_z1(struct gb*, byte);
//!POP rp2[p]
int gb_exec_x3_z1_q0(struct gb*, byte);
//!Switch for child functions
int gb_exec_x3_z1_q1(struct gb*, byte);
//!C9: RET: Pop two bytes from stack & jump to that address
int gb_exec_x3_z1_q1_p0(struct gb *gb);
//!D9: RETI: Same as RET, but enable interrupts
int gb_exec_x3_z1_q1_p1(struct gb *gb);
//!E9: JP (HL) : jump to address contained in HL
int gb_exec_x3_z1_q1_p2(struct gb *gb);
//!F9: LD SP,HL
int gb_exec_x3_z1_q1_p3(struct gb *gb);


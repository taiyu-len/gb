/* exec_x0_z2.h */
#pragma once
#include "gb_exec.h"

//!Switch for child functions
int gb_exec_x0_z2(struct gb*, byte);

//!02:LD   (BC),A: Put A into address (BC)
int gb_exec_x0_z2_q0_p0(struct gb *);

//!12:LD   (DE),A: Put A into address (DE)
int gb_exec_x0_z2_q0_p1(struct gb *);

//!22:LDI  (HL),A: Put A into address (HL) and increment HL
int gb_exec_x0_z2_q0_p2(struct gb *);

//!32:LDD  (HL),A: Put A into address (HL) and decrement HL
int gb_exec_x0_z2_q0_p3(struct gb *);

//!0A:LD   A,(BC): Put (BC) into A
int gb_exec_x0_z2_q1_p0(struct gb *);

//!1A:LD   A,(DE): Put (DE) into A
int gb_exec_x0_z2_q1_p1(struct gb *);

//!2A:LDI  A,(HL): Put (HL) into A and increment HL
int gb_exec_x0_z2_q1_p2(struct gb *);

//!3A:LDD  A,(HL): Put (HL) into A and decrement HL
int gb_exec_x0_z2_q1_p3(struct gb *);


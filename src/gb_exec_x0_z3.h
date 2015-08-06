/* exec_x0_z3.h */
# ifndef  _GB_EXEC_X0_Z3_H
# define  _GB_EXEC_X0_Z3_H
# include "gb_exec.h"

int gb_exec_x0_z3(struct gb*, byte);

//!INC rp[p]
/** Increment 16bit Register p */
int gb_exec_x0_z3_q0(struct gb*, byte);

//!DEC rp[p]
/** Decrement 16bit Register p */
int gb_exec_x0_z3_q1(struct gb*, byte);

# endif


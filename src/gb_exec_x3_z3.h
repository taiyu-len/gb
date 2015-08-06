/* exec_x3_z3.h */
# ifndef  _GB_EXEC_X3_Z3_H
# define  _GB_EXEC_X3_Z3_H
# include "gb_exec.h"

//!Switch for child functions
int gb_exec_x3_z3(struct gb*, byte);
//!C3:JP a16: Jump to immiate 16 bit address
int gb_exec_x3_z3_y0(struct gb *gb);
//!CB:Prefix:  Prefix Call for doing bitwise operators
int gb_exec_x3_z3_y1(struct gb *gb);
//!F3:DI: Disable interrupts
int gb_exec_x3_z3_y6(struct gb *gb);
//!F8:EI: Enable interrupts
int gb_exec_x3_z3_y7(struct gb *gb);

# endif


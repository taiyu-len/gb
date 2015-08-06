/* exec_x1.h */
# ifndef  _GB_EXEC_X1_H
# define  _GB_EXEC_X1_H
# include "gb_exec.h"

//!LD r[y], r[z]; 8bit load
int gb_exec_x1(struct gb*, byte);

//!0x76:HALT: replaces LD (HL), (HL), wait for interruption
int gb_exec_x1_z6(struct gb*);

# endif

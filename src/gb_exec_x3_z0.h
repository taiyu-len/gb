/* exec_x3_z0.h */
# ifndef  _GB_EXEC_X3_Z0_H
# define  _GB_EXEC_X3_Z0_H
# include "gb_exec.h"

//!RET cc[y] if y<4 Switch for others
int gb_exec_x3_z0(struct gb*, byte);
//!E0:LDH (a8), A
int gb_exec_x3_z0_y4(struct gb *);
//!E8:ADD SP, r8
int gb_exec_x3_z0_y5(struct gb *);
//!F0:LDH A,(a8)
int gb_exec_x3_z0_y6(struct gb *);
//!F8:LD HL, SP+r8
int gb_exec_x3_z0_y7(struct gb *);

# endif


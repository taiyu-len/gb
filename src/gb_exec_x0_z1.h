/* exec_x0_z1.h */
# ifndef  _GB_EXEC_X0_Z1_H
# define  _GB_EXEC_X0_Z1_H
# include "gb_exec.h"

//!Switch for child functions
int gb_exec_x0_z1(struct gb*, byte);

//!LD rp[p], NN
/** Put 16 bit immediate value into TABLE_RP[p] register */
int gb_exec_x0_z1_q0(struct gb*, byte);

//!ADD HL, n: where n = {BC, DE, HL, SP}
/**Add n to HL */
int gb_exec_x0_z1_q1(struct gb*, byte);

# endif


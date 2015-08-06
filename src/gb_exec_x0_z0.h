/* exec_x0_z0.h */
#pragma once
#include "gb_exec.h"

//!Switch for child functions
int gb_exec_x0_z0(struct gb*, byte);

//!0x00:NOP
/**Do nothing for this cycle */
int gb_exec_x0_z0_y0(struct gb*);

//!0x08:LD (a16), SP
/**Put stack pointer at address nn */
int gb_exec_x0_z0_y1(struct gb*);

//!0x10:STOP
/**Halt processor & screen until button press.*/
int gb_exec_x0_z0_y2(struct gb*);

//!0x18: JR r8
/** Add n to current address and jump to it*/
int gb_exec_x0_z0_y3(struct gb*);

//!0x20|28|30|38:JR (NZ|Z|NC|C) r8
/** Add immediate byte to address if condition is true */
int gb_exec_x0_z0_y47(struct gb *, byte op);



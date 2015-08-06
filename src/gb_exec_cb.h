/* exec_cb.h */
#pragma once
#include "gb_exec.h"
//!Switch for child functions
int gb_exec_cb(struct gb*, byte);
//!00-3F:rot[y] r[z]: Roll/shift register or memlocation
int gb_exec_cb_x0(struct gb*, byte);
//!BIT y, r[z]: testbits
int gb_exec_cb_x1(struct gb*, byte);
//!RES y, r[z]: reset bit
int gb_exec_cb_x2(struct gb*, byte);
//!SET y, r[z]: set bit
int gb_exec_cb_x3(struct gb*, byte);




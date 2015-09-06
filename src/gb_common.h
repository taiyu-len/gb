/*!@file   gb_common.h */
# ifndef  _GB_COMMON_H
# define  _GB_COMMON_H
# include "log.h"

/**{ common Datatypes */
struct gb;

///Basic 8bit gameboy data type
typedef unsigned char  byte;

///Basic 16bit gameboy data type
typedef unsigned short addr;

/**}{ memory banks*/

///16KB memory for ROM BANK
typedef byte bank16[0x4000];
///8KB  memory for Video ram and external ram
typedef byte bank08[0x2000];
///4KB memory for Working ram
typedef byte bank04[0x1000];

//enums
enum GAMEBOY_INFO
{
	//Gameboy type
	CGB_MODE = 0,
	GB_MODE  = 1,
};

enum RET_CODE {
	RET_SUCCESS,
	RET_FAILURE,
};

# endif /*_GB_COMMON_H*/


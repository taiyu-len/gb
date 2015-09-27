/**\file  gb_screen.h */
# ifndef _GB_SCREEN_H
# define _GB_SCREEN_H
# include "gb_common.h"

// Gameboy screen type
typedef struct
{
	byte r, g, b;
}
gb_screen[160][144];

/** Update the gameboy screen data */
void gb_screen_update(struct gb *);

#endif


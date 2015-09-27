/**\file   gb.h */
# ifndef  _GB_H
# define  _GB_H

# include "gb_common.h"
# include "gb_memory.h"
# include "gb_register.h"
# include "gb_exec.h"
# include "gb_screen.h"

//!Gameboy structure.
/**used to store all gameboy related data */
struct gb
{
	/* Data */
	union   gb_register reg;
	struct  gb_memory   mem;
	gb_screen           screen;
	/* Timing */
	short   cycle;
	int     lcdc_cycle;
	byte    stop;
	byte    halt;
	//color or normal gameboy mode
	enum GAMEBOY_INFO mode;
	char *title;
};

/* Functions */
/** Create and intialize a gameboy object loaded with a file
 * \param gb if NULL creates and returns new gameboy [ must use free() ]
 *           otherwise uses given gb
 * \param filename to load
 * \return returns gb*/
struct gb *gb_loadfile(struct gb *gb, char const filename[]);

/** Executets gameboy
 * \param gb to run */
int        gb_update  (struct gb *gb);


# endif /*_GB_H*/


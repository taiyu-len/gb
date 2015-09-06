/*!@file   gb_mbc.h */
# ifndef  _GB_MBC_H
# define  _GB_MBC_H
# include "gb_common.h"

//!Memory bank controller, deterines how to read and write memory to gameboy
struct gb_mbc {
	byte (*read) (struct gb*, addr);
	void (*write)(struct gb*, addr, byte);
	byte rom_switch;
	byte ram_switch;
	byte ram_enabled;
	byte ram_rom_mode;
};

/**Initialize mbc for a given gb, Rom must be loaded prior to this function
 * \param gb to initialize mbc in */
void gb_mbc_init(struct gb *gb);

# endif /*_GB_MBC_H*/


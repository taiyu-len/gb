/*!@file   gb_io.h */
# ifndef  _GB_IO_H
# define  _GB_IO_H
# include "gb_common.h"

/**Initilize IO registers
 * \param gb to init */
void gb_io_init(struct gb*);

extern
char const * const gb_io_str[0x100];

# endif /*_GB_IO_H*/

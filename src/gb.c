/* gb.c */
# include "gb.h"
# include "gb_exec.h"
# include "gb_update.h"

# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <assert.h>

struct gb *gb_loadfile(struct gb *gb, char const filename[])
{
	FILE *file;
	void *rm = NULL; /* Used to free gameboy on failure if we need to */

	logf("Loading File %s\n", filename);
	//openfile
	if((file = fopen(filename, "r")) == NULL) {
		errf();
		goto fopen_fail;
	}
	//allocate memory if requested
	if(gb == NULL && (gb = rm = malloc(sizeof(*gb))) == NULL) {
		errf();
		goto malloc_fail;
	}
	//Rom files should be a multiple of 0x4000
	if(fread(gb->mem.rom, 1, 0x80 * 0x4000, file) % 0x4000 != 0) {
		errf("Invalid Rom file\n");
		goto read_fail;
	}

	gb_register_init(gb);
	gb_memory_init(gb);

	logf("Finished loading gameboy\n");
	logf("gameboy type: %sGB_MODE\n",gb->mode?"":"C");
	logf("title       : %.16s\n",gb->title);
	fclose(file);
	return gb;

/* cleanup on failure */
read_fail:

	free(rm);
malloc_fail:

	fclose(file);
fopen_fail:

	return NULL;
}


/* Update gameboy */
int        gb_update(struct gb *gb)
{
	struct timespec delay = {0, 0};
	assert(gb != NULL);
	/* Logging */
	logf("PC(%.4x)"
			 "SP(%.4x)"
			 "AF(%.2x|%.2x)"
			 "BC(%.2x|%.2x)"
			 "DE(%.2x|%.2x)"
			 "HL(%.2x|%.2x) "
		 , REG(PC)
		 , REG(SP)
		 , REG(A), REG(F)
		 , REG(B), REG(C)
		 , REG(D), REG(E)
		 , REG(H), REG(L));

	/* Check for halt/stop flags */
	if(gb->halt || gb->stop) {
		delay.tv_nsec = 500000;
		nanosleep(&delay, NULL);
		logf(".");
	} else {
		gb_update_exec(gb);
	}
	gb_update_int (gb); //interupts
	gb_update_io  (gb);

	//Delay
	delay.tv_nsec = gb->cycle * 5000;
	nanosleep(&delay, NULL);
	gb->cycle = 0;
	return RET_SUCCESS;
}


/*!@file gb_update.h
 * Inline functions for gb_update() to use,
 * only gb.c should include this file */
# ifndef _GB_UPDATE
# error "_GB_UPDATE Must be defined, and only gb.c should include this header"
# endif

//INLINES
/* Execute next instruction */
static inline
int gb_update_exec(struct gb *gb)
{
	//Get next opcode
	byte opcode = READ(REG(PC)++);
	//Execute opcode
	if(gb_exec(gb, opcode) == RET_FAILURE) {
		errf("Invalid opcode, %x",opcode);
		return RET_FAILURE;
	}
	return RET_SUCCESS;
}

/* Check for interrupts */
static inline
void gb_update_int(struct gb *gb)
{
	byte val;
	/* Check For Interrupts
	 * only if ime flag is set and if a IO_IF flag is set*/
	if (gb->mem.ime && (val = (gb->mem.ier & READ(IO_IF) & 0x1F))) {
		//disable interrupts
		gb->mem.ime = 0x00;
		if (val & 0x01) {
			logf("V-Blank Interrupt\n");
			PUSH(REG(PC));
			REG(PC) = 0x40;
			//clear bit
			WRITE(IO_IF, READ(IO_IF) & ~(0x01));
		}
		else if (val & 0x02) {
			logf("LCD_Stat Interrupt\n");
			PUSH(REG(PC));
			REG(PC) = 0x48;
			//clear bit
			WRITE(IO_IF, READ(IO_IF) & ~(0x02));
		}
		else if (val & 0x04) {
			logf("Timer Interrupt\n");
			PUSH(REG(PC));
			REG(PC) = 0x50;
			//clear bit
			WRITE(IO_IF, READ(IO_IF) & ~(0x04));
		}
		else if (val & 0x08) {
			logf("Serial Interrupt\n");
			PUSH(REG(PC));
			REG(PC) = 0x58;
			//clear bit
			WRITE(IO_IF, READ(IO_IF) & ~(0x08));
		}
		else if (val & 0x10) {
			logf("Joypad Interrupt\n");
			PUSH(REG(PC));
			REG(PC) = 0x60;
			//clear bit
			WRITE(IO_IF, READ(IO_IF) & ~(0x10));
		}
		gb->stop = gb->halt = 0;
	}
}

/* Update stat io register */
static inline
void gb_update_stat(struct gb *gb)
{
	//TODO set vblank interrupt flag
	//|2 : 80|3 : 172|0 : 204|1 : 4560|
	//|                      |        |
	//|loop 144 times : 65664|  once  |
	//|                               |
	//|   entire loop lasts : 70224   |
	if (!gb->cycle) {
		return;
	}
	//Update lcdc
	gb->lcdc_cycle += gb->cycle;

	//get pointer for modifying mode
	struct {unsigned mode:2;} *ptr = (void*)&gb->mem.io[IO_STAT - MEM_IO_PORTS];

	switch(ptr->mode) {
	case 2: /* reading from OAM memory */
		// Switch to Mode 3
		if (gb->lcdc_cycle % 456 > 80) ptr->mode = 3;

		break;

	case 3: /* Reading from oam and Vram memory */
		//switch to mode 0, and draw scanline
		if (gb->lcdc_cycle % 456 > 80+172) {
			ptr->mode = 0;
			//TODO draw_scanline(gb, gb->lcdc_cycle / 456);
		}
		break;

	case 0: /* Hblank mode */
		//Switch to mode 1:VBlank
		if (gb->lcdc_cycle > 456 * 144) {
			ptr->mode = 1;
			//Set vblank intterupt bit
			WRITE(IO_IF, READ(IO_IF) | 0x01);
		}
		//Swith to mode 2:OAM
		else if (gb->lcdc_cycle % 456 <= 80) {
			ptr->mode = 2;
		}
		break;

	case 1:/* Vblank mode */
		//reset and switch to mode 2
		if (gb->lcdc_cycle > 70224) {
			ptr->mode = 2;
			gb->lcdc_cycle = 0;
		}
		break;
	}

	//Set scanline number
	WRITE(IO_LY, gb->lcdc_cycle / 456);
}

/* Update IO values */
static inline
void gb_update_io(struct gb *gb)
{
	//Update lcdc STAT io register
	gb_update_stat(gb);
}


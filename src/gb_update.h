/*!@file   gb_update.h
 * Inline functions for gb_update() to use,
 * only gb.h can include this file */
# ifdef  _GB_H

//INLINES
/* Execute next instruction */
static inline int  gb_update_exec(struct gb *gb)
{
  byte opcode;
  //Get opcode
  opcode = READ(REG(PC)++);
  //Execute opcode
  if(gb_exec(gb, opcode) == RET_FAILURE) {
    errf("Invalid opcode, %x",opcode);
    return RET_FAILURE;
  }
  //delay for 0.5 ms per cycle used
  return RET_SUCCESS;
}

/* Check for interrupts */
static inline void gb_update_int(struct gb *gb)
{
  byte val;
  /* Check For Interrupts */
  if(gb->mem.ime && (val = gb->mem.ier & gb->mem.io[IO_IF - MEM_IO_PORTS] & 0x1F)) {
    //val garunteed to have at least 1 bit between 0 and 5 set.
    //disable interrupts
    gb->mem.ime = 0x00;
    if(val & 0x01) {
      logf("V-Blank Interrupt\n");
      PUSH(REG(PC));
      REG(PC) = 0x40;
      //clear bit
      gb->mem.io[IO_IF - MEM_IO_PORTS] &= ~(0x01);
    }
    else if(val & 0x02) {
      logf("LCD_Stat Interrupt\n");
      PUSH(REG(PC));
      REG(PC) = 0x48;
      //clear bit
      gb->mem.io[IO_IF - MEM_IO_PORTS] &= ~(0x02);
    }
    else if(val & 0x04) {
      logf("Timer Interrupt\n");
      PUSH(REG(PC));
      REG(PC) = 0x50;
      //clear bit
      gb->mem.io[IO_IF - MEM_IO_PORTS] &= ~(0x04);
    }
    else if(val & 0x08) {
      logf("Serial Interrupt\n");
      PUSH(REG(PC));
      REG(PC) = 0x58;
      //clear bit
      gb->mem.io[IO_IF - MEM_IO_PORTS] &= ~(0x08);
    }
    else if(val & 0x10) {
      logf("Joypad Interrupt\n");
      PUSH(REG(PC));
      REG(PC) = 0x60;
      //clear bit
      gb->mem.io[IO_IF - MEM_IO_PORTS] &= ~(0x10);
    }
    gb->stop = gb->halt = 0;
  }
}

/* Update lcdc register */
static inline void gb_update_stat(struct gb *gb)
{
  //TODO set vblank interrupt flag
  //|2 : 80|3 : 172|0 : 204|1 : 4560|
  //|                      |        |
  //|loop 144 times : 65664|  once  |
  //|                               |
  //|   entire loop lasts : 70224   |
  if(!gb->cycle) {
    return;
  }
  //Get current mode
  int mode = gb->lcdc_cycle > 65664         ? 1
           : gb->lcdc_cycle % 456 <= 80     ? 2
           : gb->lcdc_cycle % 456 <= 80+172 ? 3
           :                                  0;
  //Update lcdc
  gb->lcdc_cycle += gb->cycle;

  //get pointer for modifying mode
  struct {unsigned x:2;} *ptr = (void*)&gb->mem.io[IO_STAT - 0xFF00];

  switch(mode) {
    case 2: /* reading from OAM memory */
      //Switch to Mode 3
      if(gb->lcdc_cycle % 456 > 80) {
        ptr->x = 3;
      }
      break;

    case 3: /* Reading from oam and Vram memory */
      //switch to mode 0, and draw scanline
      if(gb->lcdc_cycle % 456 > 80+172) {
        ptr->x = 0;
        //TODO draw_scanline(gb, gb->lcdc_cycle / 456);
      }
      break;

    case 0: /* Hblank mode */
      //Switch to mode 1. and draw screen
      if(gb->lcdc_cycle > 456 * 144) {
        ptr->x = 1;
        //TODO draw_screen;
      }
      //Switch to mode 2
      else if(gb->lcdc_cycle % 456 <= 80) {
        ptr->x = 2;
      }
      break;

    case 1:/* Vblank mode */
      //reset and switch to mode 2
      if(gb->lcdc_cycle > 70224) {
        ptr->x = 2;
        gb->lcdc_cycle = 0;
      }
      break;
  }
}

/* Update IO values */
static inline void gb_update_io(struct gb *gb)
{
  byte *io = gb->mem.io;

  //LCDC Y-Coordinate. scanline value
  io[IO_LY - 0xFF00] = gb->lcdc_cycle / 456;
}

# endif /*_GB_H*/

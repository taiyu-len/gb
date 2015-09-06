/* gb_mbc.c */
# include "gb_mbc.h"
# include "gb.h"


static byte read(struct gb *, addr);
static void write_mbc0(struct gb *, addr, byte);
static void write_mbc1(struct gb *, addr, byte);
static void write_mbc2(struct gb *, addr, byte);
static void write_mbc3(struct gb *, addr, byte);
static void write_mbc4(struct gb *, addr, byte);
static void write_mbc5(struct gb *, addr, byte);

static struct gb_mbc mbc0 = {.read = read, .write = write_mbc0 };
static struct gb_mbc mbc1 = {.read = read, .write = write_mbc1 };
static struct gb_mbc mbc2 = {.read = read, .write = write_mbc2 };
static struct gb_mbc mbc3 = {.read = read, .write = write_mbc3 };
static struct gb_mbc mbc4 = {.read = read, .write = write_mbc4 };
static struct gb_mbc mbc5 = {.read = read, .write = write_mbc5 };

void gb_mbc_init(struct gb *gb)
{
	byte cart_type = gb->mem.rom[0][ADDR_CARTRIDGE_TYPE];

	switch(cart_type) {
		//Case No mbc
		case 0x00: case 0x08: case 0x09:
			gb->mem.mbc = mbc0;
			break;
		//Case of MBC 1
		case 0x01: case 0x02: case 0x03:
			gb->mem.mbc = mbc1;
			break;
		//Case of MBC2
		case 0x05: case 0x06:
			gb->mem.mbc = mbc2;
			break;
		//Case of MBC3
		case 0x0F: case 0x10: case 0x11: case 0x12: case 0x13:
			gb->mem.mbc = mbc3;
			break;
		//Case of MBC4
		case 0x15: case 0x16: case 0x17:
			gb->mem.mbc = mbc4;
			break;
		//Case of MBC5
		case 0x19: case 0x1A: case 0x1B: case 0x1C: case 0x1D: case 0x1E:
			gb->mem.mbc = mbc5;
			break;
	}
	gb->mem.mbc.rom_switch
	= gb->mem.mbc.ram_switch
	= gb->mem.mbc.ram_enabled
	= 1;
	gb->mem.mbc.ram_rom_mode = 0;
}


# include <assert.h>

//Memory bank controller
byte read(struct gb *gb, addr address)
{
	//FFFF| Read from interrupt register
	if(address >= MEM_INTERRUPT_REGISTER) {
		return gb->mem.ier;
	}
	//FF80-FFFE|Read from high ram (stack)
	if(address >= MEM_HRAM) {
		return gb->mem.hram[address - MEM_HRAM];
	}
	//FF00-FF7F|Read from IO registers
	if(address >= MEM_IO_PORTS) {
		return gb->mem.io[address - MEM_IO_PORTS];
	}
	//FE00-FE9F|Read from OAM
	if(address >= MEM_OAM) {
		return gb->mem.oam[address - MEM_OAM];
	}
	//E000-FDFF|Working ram & echo
	if(address >= MEM_WRAM_ECHO) {
		address -= 0x2000;
	}
	//D000-DFFF|Working ram bank N
	if(address >= MEM_WRAM_BANK_N) {
		if(gb->mode == CGB_MODE) {
			return gb->mem.wram[gb->mem.io[IO_SVBK - MEM_IO_PORTS] & 3]
												 [address - MEM_WRAM_BANK_N];
		} else {
			return gb->mem.wram[1][address - MEM_WRAM_BANK_N];
		}
	}
	//C000-CFFF|Working ram bank 0
	if(address >= MEM_WRAM_BANK_0) {
		return gb->mem.wram[0][address - MEM_WRAM_BANK_0];
	}
	//A000-BFFF|Read from external ram
	if(address >= MEM_ERAM) {
		return gb->mem.eram[gb->mem.mbc.ram_switch][address - MEM_ERAM];
	}
	//8000-9FFF|Read from videoram
	if(address >= MEM_VRAM) {
		address -= MEM_VRAM;
		if(gb->mode == CGB_MODE) {
			return gb->mem.vram[gb->mem.io[IO_VBK - MEM_IO_PORTS]][address];
		} else {
			return gb->mem.vram[0][address];
		}
	}
	//4000-7FFF|Read from rom bank 1+
	if(address >= MEM_ROM_BANK_N) {
		return gb->mem.rom[gb->mem.mbc.rom_switch][address - MEM_ROM_BANK_N];
	}
	//0000-3FFF|Read from rom bank 0
	//if(address >= MEM_ROM_BANK_0) {
	return gb->mem.rom[0][address];
	//}
	//impossible to reach this point
	return 0;
}

//Common write above address 8000
void write_common(struct gb *gb, addr address, byte value)
{
	if(address < 0x8000){
		return;
	}
	//FFFF| Read from interrupt register
	if(address >= MEM_INTERRUPT_REGISTER) {
		gb->mem.ier = value;
		return;
	}
	//FF80-FFFE|Read from high ram (stack)
	if(address >= MEM_HRAM) {
		gb->mem.hram[address - MEM_HRAM] = value;
		return;
	}
	//FF00-FF7F|Read from IO registers
	if(address >= MEM_IO_PORTS) {
		gb->mem.io[address - MEM_IO_PORTS] = value;
		return;
	}
	//FE00-FE9F|Read from OAM
	if(address >= MEM_OAM) {
		gb->mem.oam[address - MEM_OAM] = value;
		return;
	}
	//E000-FDFF|Working ram & echo
	if(address >= MEM_WRAM_ECHO) {
		address -= 0x2000;
	}
	//D000-DFFF|Working ram bank N
	if(address >= MEM_WRAM_BANK_N) {
		if(gb->mode == CGB_MODE) {
			gb->mem.wram
				[gb->mem.io[IO_SVBK - MEM_IO_PORTS] & 3]
				[address - MEM_WRAM_BANK_N]
				= value;
		} else {
			gb->mem.wram[1][address - MEM_WRAM_BANK_N] = value;
		}
		return;
	}
	//C000-CFFF|Working ram bank 0
	if(address >= MEM_WRAM_BANK_0) {
		gb->mem.wram[0][address - MEM_WRAM_BANK_0] = value;
		return;
	}
	//A000-BFFF|Read from external ram
	if(address >= MEM_ERAM) {
		gb->mem.eram[gb->mem.mbc.ram_switch][address - MEM_ERAM] = value;
		return;
	}
	//8000-9FFF|Read from videoram
	if(address >= MEM_VRAM) {
		address -= MEM_VRAM;
		if(gb->mode == CGB_MODE) {
			gb->mem.vram[gb->mem.io[IO_VBK - MEM_IO_PORTS]][address] = value;
		} else {
			gb->mem.vram[0][address] = value;
		}
		return;
	}
}

//TODO
//this later vvv

void write_mbc0(struct gb *gb, addr address, byte value)
{
	if(address >= MEM_READ_WRITE) {
		write_common(gb,address,value);
		return;
	}
	//no writing allowed anywhere else
}

void write_mbc1(struct gb *gb, addr address, byte value)
{
	//8000-FFFF
	if(address >= MEM_READ_WRITE) {
		write_common(gb,address,value);
		return;
	}
	//6000-7FFF:Rom/ram mode select
	if(address >= MEM_RAM_ROM_SELECT) {
		gb->mem.mbc.ram_rom_mode = value & 1;
	}
	//4000-5FFF - RAM Bank Number - or - Upper Bits of ROM Bank Number
	if(address >= MEM_RAM_BANK_SELECT) {
	}
}

void write_mbc2(struct gb *gb, addr address, byte value)
{
	if(address >= MEM_READ_WRITE) {
		write_common(gb,address,value);
		return;
	}
	
}

void write_mbc3(struct gb *gb, addr address, byte value)
{
	if(address >= MEM_READ_WRITE) {
		write_common(gb,address,value);
		return;
	}
	
}

void write_mbc4(struct gb *gb, addr address, byte value)
{
	if(address >= MEM_READ_WRITE) {
		write_common(gb,address,value);
		return;
	}
	
}

void write_mbc5(struct gb *gb, addr address, byte value)
{
	if(address >= MEM_READ_WRITE) {
		write_common(gb,address,value);
		return;
	}
	
}




/**\file   gb_memory.h */
# ifndef  _GB_MEMORY_H
# define  _GB_MEMORY_H
# include "gb_common.h"
# include "gb_mbc.h"

struct gb_memory
{
  //memory blocks
  bank16 rom [0x80];///< 80 blocks of 16KB rom
  bank08 vram[0x02];///< 2  blocks of 8kb video ram
  bank08 eram[0x10];///< 16 blocks of 8kb external ram
  bank04 wram[0x08];///< 8  blocks of 4kb working ram
  byte   oam [0xA0];///< 160 bytes of sprite attribute table
  byte   io  [0x80];///< 128 bytes of IO ports
  byte   hram[0x80];///< 128 bytes of high ram (stack)
  byte   ier;       ///< Interrupt enable register

  //Memory bank controller
  struct gb_mbc mbc;
};

/**Initilalize gameboy memory, rom must be written prior to this
 * \param gb to initialize */
void gb_memory_init(struct gb *);

//Memory locations
enum MEMORY_ADDR
{
  //Offsets for memory sections
  //Readonly
  MEM_READ_ONLY             = 0x0000,
    MEM_ROM_BANK_0          = 0x0000,
    MEM_ROM_BANK_N          = 0x4000,
  //Writeonly
  MEM_WRITE_ONLY            = 0x0000,
    MEM_RAM_BANK_ENABLE     = 0x0000,//mbc1,2,3
    MEM_RAM_BANK_SELECT_LSB = 0x2000,
    MEM_ROM_BANK_SELECT_MSB = 0x3000,
    MEM_RAM_BANK_SELECT     = 0x4000,
    MEM_RAM_ROM_SELECT      = 0x6000,
    //R/W section
  MEM_READ_WRITE            = 0x8000,
    MEM_VRAM                = 0x8000,
    MEM_ERAM                = 0xA000,
    MEM_WRAM_BANK_0         = 0xC000,
    MEM_WRAM_BANK_N         = 0xD000,
    MEM_WRAM_ECHO           = 0xE000,
    MEM_OAM                 = 0xFE00,
    MEM_EMPTY               = 0xFEA0,
    MEM_IO_PORTS            = 0xFF00,
    MEM_HRAM                = 0xFF80,
    MEM_INTERRUPT_REGISTER  = 0xFFFF,
  //Reserved Memory Location Offsets
  ADDR_RESTART_00            = 0x0000,
  ADDR_RESTART_08            = 0x0008,
  ADDR_RESTART_10            = 0x0010,
  ADDR_RESTART_18            = 0x0018,
  ADDR_RESTART_20            = 0x0020,
  ADDR_RESTART_28            = 0x0028,
  ADDR_RESTART_30            = 0x0030,
  ADDR_RESTART_38            = 0x0038,
  ADDR_V_BLANK_INTERRUPT     = 0x0040,
  ADDR_LCDC_STAT_INTERRUPT   = 0x0048,
  ADDR_TIMER_OF_INTERRUPT    = 0x0050,
  ADDR_STC_INTERRUPT         = 0x0058,
  ADDR_HL_P10_P13_INTERRUPT  = 0x0060,
  //Cartridge reserved memory
  ADDR_CART_START            = 0x0100,
  ADDR_NINTENDO_GFX          = 0x0104,
  ADDR_GAME_TITLE            = 0x0134,
  ADDR_GAMEBOY_TYPE          = 0x0143,
  ADDR_HIGH_LICENSEE_CODE    = 0x0144,
  ADDR_LOW_LICENSEE_CODE     = 0x0145,
  ADDR_GB_SGB_INDICATOR      = 0x0146,
  ADDR_CARTRIDGE_TYPE        = 0x0147,
  ADDR_ROM_SIZE              = 0x0148,
  ADDR_RAM_SIZE              = 0x0149,
  ADDR_DESTINATION_CODE      = 0x014A,
  ADDR_LICENSEE_CODE_OLD     = 0x014B,
  ADDR_MASK_ROM_VERSION_NUM  = 0x014C,
  ADDR_COMPLEMENT_CHECK      = 0x014D,
  ADDR_CHECKSUM              = 0x014E,
  //I/O Registers
  IO_P1                     = 0xFF00,
  IO_SB                     = 0xFF01,
  IO_SC                     = 0xFF02,
  IO_DIV                    = 0xFF04,
  IO_TIMA                   = 0xFF05,
  IO_TMA                    = 0xFF06,
  IO_TAC                    = 0xFF07,
  IO_IF                     = 0xFF0F,
  IO_NR10                   = 0xFF10,
  IO_NR11                   = 0xFF11,
  IO_NR12                   = 0xFF12,
  IO_NR13                   = 0xFF13,
  IO_NR14                   = 0xFF14,
  IO_NR21                   = 0xFF16,
  IO_NR22                   = 0xFF17,
  IO_NR23                   = 0xFF18,
  IO_NR24                   = 0xFF19,
  IO_NR30                   = 0xFF1A,
  IO_NR31                   = 0xFF1B,
  IO_NR32                   = 0xFF1C,
  IO_NR33                   = 0xFF1D,
  IO_NR34                   = 0xFF1E,
  IO_NR41                   = 0xFF20,
  IO_NR42                   = 0xFF21,
  IO_NR43                   = 0xFF22,
  IO_NR44                   = 0xFF23,
  IO_NR50                   = 0xFF24,
  IO_NR51                   = 0xFF25,
  IO_NR52                   = 0xFF26,
  IO_FF3F                   = 0xFF3F,
  IO_LCDC                   = 0xFF40,
  IO_STAT                   = 0xFF41,
  IO_SCY                    = 0xFF42,
  IO_SCX                    = 0xFF43,
  IO_LY                     = 0xFF44,
  IO_LYC                    = 0xFF45,
  IO_DMA                    = 0xFF46,
  IO_BGP                    = 0xFF47,
  IO_OBP0                   = 0xFF48,
  IO_OBP1                   = 0xFF49,
  IO_WY                     = 0xFF4A,
  IO_WX                     = 0xFF4B,
  IO_KEY1                   = 0xFF4D,//CGB Only
  IO_VBK                    = 0xFF4F,//CGB Only
  IO_HDMA1                  = 0xFF51,//CGB Only
  IO_HDMA2                  = 0xFF52,//CGB Only
  IO_HDMA3                  = 0xFF53,//CGB Only
  IO_HDMA4                  = 0xFF54,//CGB Only
  IO_HDMA5                  = 0xFF55,//CGB Only
  IO_RP                     = 0xFF56,//CGB Only
  IO_BCPS                   = 0xFF68,//CGB Only
  IO_BCPD                   = 0xFF69,//CGB Only
  IO_OCPS                   = 0xFF6A,//CGB Only
  IO_OCPD                   = 0xFF6B,//CGB Only
  IO_SVBK                   = 0xFF70,//CGB Only
  IO_IE                     = 0xFFFF
};

/* Macros */
# include "gb.h"
union endian {
  struct {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    //0xABCD => CD,AB
    byte lsb, msb;
#else
    //0xABCD => AB,CD
    byte msb, lsb;
#endif
  };
  addr addr;
};

//read byte or addr from memory
# define READ(ADDR) gb->mem.mbc.read(gb, (ADDR))
# define READ16(ADDR)  \
  ({addr tmp = (ADDR); \
    union endian val = { .lsb = READ(tmp), .msb = READ(tmp+1)}; \
    val.addr;})

//write byte or addr to memory
# define WRITE(ADDR, VALUE) gb->mem.mbc.write(gb, (ADDR), (VALUE));
# define WRITE16(ADDR, VALUE)                 \
  do{ addr tmp = (ADDR);                      \
      union endian val = { .addr = (VALUE) }; \
      WRITE(tmp  , val.lsb);                  \
      WRITE(tmp+1, val.lsb); }while(0)

//pop or push value to/from stack
# define POP() ({REG(SP)+=2; READ16(REG(SP)-2);})
# define PUSH(VALUE)do{REG(SP)-=2; WRITE16(REG(SP), (VALUE));}while(0)

# endif /*_GB_MEMORY_H*/


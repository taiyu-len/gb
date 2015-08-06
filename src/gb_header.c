/* gb_header.c */
//Prints out header data for gameboy
#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;
  while(--argc)
  {
    FILE *file = fopen(argv[++i], "r");
    if(!file) {
      perror(NULL);
      continue;
    }
    fseek(file, 0x100, SEEK_SET);
    unsigned char data[0x50];
    if(fread(data, 1, 0x50, file) != 0x50) goto end;
    //print title
    printf("%d:%.16s\n", i, &data[0x34]);
    printf("%d:%s Gameboy\n", data[0x43], data[0x43]==0x80?"Color":"");
    printf("licensee code: %d\n", (data[0x44] << 8) + data[0x45]);
    printf("gameboytype: %sgameboy\n",data[0x46]==0x03?"super ":"");
    printf("Cartridge type: ");
    if(data[0x47] < 0x1F)
      printf("ROM");
    switch(data[0x47]) {
      case 0x00: printf(" ONLY");break;
      case 0x03: printf("+BATTERY");
      case 0x02: printf(        "+RAM");
      case 0x01: printf(            "+MBC1");break;
      case 0x06: printf("+BATTERY");
      case 0x05: printf(        "+MBC2");break;
      case 0x09: printf("+BATTERY");
      case 0x08: printf(        "+RAM");break;
      case 0x0d: printf("+BATTERY");
      case 0x0c: printf(        "+SRAM");
      case 0x0b: printf(             "+MMM01");break;
      case 0x0F: printf("+MBC3+TIMER+RAM");
      case 0x10: printf("+MBC3+TIMER+RAM+BATT");
      case 0x13: printf("+BATTERY");
      case 0x12: printf(         "+RAM");
      case 0x11: printf("             +MBC3"); break;
      case 0x1B: printf("+BATTERY");
      case 0x1A: printf(        "+RAM");
      case 0x19: printf(            "+MBC5");break;
      case 0x1E: printf("+BATTERY");
      case 0x1D: printf(        "+SRAM");
      case 0x1C: printf(             "+MBC5+RUMBLE");break;
      case 0x1F: printf("Pocket Camera"); break;
      case 0xFD: printf("Bandai TAMA5"); break;
      case 0xFE: printf("Hudson HuC-3"); break;
      default: printf("Unknown");
    }
    putchar('\n');
    printf("Romsize:");
    if(data[0x48] <= 6)
      printf("%d Banks", 2 << data[0x48]);
    else
      switch(data[0x48]) {
        case 0x52: printf("72 Banks"); break;
        case 0x53: printf("80 Banks"); break;
        case 0x54: printf("96 Banks"); break;
        default: printf("Unknown");
      }
    putchar('\n');
    printf("Ramsize:");
    switch(data[0x49]) {
      case 0x00: printf("None"); break;
      case 0x01: printf("16Kbits, 1bank"); break;
      case 0x02: printf("64KBits, 1bank"); break;
      case 0x03: printf("245kBits, 4 banks"); break;
      case 0x43: printf("1Mbit, 16 banks"); break;
      default:printf("Unknown");
    }
    putchar('\n');
    printf("Destination code: %sJapanese\n",data[0x4A]?"Non-":"");
end:
    fclose(file);
  }
}


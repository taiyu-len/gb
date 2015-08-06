# # GAMEBOY EMULATOR LIBRARY
# Static library for gameboy emulator
LIBRARY = libgb.so
ARCHIVE = gb.a
# Standalone executable for gameboy emulator
SUTAKO  = gb

# # Source files
PLAYER  = gb_player.c
# Source files.
SOURCE  = gb.c
SOURCE += gb_memory.c
SOURCE +=   gb_mbc.c
SOURCE +=   gb_rom.c
SOURCE +=   gb_io.c
SOURCE += gb_register.c
SOURCE += gb_exec.c
SOURCE +=   gb_exec_x0.c
SOURCE +=     gb_exec_x0_z0.c
SOURCE +=     gb_exec_x0_z1.c
SOURCE +=     gb_exec_x0_z2.c
SOURCE +=     gb_exec_x0_z3.c
SOURCE +=     gb_exec_x0_z4.c
SOURCE +=     gb_exec_x0_z5.c
SOURCE +=     gb_exec_x0_z6.c
SOURCE +=     gb_exec_x0_z7.c
SOURCE +=   gb_exec_x1.c
SOURCE +=   gb_exec_x2.c
SOURCE +=   gb_exec_x3.c
SOURCE +=     gb_exec_x3_z0.c
SOURCE +=     gb_exec_x3_z1.c
SOURCE +=     gb_exec_x3_z2.c
SOURCE +=     gb_exec_x3_z3.c
SOURCE +=     gb_exec_x3_z4.c
SOURCE +=     gb_exec_x3_z5.c
SOURCE +=     gb_exec_x3_z6.c
SOURCE +=     gb_exec_x3_z7.c
SOURCE +=   gb_exec_cb.c
SOURCE +=   gb_exec_tables.c
SOURCE += log.c

# # Build Flags
# Static Build
CFLAGS += -std=c11 -Wall -Wextra -fPIC
CFLAGS += -g -Og -pg
LDLIBS += -lm

# # Builds
# Standalone build
$(SUTAKO): $(PLAYER) $(ARCHIVE)
	@echo Building standalone gameboy emulator
	$(CC) $(CPPFLAGS) $(CFLAGS)\
	 $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS)\
	 -o $@

# Archive build
$(ARCHIVE): $(SOURCE:.c=.o)
	@echo Building archive
	$(AR) -cvr -- $@ $^

$(LIBRARY): $(SOURCE:.c=.o)
	@echo Building static lib
	$(CC) -shared $^ -o $@

# Cleanup
clean:
	@echo Cleaning files
	$(RM) -v -- $(SOURCE:.c=.o)\
	 $(SOURCE:.c=.d) \
	 $(ARCHIVE) $(SUTAKO)

#  Prerequisites
%.d: %.c
	@echo Generating prerequisite makefile...
	@set -e; rm -f $@; \
	 $(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	 sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	 rm -f $@.$$$$

# include prerequisite makefiles
include $(SOURCE:.c=.d) $(MAIN:.c=.d)

ifndef MODEL
MODEL=n0110
endif

ifndef SLOT
SLOT=B
endif


HOST_CC=gcc
HOST_LD=gcc
HOST_GDB=gdb
HOST_OBJCOPY=objcopy

COMMON_CFLAGS=-std=gnu99

CFLAGS=$(COMMON_CFLAGS)

ifndef SIMULATOR

include models/$(MODEL)/Makefile
CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
GDB=arm-none-eabi-gdb
OBJCOPY=arm-none-eabi-objcopy
CFLAGS+=-Ofast -fdata-sections -ffunction-sections -ggdb3
LDLIBS+=
LDFLAGS+=$(CFLAGS)
LDFLAGS+=-Wl,--gc-sections

else
CC=$(HOST_CC)
LD=$(HOST_LD)
GDB=$(HOST_GDB)
OBJCOPY=$(HOST_OBJCOPY)
CFLAGS+=-DSIMULATOR

LDLIBS+=-lSDL2 -lSDL2_image
LDFLAGS=$(CFLAGS)
LDFLAGS+=-Wl,--gc-sections

endif

include drivers/Makefile
include kernel/Makefile

ifndef SIMULATOR
.PHONY: write_flash
write_flash: boot.bin
	@echo "Please plug your calculator inside of your computer."
	@echo "Immediately after being plugged, the software will be flashed."
	@echo "Do not use the RESET+6 key combination for this flash."
ifeq ($(SLOT), B)
	@dfu-util -w -d 0483:a291 -a 0 -D boot.bin -s 0x90410000:leave > /dev/null 2>&1
else
	@dfu-util -w -d 0483:a291 -a 0 -D boot.bin -s 0x90010000:leave > /dev/null 2>&1
endif
	@echo "The device has been flashed."
	
.PHONY: boot_only
boot_only:
	@echo "Please plug your calculator inside of your computer."
	@echo "Immediately after being plugged, calculator will reboot."
	@echo "The software must have already been flashed to use this command."
	@echo "Do not use the RESET+6 key combination for this flash."
ifeq ($(SLOT), B)
	@dfu-util -w -d 0483:a291 -a 0 -s 0x90410000:leave > /dev/null 2>&1
else
	@dfu-util -w -d 0483:a291 -a 0 -s 0x90010000:leave > /dev/null 2>&1
endif
	@echo "The device has been reboot."
	
else
.PHONY: run
run: boot.elf
	@echo "Now running the simulator."
	@./boot.elf

endif


.PHONY: help
help:
	@echo "Usage"
	@echo "   make SIMULATOR=1"
	@echo "   make SLOT=B MODEL=n0110"
	@echo "   make boot_only"
	@echo ""
	@echo "Targets"
	@echo "   write_flash             Waits for the device to be connected and flashes it."
	@echo "   boot_only               Only boots the device without flashing. Useful if you want to preserve the Flash memory."
	@echo "   run                     Only valid with SIMULATOR=1, starts the simulator."
	@echo ""
	@echo "Options"
	@echo "   SIMULATOR=1             Builds the simulator instead of a bootable image"
	@echo "   MODEL=n0110|n0115|n0120 Chooses the output model"
	@echo "   SLOT=A|B                Chooses the target slot"


include font/Makefile

boot.hex: boot.elf
	@echo "OBJCOPY $@"
	@$(OBJCOPY) -O ihex boot.elf boot.hex

boot.bin: boot.elf
	@echo "OBJCOPY $@"
	@$(OBJCOPY) -O binary boot.elf boot.bin

boot.elf: $(objs)
	@echo "LD      $@"
	@$(LD) $(LDFLAGS) $(objs) -o $@ $(LDLIBS)

%.o: %.c
	@echo "CC      $@"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "CLEAN"
	@find -name *.o | xargs rm -f
	@rm -f boot.bin
	@rm -f boot.hex
	@rm -f boot.elf
	@rm -f font/ttf2c
	@rm -f kernel/src/sysfont.c

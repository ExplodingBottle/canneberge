font/ttf2c: font/ttf2c.c font/mappings.c font/mappings.h
	@echo "CC      font/ttf2c"
	@$(HOST_CC) $(COMMON_CFLAGS) $(shell pkg-config freetype2 --cflags) font/ttf2c.c font/mappings.c -o font/ttf2c $(shell pkg-config freetype2 --libs)

kernel/src/sysfont.c: kernel/include/kernel/sysfont.h font/ttf2c
	@echo "TTF2C   kernel/src/sysfont.c"
	@./font/ttf2c kernel/src/sysfont.c

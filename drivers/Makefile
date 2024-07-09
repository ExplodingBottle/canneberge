CFLAGS += -Idrivers/include

ifndef SIMULATOR
objs += $(addprefix drivers/src/,\
	display.o \
	keyboard.o \
	powmgmt.o \
)
else
objs += $(addprefix drivers/simulator/,\
	display.o \
	keyboard.o \
	powmgmt.o \
)
endif

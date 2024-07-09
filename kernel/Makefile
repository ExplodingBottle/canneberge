CFLAGS += -Ikernel/include

# Shared objetcs
objs += $(addprefix kernel/src/,\
	sysfont.o \
	console.o \
	bugcheck.o \
	boot.o \
)

ifdef SIMULATOR
# Simulator objects
objs += $(addprefix kernel/simulator/,\
	sim_mem_ctrl.c \
	sim_main.c \
)

else
# Bare metal objects
objs += $(addprefix kernel/src/,\
	boot_header.o \
	vec_table.o \
	syscalls.o \
	memory_control.o \
)
endif
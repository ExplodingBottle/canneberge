#ifndef MEMORY_CONTROL_H
#define MEMORY_CONTROL_H

#define STACK_SIZE 1000
#define SECURITY_MARKER 0xCAD0

void init_stack_security(void);

unsigned long free_mem(void);
extern void _estack(void);

#endif
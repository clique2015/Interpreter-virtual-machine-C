#ifndef PROGMEM_M
#define PROGMEM_M

#include "register.h"
#include "decode.h"

typedef struct {
 int INSTRUCTION;
} progmem;
progmem pm;

void pm_write(int address, int data);
void pm_read();
#endif
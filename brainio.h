#ifndef GO_M
#define GO_M
#include "common.h"
#include "program_memory.h"
#include "register.h"
typedef struct {
 bool INTR0;
 bool INTR1;
 bool INTR2;
}mains;
mains GO_FUNC;
#endif
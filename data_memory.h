#ifndef DM_M
#define DM_M

#include "common.h"
#include "mult.h"
#include "splitbit.h"

typedef enum {
ADDR_INSTR,
ADDR_INDR
} addr_type;

typedef enum {
 PEEK,
 POP_RAM,
 PUSH_RAM,
 MAN_SEL
} ramOp;

typedef struct {
 bool full;
 int RAM_DATA;
}data_memory;

data_memory dm;

void dm_write(addr_type  type, int address, ramOp ram_addr_select);
void dm_read(addr_type  type, int address, ramOp ram_addr_select);

#endif
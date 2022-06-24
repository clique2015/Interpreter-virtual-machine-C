#ifndef DATABUS_M
#define DATABUS_M

#include "ioport.h"
#include "lifo.h"
#include "alumath.h"
#include "fifo.h"


#include "register.h"
#include "program_memory.h"


typedef enum {
regA,
MULT_OUT
} output_select;

typedef enum {
 DATA,
 TIMER_DATA_IN,
 IO_DATA_IN,
 LIFO_IN,
 FIFO_IN,
 IOREAD,
 PROGRAM_COUNTER,
 IO_OUT,
 ALU_OUT,
 FIFO_OUT,
 LIFO_OUT,
 INTERRUPTS
} databusOp;

typedef struct{
 int MULTOUT;
 int regA;
} dbus;
dbus databus_data;

void  bus_set(databusOp sel, output_select outsel);
void set_dataregister(int instructions);

#endif
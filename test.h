#include "common.h"

typedef struct{
 int TIMER_DATA;
 int IO_DATA;
 int LIFO_DATA;
 int FIFO_DATA;
 int IOREAD_DATA;
 int PC_DATA;
 int INTERRUPT_DATA;
 int BAUD;
}Point;
 Point p4;
 Point* p2;

 typedef struct{
 int MULTOUT;
 int regA;
} dbus;
dbus databus_data;

typedef struct {
 bool LT;
 bool EQ;
 bool GT;
 int ALU_OUT;
}Alus;
Alus alu;
#ifndef FIFO_M
#define FIFO_M

#include "register.h"

#include "common.h"


typedef struct {
 bool full;
 bool empty;
 int FIFO_OUT;
}fifo;
fifo fifo_data;

void fifo_push();
void  fifo_pop();

#endif
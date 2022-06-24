
#ifndef LIFO_M
#define LIFO_M

#include "common.h"
#include "register.h"
typedef struct {
 bool full;
 bool empty;
 int LIFO_OUT;
} lifo;
lifo lifo_data;

void lifo_push();
void lifo_pop();
#endif


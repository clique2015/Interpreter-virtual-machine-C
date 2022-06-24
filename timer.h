
#ifndef TIMER_M
#define TIMER_M

#ifndef REGISTER_H
#define REGISTER_H
#include "register.h"
#endif

#include "common.h"

typedef struct {
 bool TON;
} timer;
timer t_data;

void  timer_set(int timer_cs);
#endif
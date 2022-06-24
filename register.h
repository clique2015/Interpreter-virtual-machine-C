
#ifndef REGISTER_M
#define REGISTER_M


#include "lifo.h"
#include "mult.h"
#include "timer.h"
#include "alumath.h"
#include "data_memory.h"
#include "brainio.h"
#include "program_memory.h"
#include "common.h"
#include "ioport.h"
#include "fifo.h"
#include "splitbit.h"

typedef struct{
 int TIMER_DATA;
 int IO_DATA;
 int LIFO_DATA;
 int FIFO_DATA;
 int IOREAD_DATA;
 int PC_DATA;
 int INTERRUPT_DATA;
 bool PUSH_LIFO;
 bool PUSH_FIFO;
 int IO_CS;
 int TIMER_CS;
 bool FREQ_PIN;
 bool CACHE_SET;
 int BAUD;
 int READ_CS;
}registers;
 registers reg_data;


typedef enum {
 TIMER_DATAIN,
 IO_DATAIN,
 LIFOIN,
 FIFOIN,
 IOREADIN,
 PC,
 INTERRUPT
}regsel;

void reg_write(regsel reg_sel, int loadfetch, bool mem);
void intr_set(int intr);
void baud_set(int baud);
void jump(int jump, int jump_sel);	
void set_intr_rt(int intr_rt);	
void run_pc();
#endif
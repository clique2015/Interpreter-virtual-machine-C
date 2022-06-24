/*

#ifndef clox_Ram_mem_h
#define clox_Ram_mem_h

#include "common.h"

typedef enum {
 OP_RETURN,
} OpCode;

typedef struct {
 int count;
 int capacity;
 uint8_t* code;
} Ram_mem;

void initRam_mem(Ram_mem* Ram_mem);
void freeRam_mem(Ram_mem* Ram_mem);
void writeRam_mem(Ram_mem* Ram_mem, uint8_t byte);

#endif
 */

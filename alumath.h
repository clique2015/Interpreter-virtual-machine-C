#ifndef ALU_M
#define ALU_M

#include "common.h"
#include "mult.h"

typedef struct {
 bool LT;
 bool EQ;
 bool GT;
 int ALU_OUT;
}Alus;
Alus alu;


typedef enum {
Inverse, 
Negate, 
Decrement, 
Subtraction,
Addition,
Increment, 
Shift_right,
Shift_left,
XOR, 
OR,
AND,
MAX,
MIN
} alu_op;

void alu_set(alu_op operand);


#endif
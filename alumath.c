#include "alumath.h"
bool GT();
bool LT();
bool EQ();

bool GT(){
    if(databus_data.regA > databus_data.MULTOUT ){
        return true; }
    else{ return false; };    
}

bool LT(){
    if(databus_data.regA < databus_data.MULTOUT ){
        return true; }
    else{ return false; };    
}

bool EQ(){
    if(databus_data.regA == databus_data.MULTOUT ){
        return true; }
    else{ return false; };    
}

void alu_set(alu_op operand) {
    switch (operand) {
    case Inverse :
        alu.ALU_OUT = ~(databus_data.regA);
        break;
    case Negate :
        alu.ALU_OUT = 0 - databus_data.regA;
        break; 
    case Decrement :
        alu.ALU_OUT = databus_data.regA - 1;
        break; 
    case Subtraction :
        alu.ALU_OUT = databus_data.regA - databus_data.MULTOUT ;
        break;
    case Addition :
        alu.ALU_OUT = databus_data.regA + databus_data.MULTOUT ;

        break;
    case Increment :
        alu.ALU_OUT = databus_data.regA + 1;
        break; 
    case Shift_right :
        alu.ALU_OUT = databus_data.regA >> databus_data.MULTOUT ; 
        break;
    case Shift_left :
        alu.ALU_OUT = databus_data.regA << databus_data.MULTOUT ; 
        break;
    case XOR :
        alu.ALU_OUT = databus_data.regA ^ databus_data.MULTOUT ; 
        break; 
    case OR :
        alu.ALU_OUT = databus_data.regA | databus_data.MULTOUT ; 
        break;
    case AND :
        alu.ALU_OUT = databus_data.regA & databus_data.MULTOUT ; 
        break;
    case MAX :
        if(databus_data.regA > databus_data.MULTOUT ){
            alu.ALU_OUT = databus_data.regA; }
        else{alu.ALU_OUT = databus_data.MULTOUT; };
        break;
    case MIN :
        if(databus_data.regA < databus_data.MULTOUT ){
            alu.ALU_OUT = databus_data.regA; }
        else{alu.ALU_OUT = databus_data.MULTOUT; };
    default:
        alu.ALU_OUT = 0;
        break;
    }
    LT();
    GT();
    EQ();

}
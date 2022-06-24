
#include "mult.h"

int bus_output, data_register;

void set_dataregister(int instructions){

    data_register = instructions;
}

void  bus_set(databusOp sel, output_select outsel){
     switch (sel) {
    case DATA:
        bus_output =  data_register;
        break;
    case TIMER_DATA_IN:
        bus_output =  reg_data.TIMER_DATA;
        break;
    case IO_DATA_IN:
        bus_output =  reg_data.IO_DATA;
        break;
    case LIFO_IN:
        bus_output =  reg_data.LIFO_DATA;
        break;
    case FIFO_IN:
        bus_output =  reg_data.FIFO_DATA;
        break;
    case IOREAD:
        bus_output =  reg_data.IOREAD_DATA;
        break;
    case PROGRAM_COUNTER:
        bus_output =  reg_data.PC_DATA;
        break;
    case INTERRUPTS:
        bus_output =  reg_data.INTERRUPT_DATA;
        break;       
    case IO_OUT:
        bus_output =  io_data.IO_DATAOUT;
        break;
    case ALU_OUT:
        bus_output =  alu.ALU_OUT;
        break;
    case FIFO_OUT:
        bus_output = fifo_data.FIFO_OUT;
        break;
    case LIFO_OUT:
        bus_output =  lifo_data.LIFO_OUT;
        break;      
    default:
        bus_output = 0;
        break;
    }
    if(outsel == MULT_OUT){databus_data.MULTOUT = bus_output;} 
    else
    if(outsel == regA){databus_data.regA = bus_output; }
}


#include "data_memory.h"



int ram_reg, addr_reg , addr_return, bins = 0;
int ram_in[1024];
bool empty;

void set_ram_flag(){
  if(addr_reg == 0){
     empty = true;
    }else
    if(addr_reg == 1024){
        dm.full = true;
    }else
    if(addr_reg > 0){
        empty = false;
    }else
    if(addr_reg < 1024){
        dm.full = false;
    }
}

int switch_ram(int address, ramOp ram_addr_select) {
    switch (ram_addr_select) {
    case MAN_SEL:
        addr_reg = address;
        set_ram_flag();
        break;
    case POP_RAM:
        if(!empty) addr_reg--;
        set_ram_flag();
        break;
    case PUSH_RAM:
        if(!dm.full)addr_reg++;
        set_ram_flag();
        break;
    case PEEK:
        return address;
        break;
    }
return addr_reg;
}


void dm_write(addr_type  type, int address, ramOp ram_addr_select) {
    switch (type) {

    case ADDR_INSTR:
        ram_in[address] = databus_data.MULTOUT;
        break;
    case ADDR_INDR:
        bins = split_bit(databus_data.regA, 7, 0);
        addr_return = switch_ram(bins, ram_addr_select);
        ram_in[addr_return] = databus_data.MULTOUT;
        break;
    }
}

void dm_read(addr_type  type, int address, ramOp ram_addr_select) {
    switch (type) {
     
    case ADDR_INSTR:
        dm.RAM_DATA = ram_in[address];
        break;
    case ADDR_INDR:
        bins = split_bit(databus_data.regA, 7, 0);
        addr_return = switch_ram(bins, ram_addr_select);
        dm.RAM_DATA = ram_in[addr_return];
        break;
    }
}

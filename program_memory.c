
#include "program_memory.h"


int ram_in[1024];
int previous_instr;

void pm_write(int address, int data) {
        ram_in[address] = data;

}

void pm_read() {
        int instructions = ram_in[reg_data.PC_DATA];
 
        previous_instr = pm.INSTRUCTION;
        pm.INSTRUCTION  = instructions; 
        if(!((previous_instr == 0) && (pm.INSTRUCTION == 0))){
        decodes(pm.INSTRUCTION);}

}

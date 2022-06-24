

/*
int main(int argc, const char* argv[]) {
 Ram_mem Ram_mem;
 Alu alu;
 alu_set(&alu, alu_op operand); 
ramOp test;
test = PUSH_RAM;
 initRam_mem(&ram_mem);
 loadRam_mem(&ram_mem, 312);
 writeRam_mem(&ram_mem);
 setRamOp(&ram_mem, test);
 writeRam_mem(&ram_mem);
 setRamOp(&ram_mem, test);
 writeRam_mem(&ram_mem);
test = PEEK;
 setRamOp(&ram_mem, test);
 setRamaddr(&ram_mem, 2);
 int ank = readRam_mem(&ram_mem);
 printf("%4d \n", ank);
 disassembleRam_mem(&ram_mem, "test Ram_mem");

 return 0;
}
 */


#include "brainio.h"
int main(int argc, const char* argv[]) {
    
    pm_write(1, 5);   
    pm_write(2, 59419); 
    pm_write(3, 25);   
    pm_write(4, 59419); 
    pm_write(5, 6);  
    pm_write(6, 59419); 
    pm_write(7, 64); 
    pm_write(8, 59419); 
    pm_write(9, 45057); 
    pm_write(10, 45057); 
    pm_write(11, 45057); 
    pm_write(12, 45057); 
    run_pc();  
}

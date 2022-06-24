#include "decode.h"

typedef void (*run_func)(int instructions);

typedef struct {
  int nobits;
  int value;
  run_func func;
} instruction_set;

typedef enum {
 DATA_INSTR,
 EXECUTE_INSTR,
 REG_WRITE_DIRECT_MEM,
 JMP_CTRL,
 REG_WRITE_INDIRECT_MEM,
 CS_CTRL,
 INTR_CTRL,
 REG_WRITE_REG,
 REG_WRITE_POP,
 DIRECT_MEM_WRITE_REG,
 DIRECT_MEM_WRITE_POP,
 INDIRECT_MEM_WRITE_REG,
 INDIRECT_MEM_WRITE_POP
}instruction_type;

void pop(int instructions){
  if(split_bit(instructions, 1, 1) == 1){lifo_pop();}
  if(split_bit(instructions, 0, 0) == 1){fifo_pop();}
  if(split_bit(instructions, 0, 0) == 1){
    bus_set(9 , MULT_OUT); 
  }else{
    bus_set(10 , MULT_OUT);     
  }  
}


void data_func(int instructions){
  set_dataregister(instructions);
  run_pc();
}
void exec_func(int instructions){
  bus_set(split_bit(instructions, 9, 6), regA);
  bus_set(split_bit(instructions, 5, 2), MULT_OUT);
  alu_set(split_bit(instructions, 13, 10));
  pop(instructions);
  run_pc();
}

void dmw_reg(int instructions){
  bus_set(split_bit(instructions, 3, 0), MULT_OUT);  
  dm_write(ADDR_INSTR, split_bit(instructions, 11, 4), PEEK);
  run_pc();
}

void dmw_pop(int instructions){
  pop(instructions);
  dm_write(ADDR_INSTR, split_bit(instructions, 10, 3), PEEK); 
  run_pc();
}

void Imw_pop(int instructions){
  pop(instructions);
  bus_set(split_bit(instructions, 9, 6), regA);   
  dm_write(ADDR_INDR, 0, split_bit(instructions, 5, 4));  
  run_pc();
}

void Imw_reg(int instructions){
  bus_set(split_bit(instructions, 3, 0), MULT_OUT); 
  bus_set(split_bit(instructions, 9, 6), regA);   
  dm_write(ADDR_INDR, 0, split_bit(instructions, 5, 4));  
  run_pc();
}

void rw_dmem(int instructions){
  dm_read(ADDR_INSTR, split_bit(instructions, 12, 5), PEEK);
  reg_write(split_bit(instructions, 2, 0), split_bit(instructions, 4, 3), 1);
  run_pc();
}

void rw_Imem(int instructions){
  bus_set(split_bit(instructions, 10, 7), regA); 
  dm_read(ADDR_INDR, 0, split_bit(instructions, 6, 5));  
  reg_write(split_bit(instructions, 2, 0), split_bit(instructions, 4, 3), 1); 
  run_pc();
}

void rw_reg(int instructions){
  bus_set(split_bit(instructions, 8, 5) , MULT_OUT);    
  reg_write(split_bit(instructions, 2, 0), split_bit(instructions, 4, 3), 0);
  run_pc();
}

void rw_pop(int instructions){
  pop(instructions); 
  reg_write(split_bit(instructions, 2, 0), split_bit(instructions, 4, 3), 0);   
  run_pc();
}

void jmp_set(int instructions){
  jump(split_bit(instructions, 7, 0), split_bit(instructions, 10, 8));
  run_pc();
}

void control_set(int instructions){
  baud_set(split_bit(instructions, 7, 4));
  intr_set(split_bit(instructions, 3, 0));
  run_pc();
}

void control_sig(int instructions){
  pop(instructions);
  timer_set(split_bit(instructions, 3, 2));
  if(split_bit(instructions, 4, 4) == 1){
			fifo_push();}		
  if(split_bit(instructions, 5, 5) == 1){
			lifo_push();}	
  if(split_bit(instructions, 9, 8) > 0){
			set_intr_rt(split_bit(instructions, 9, 8));}	
  run_pc();
}

instruction_set set[] = {
  [DATA_INSTR]   	         = {14,  0,     data_func},
  [EXECUTE_INSTR]          = {14,  1,     exec_func},
  [REG_WRITE_DIRECT_MEM]   = {13,  6,     rw_dmem},
  [DIRECT_MEM_WRITE_REG] 	 = {12,  8,     dmw_reg},
  [JMP_CTRL]		           = {12,  11,    jmp_set},
  [DIRECT_MEM_WRITE_POP]   = {11,  19,    dmw_pop},
  [REG_WRITE_INDIRECT_MEM] = {11,  28,    rw_Imem},
  [CS_CTRL]		             = {11,  20,    control_sig},
  [INTR_CTRL]		           = {11,  21,    control_set},
  [INDIRECT_MEM_WRITE_REG] = {10,  36,    Imw_reg},
  [INDIRECT_MEM_WRITE_POP] = {10,  37,    Imw_pop},
  [REG_WRITE_REG]    		   = {10,  58,    rw_reg},
  [REG_WRITE_POP]   	     = {8,   118,   rw_pop},
};


static instruction_set* getset(instruction_type types) {
  return &set[types];
}

void recursive(int instructions, instruction_type types){
	if(split_bit(instructions, 15, getset(types)->nobits) == getset(types)->value){

    run_func function = getset(types)->func;	
	function(instructions);	
	}else{
		types++;
		recursive(instructions, types);
	}
}

void decodes(int instructions){
	recursive(instructions, 0);
}

#include <pthread.h>
#include <unistd.h>


#include "register.h"


int pc_previous, intr_rdata, intr_data0, intr_data1 = 0;
int intr_data2, split_intr_rt1, pwm_data, pwm_counter = 0;
int jpc_data, set_pc_data, data, split_intr_rt0 = 0;

bool intr_b0, intr_b1, intr_b2, intr_set0, intr_set1, intr_set2 = 0;
bool pwm_set, intr0, intr1, intr2, jump_set, pc_set, int_on = 0; 



void reg_write(regsel reg_sel, int loadfetch, bool mem) {
	if(mem == true){
		data = dm.RAM_DATA;
	}else{
		data = databus_data.MULTOUT;		
	}
    switch (reg_sel) {
    case TIMER_DATAIN:
        reg_data.TIMER_DATA = data;
		if(loadfetch > 0){
			timer_set(loadfetch);
		}
        break;
    case IO_DATAIN:
        reg_data.IO_DATA = data;
		if(loadfetch > 0){
			io_write(loadfetch);}		
        break;
    case LIFOIN:
        reg_data.LIFO_DATA = data;
		if((loadfetch == 1) | (loadfetch == 3)){
			lifo_push();}		
        break;
    case FIFOIN:
        reg_data.FIFO_DATA = data;

		if((loadfetch == 1) | (loadfetch == 3)){
			fifo_push();}			
        break;
    case IOREADIN:
        reg_data.IOREAD_DATA = data;
        reg_data.READ_CS     = loadfetch;
        port_read();

        break;
    case PC:
        set_pc_data = data;
        pc_set = true;
        break;
    case INTERRUPT:
        reg_data.INTERRUPT_DATA = data;
        break;
    default:
        0;
        break;
    }

}

void run_pc(){

    if(intr0 == true){
        intr0                     = false;
        intr1                     = false;
        intr2                     = false;
        reg_data.PC_DATA          = intr_data0;
        intr_rdata                = pc_previous + 1;
        int_on                    = true;
    }
    else if(intr1 == true){
        intr0                     = false;
        intr1                     = false;
        intr2                     = false;
        reg_data.PC_DATA          = intr_data1;
        intr_rdata                = pc_previous + 1;
        int_on                    = true;
    }
    else if(intr2 == true){
        intr0                     = false;
        intr1                     = false;
        intr2                     = false;
        reg_data.PC_DATA          = intr_data2;
        intr_rdata                = pc_previous + 1;
        int_on                    = true;
    }

    else if(split_intr_rt0 == true){
        split_intr_rt0          = false;
        reg_data.PC_DATA   = intr_rdata;        
    }

    else if(t_data.TON == true){
        reg_data.PC_DATA       = pc_previous;  
    }

    else if(pc_set == true){
        pc_set                    = false;
        reg_data.PC_DATA        = set_pc_data;         
    }
    else if(jump_set == true){
        jump_set                  = false;
        reg_data.PC_DATA        = jpc_data; 
    }
    else {
        reg_data.PC_DATA    = pc_previous + 1;

         }
    pc_previous               = reg_data.PC_DATA;
  
    pm_read();
    
}
void set_intr_rt(intr_rt){
    split_intr_rt0 = split_bit(intr_rt, 0, 0);    
    split_intr_rt1 = split_bit(intr_rt, 1, 1);
    if(split_intr_rt1 == true){
        int_on  = false; 
        split_intr_rt1 = false;   
    }

}

void run_jump(int jump);
void jump(int jump, int jump_sel){
    switch (jump_sel) {
    case 1:
        if(alu.GT == true){run_jump(jump);}
        break;
    case 2:
        if(alu.EQ == true){run_jump(jump);}
        break;
    case 3:
        if(alu.LT == true){run_jump(jump);}
        break;
    case 4:
        if(lifo_data.full == true){run_jump(jump);}
        break;
    case 5:
        if(lifo_data.empty == true){run_jump(jump);}
        break;
    case 6:
        if(fifo_data.full == true){run_jump(jump);}
        break;
    case 7:
        if(fifo_data.empty == true){run_jump(jump);}
        break;
    }   
}

void run_jump(int jump){

    int plus_minus = split_bit(jump, 0, 0);
    if(plus_minus == 1){
        jpc_data = pc_previous + jump;
    }else{jpc_data = pc_previous - jump;}
    jump_set = true; 

}

void baud_set(int baud){
    if (baud == 14) {
        reg_data.CACHE_SET = false;
    }else
     if(baud > 0){
        reg_data.CACHE_SET = true;
        reg_data.BAUD = split_bit(baud, 3, 1);
}
}

void int0_start();
void int1_start();
void int2_start();
void start_clock();

void intr_set(int intr){
    switch (intr) {
    case 1:
        intr_set0 = 0;
        break;
    case 2:
        intr_set0 = 1;
        int0_start();
        break;
    case 3:
        intr_set1 = 0;
        break;
    case 4:
        intr_set1 = 1;
        int1_start();
        break;
    case 5:
        intr_set2 = 0;
        break;
    case 6:
        intr_set2 = 1;
        int2_start();
        break;
    case 7:
        pwm_set = 0;
        break;
    case 8:
        pwm_set = 1;
        start_clock();
        break;
    case 9:
        intr_data0 = reg_data.INTERRUPT_DATA;
        break;
    case 10:
        intr_data1 = reg_data.INTERRUPT_DATA;
        break;
    case 11:
        intr_data2 = reg_data.INTERRUPT_DATA;
        break;
    case 12:
        pwm_data = reg_data.INTERRUPT_DATA;
        break;

    }   
}

void* tick(void* arg){
    while(1){
        if(pwm_data == pwm_counter){
            pwm_counter = 0;
            reg_data.FREQ_PIN = !reg_data.FREQ_PIN;
        }else {pwm_counter++;}
        if(pwm_set == 0)
        {
            pthread_exit(NULL);
        }

    }
}

void* listen0(void* arg){
    while(1){
        if(GO_FUNC.INTR0 == 1 && int_on == false){
            intr0 = true;
            sleep(5);
        }
        if(intr_set0 == 0)
        {
            pthread_exit(NULL);
        }

    }
}

void* listen1(void* arg){
    while(1){
        if(GO_FUNC.INTR1 == 1 && int_on == false){
            intr1 = true;
            sleep(5);
        }
        if(intr_set1 == 0)
        {
            pthread_exit(NULL);
        }

    }
}

void* listen2(void* arg){
    while(1){
        if(GO_FUNC.INTR2 == 1 && int_on == false){
            intr2 = true;
            sleep(5);
        }
        if(intr_set2 == 0)
        {
            pthread_exit(NULL);
        }

    }
}

void start_clock()
{
	pthread_t ptid;
	pthread_create(&ptid, NULL, &tick, &reg_data);
	pthread_join(ptid, NULL);
}

void int0_start()
{
	pthread_t ptid0;
	pthread_create(&ptid0, NULL, &listen0, &reg_data);
	pthread_join(ptid0, NULL);
}
void int1_start()
{
	pthread_t ptid1;
	pthread_create(&ptid1, NULL, &listen1, &reg_data);
	pthread_join(ptid1, NULL);
}
void int2_start()
{
	pthread_t ptid2;
	pthread_create(&ptid2, NULL, &listen2, &reg_data);
	pthread_join(ptid2, NULL);
}


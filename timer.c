#include "timer.h"

int timer_reg, up_count, counter_reg, down_count = 0;

void  timer_set(int timer_cs){
    if(timer_cs > 1){
        timer_reg = reg_data.TIMER_DATA; 
        if(timer_cs == 2){    
            up_count = 1;
            counter_reg = 0;
        }else
         if(timer_cs == 3){
                down_count = 1;
                counter_reg =  reg_data.TIMER_DATA;    
            }
    }
    while(up_count == 1){
        counter_reg++ ;
        t_data.TON =1;
        if(counter_reg == timer_reg){
            up_count = 0;
            t_data.TON =0;
            counter_reg = 0;                          
            break;
        }
    }
    while(down_count == 1){
        counter_reg-- ;
        t_data.TON =1;
        if(counter_reg == 1){
            down_count = 0;
            t_data.TON = 0;  
            counter_reg = 0;             
            break;
        }
    }
}   

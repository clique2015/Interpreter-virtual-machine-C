
#include "lifo.h"

int addr_reg = 0;
int lifo_array[7];


void lifo_push(){
    if(addr_reg == 7){
        lifo_data.full =true;
         }
        else{
            lifo_array[addr_reg] = reg_data.LIFO_DATA;
           addr_reg++;
        }
}

void  lifo_pop() {
    if(addr_reg == 0){
        lifo_data.empty =true;
         }
        else{
            lifo_data.LIFO_OUT = lifo_array[addr_reg];
           addr_reg--;
        }   
}

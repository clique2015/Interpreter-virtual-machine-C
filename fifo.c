
#include "fifo.h"
int push_point , pop_point = 0;
int fifo_array[7];


void fifo_push(){
    if(pop_point == (push_point + 1 )){
        fifo_data.full =true;
         }
        else{
            fifo_array[push_point] = reg_data.FIFO_DATA;
            push_point++;
        }
}

void  fifo_pop() {
    if(push_point == pop_point){
        fifo_data.empty =true;
        }
        else{
            fifo_data.FIFO_OUT = fifo_array[pop_point];
            pop_point++;
        }   
}


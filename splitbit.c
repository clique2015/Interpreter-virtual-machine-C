#include<stdio.h>
#include "splitbit.h"

 
 int split_bit(int value, int start, int end)
{
   int output = 0;  
   int c = 0;     
   unsigned count;
   int t = 1 << start; 
         
    for (count = 1 << 15; count > 0; count = count / 2){
        if (value & count){
           if(count <=  t){
               c = count >> end;
               output = output + c;
            }
         }
     }
    return output;
}
 
/** int main(void)
{
   int p;
   int i;

   p = split_bit(12, 3,2);

   printf( "%d\n", p);

} **/
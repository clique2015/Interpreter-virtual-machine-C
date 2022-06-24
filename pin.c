#include<stdio.h>
#include "splitbit.h"

 
 int* pin(unsigned n, unsigned f, unsigned s)
{
   static int arr[7];      
   int count = 0; 
   int cunt = 0;    
    unsigned i;
	int w = 1 << 7;
    for (i = 1; i < w; i = i * 2){
        if(count >= s && count < f){

            if (n & i){
                arr[cunt] = 1;
            }else{
                arr[cunt] = 0;
            }
            cunt++;
        }
        count++;        
    }
    return arr;
}
 
int main()
{
   int *p;
   int i;
   int arr[7];
   p = pin(12, 7,0);
   
 for(i = 0; i < 7; i++)
  {
    arr[i] = *(p+i);
   
  }
   for ( i = 0; i < 7; i++ ) {
      printf( "*(p + %d) : %d\n", i, arr[i]);
   }

}
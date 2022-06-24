#include<stdio.h>
#include "test.h"


void fpoint(){

    Point p1 = {1, 2, 3, 4, 5, 6, 7, 8};
    Point p3 = {1, 2, 3, 4, 5, 6, 7, 18};
    // p2 is a pointer to structure p1
    p2 = &p1;
    *(p2+1) = p3;
    p4.PC_DATA = 20;
    // Accessing structure members using structure pointer
    printf("%d %d", p4.PC_DATA, (p2+1)->BAUD);


}
bool GT(){
    if(databus_data.regA > databus_data.MULTOUT ){
        return true; }
    else{ return false; };    
}

bool LT(){
    if(databus_data.regA < databus_data.MULTOUT ){
        return true; }
    else{ return false; };    
}




int main()
{

GT();

}

#ifndef IOPORT_M
#define IOPORT_M


#ifndef REGISTER_H
#define REGISTER_H
#include "register.h"
#endif

#include "splitbit.h"
typedef struct {  
 int IO_DATAOUT0;
 int IO_DATAOUT1;
 int  portA[7];
 int  portB[7];
 int  portC[7];
 int  portD[7]; 

}iodata;
iodata io_data;

void io_write(int loadfetch);
int port_read();
void port_write(int port_data, int port_ddr, int port_sel);
int data_write(int data, int old_data, int port_ddr, int port_sel);
int readpin(int port_indata, int port_ddr, int port[]);
int concatenate( int dataout1, int dataout2);
#endif
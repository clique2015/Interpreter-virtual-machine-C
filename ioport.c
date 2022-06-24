
#include "ioport.h"

int portA_ddr, portB_ddr, portC_ddr, portD_ddr; 
int portA_data_reg, portB_data_reg, portC_data_reg, portD_data_reg;   
int dataout, dataout_prev, io_output_sel;
int calc0, calc1, dataoutA, dataoutB, dataoutC, dataoutD, dataout0, dataout1, PORT0, PORT1;

void io_write( int loadfetch) {
    if (loadfetch == 3) {
        int cases = split_bit(reg_data.IO_DATA, 1, 0);
        switch (cases) {
        case 0:
            portA_ddr = split_bit(reg_data.IO_DATA, 15, 8);
            port_write(portA_data_reg, portA_ddr, cases);
            break;
        case 1:
            portB_ddr = split_bit(reg_data.IO_DATA, 15, 8);
            port_write(portB_data_reg, portB_ddr, cases);
            break;
        case 2:
            portC_ddr = split_bit(reg_data.IO_DATA, 15, 8);
            port_write(portC_data_reg, portC_ddr, cases);
            break;
        case 3:
            portD_ddr = split_bit(reg_data.IO_DATA, 15, 8);
            port_write(portD_data_reg, portD_ddr, cases);
            break;
        }
    }
    else if (loadfetch == 1) {
        int cases = split_bit(reg_data.IO_DATA, 1, 0);
        switch (cases) {
        case 0:
            portA_data_reg = data_write(reg_data.IO_DATA, portA_data_reg, portA_ddr, cases);
            break;
        case 1:
            portB_data_reg = data_write(reg_data.IO_DATA, portB_data_reg, portB_ddr, cases);
            break;
        case 2:
            portC_data_reg = data_write(reg_data.IO_DATA, portC_data_reg, portC_ddr, cases);
            break;
        case 3:
            portD_data_reg = data_write(reg_data.IO_DATA, portD_data_reg, portD_ddr, cases);
            break;
        }
    }
}
void port_write(int port_data, int port_ddr, int port_sel){
    int w = 1 << 7;
    int count = 0;
    for (int i = 1; i < w; i = i * 2){
        if ((port_ddr & i)){
            if(port_data & i){
                switch (port_sel) {
                    case 0:
                        io_data.portA[count] = 1;
                        break;
                    case 1:
                        io_data.portB[count] = 1;
                        break;
                    case 2:
                        io_data.portC[count] = 1;
                        break;
                    case 3:
                        io_data.portD[count] = 1;
                        break;
                }
            }else{ 
                switch (port_sel) {
                    case 0:
                        io_data.portA[count] = 0;
                        break;
                    case 1:
                        io_data.portB[count] = 0;
                        break;
                    case 2:
                        io_data.portC[count] = 0;
                        break;
                    case 3:
                        io_data.portD[count] = 0;
                        break;
                }
            }
         }
         count++ ;
    }
    
}

int data_write(int data, int old_data, int port_ddr, int port_sel){
    int sel_data = 255 << split_bit(data, 4, 2);
    sel_data  = sel_data >> split_bit(data, 7, 5);
    int in_data = split_bit(data, 15, 8) << (split_bit(data, 4, 2) - split_bit(data, 7, 5));
    int w = 1 << 7;
    int count = 0;
    for (int i = 1; i < w; i = i * 2){
        if (sel_data & i){
            if((in_data & i) != (old_data & i)){
              if((in_data & i)){  
                  old_data + i;
                  if(port_ddr & i){
                    switch (port_sel) {
                        case 0:
                            io_data.portA[count] = 1;
                            break;
                        case 1:
                            io_data.portB[count] = 1;
                            break;
                        case 2:
                            io_data.portC[count] = 1;
                            break;
                        case 3:
                            io_data.portD[count] = 1;
                            break;
                        }
              }
              else{
                  old_data - i;
                  if(port_ddr & i){
                    switch (port_sel) {
                        case 0:
                            io_data.portA[count] = 0;
                            break;
                        case 1:
                            io_data.portB[count] = 0;
                            break;
                        case 2:
                            io_data.portC[count] = 0;
                            break;
                        case 3:
                            io_data.portD[count] = 0;
                            break;
                    }
                      }
              }
            }
         }
         count++ ;
    }
return old_data;
    }
}



int concatenate( int dataout1, int dataout2){
    char s1[20];
    char s2[20];
 
    sprintf(s1, "%d", dataout1);
    sprintf(s2, "%d", dataout2);
 
    strcat(s1, s2);
    int output = atoi(s1);
    return output;
}

int readpin(int port_indata, int port_ddr, int port[]){
    int data;
    int count = 0;
    int w = 1 << 7;
    for (int i = 1; i < w; i = i * 2){
        if ((port_ddr & i) && (port_indata & i)){
            data = data + i;
        }else
             if(!(port_ddr & i) && (port[count] & i)){
            data = data + i;
            }
        count++;
    }
            
return data;
}

int port_read(){

    dataoutA   = readpin(portA_data_reg, portA_ddr, io_data.portA);
    dataoutB   = readpin(portB_data_reg, portB_ddr, io_data.portB); 
    dataoutC   = readpin(portC_data_reg, portC_ddr, io_data.portC);
    dataoutD   = readpin(portD_data_reg, portD_ddr, io_data.portD);

    switch (reg_data.READ_CS) {
        case 0:
            int PORT1  = concatenate(dataoutA, dataoutB);
            int PORT2  = concatenate(dataoutA, dataoutB);  
            break;
        case 1:
            int PORT1  = concatenate(dataoutA, dataoutB);
            int PORT2  = concatenate(dataoutC, dataoutD);  
            break;
        case 2:
            int PORT1  = concatenate(dataoutC, dataoutD); 
            int PORT2  = concatenate(dataoutA, dataoutB); 
            break;
        case 3:
            int PORT1  = concatenate(dataoutC, dataoutD);  
            int PORT2  = concatenate(dataoutC, dataoutD);  
            break;
    }  

    calc0 = (15 - split_bit(reg_data.IOREAD_DATA, 3, 0));
    calc1 = (15 - split_bit(reg_data.IOREAD_DATA, 11, 8));

    dataout0 = PORT0 << calc0;
    dataout1 = PORT1 << calc1;

    io_data.IO_DATAOUT0 = dataout0 >> (calc0 + split_bit(reg_data.IOREAD_DATA, 7, 4));
    io_data.IO_DATAOUT1 = dataout1 >> (calc1 + split_bit(reg_data.IOREAD_DATA, 15, 12));

}










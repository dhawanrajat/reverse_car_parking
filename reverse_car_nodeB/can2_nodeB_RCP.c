/*  Reverse Car Parking ECU  */
#include <LPC21xx.H>
#include"header.h"

#define TRIG (1<<5)				//---> connect trig to P0.5 

CAN2 v1,v2;
unsigned char flag;        		// to monitor can2 interrupt
int main(){
	IODIR0|=TRIG;

	can2_init();
	uart0_init(9600);

	config_vic_for_can2();
	en_can2_interrupt();

	while(1){
		if(flag){
			flag=0;
			if(v1.rtr){
				v2.id=v1.id;
				v2.dlc=v1.dlc;
				v2.rtr=0;	
				while(1){
					if(flag){
						flag=0;
						if(v1.rtr==0)
							break;
					}
					v2.byteA=read_distance();
					can2_tx(v2);
					delay_ms(50);
				}
			}
		}
	}
}

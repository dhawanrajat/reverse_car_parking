/*  Reverse Car Parking  */
#include<LPC21xx.H>
#include"header.h"

#define LED (1<<17)			//Reverse gear LED
#define BUZ (1<<21)			//---> for Buzzer

CAN2 v1,v2;
unsigned char gear,flag,tc,tb;
int main(){
	IODIR0|=LED|BUZ;		//output direction for LED and Buzzer
	IOSET0|=LED;			//turning off LED
	IOCLR0|=BUZ;			//turning off Buzzer
	
	can2_init();
	uart0_init(9600);

	config_vic_for_timer1();
	en_timer1_interrupt();

	config_vic_for_ext0();
	en_ext0_interrupt();

	config_vic_for_can2();
	en_can2_interrupt();

	v2.dlc=2;
	uart0_tx_string("YES\r\n");
	while(1){
		if(gear){
			gear=0;
			uart0_tx_string("GON\r\n");
			IOCLR0|=LED;
			
			v2.id=0x2FA;
			v2.rtr=1;
			v2.byteA=0x10;
			can2_tx(v2);
			tc=1;
            tb=0;
			T1TC=0;
			T1TCR=1;

			while(1){
				if(gear){                       
					gear=0;
					uart0_tx_string("GOFF\r\n");
					IOSET0|=LED;
					IOCLR0|=BUZ;
					v2.id=0x2FB;
					v2.rtr=0;
					v2.byteA=0x11;
					T1TCR=0;
					can2_tx(v2);
					tc=1;
					tb=0;
					break;
				}
				if(flag){
					flag=0;
					//uart0_tx_string("UREC\r\n");
					uart0_integer(v1.byteA);
					uart0_tx_string("\r\n");
					if(v1.byteA>400){
						if(tc){
							tb=0;
							IOCLR0|=BUZ;
							T1TCR=0;
						}
					}
					else if(v1.byteA<=49){
						if(tc){
							tb=0;
							IOSET0|=BUZ;
							T1TCR=0;
						}
					}
					else{
						if(tc){
							if(tb==0){
                                tb=1;
								IOCLR0|=BUZ;
								T1TC=0;
								T1TCR=1;
							}
						}
					}
					if(tb){
						if(v1.byteA>=300 && v1.byteA<=400){
							T1MR0=1000;
						}
						else if(v1.byteA>=200 && v1.byteA<=299){
							T1MR0=500;
						}
						else if(v1.byteA>=100 && v1.byteA<=199){
							T1MR0=100;
						}
						else if(v1.byteA>=50 && v1.byteA<=99){
							T1MR0=50;
						}
					}
				}
			}
		}
	}
}

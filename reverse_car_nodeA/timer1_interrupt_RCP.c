#include<lpc21xx.h>
#include"header.h"

#define BUZ (1<<21)		//---> for Buzzer

unsigned char buz;

/*  ISR for RCP program  */
void timer1_handler(void) __irq{
    if(buz){
        IOSET0|=BUZ;
        buz=0;
    }
    else{
        IOCLR0|=BUZ;
        buz=1;
    }
	T1IR=1;
	VICVectAddr=0;
}

void config_vic_for_timer1(void){
	VICIntSelect=0;
	VICVectCntl1=5|(1<<5);
	VICVectAddr1=(unsigned int)timer1_handler;
	VICIntEnable|=(1<<5);
}

/*  Timer1 interrupt for RCP program  */
void en_timer1_interrupt(void){
	T1PC=0;
	T1MCR=3;
	T1PR=60000-1;
	T1TC=0;
}

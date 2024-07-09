/*  External Interrupt  */
#include"header.h"
#include<lpc21xx.h>

extern unsigned char gear;                  //flag for gear
void ext0_handler(void) __irq{
	gear=1;
	EXTINT=1;
	VICVectAddr=0;
}
void config_vic_for_ext0(void){
	VICIntSelect=0;
	VICVectCntl0=14|(1<<5);		
	VICVectAddr0=(unsigned int)ext0_handler;
	VICIntEnable|=1<<14;
}

void en_ext0_interrupt(void){
	PINSEL1|=1;		//p0.16 ==> EINT0
	EXTMODE|=1;		//Select edge sensitivity
	EXTPOLAR=0;		//Active low for Falling edge
}

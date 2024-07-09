/*  Ultrasonic Sensor Driver  */
#include <LPC21xx.H>
#include"header.h"

#define TRIG (1<<5)				//---> connect trig to P0.5 
#define ECHO ((IOPIN0>>6)&1)	//---> connect echo to P0.6

float read_distance(void){
	unsigned int p;
	float dist;
	
	//VPBDIV=1;
	IOSET0|=TRIG;
	delay_us(10);
	IOCLR0|=TRIG;
		
	T1PC=0;
	//T1PR=15-1;
	T1PR=60-1;
	T1TC=0;

	while(ECHO==0);

	T1TCR=1;

	while(ECHO){
		if(T1TC>25000)
			break;
	}
	T1TCR=0;
	
	//p=T1TC*1000;			//convert into microsecond
	p=T1TC;
	dist=((float)p*0.0343)/2;
	//dist=(float)p/58;
	return dist;
}

#include<LPC21XX.H>
void delay_sec(const unsigned int sec){
	unsigned int vpbdiv;
	unsigned int pclk;
	int a[]={15,60,30,15};
	
	if(VPBDIV>3){
		vpbdiv=VPBDIV%4;
	}
	else{
	vpbdiv=VPBDIV;
	}
	pclk=a[vpbdiv]*1000000-1;
	T0PC=0;
	T0PR=pclk;
	T0TC=0;
	T0TCR=1;
	while(T0TC<sec);
	T0TCR=0;
}

void delay_ms(const unsigned int ms){
	unsigned int vpbdiv;
	unsigned int pclk;
	
	int a[]={15,60,30,15};	

	if(VPBDIV>3){
		vpbdiv=VPBDIV%4;
	}
	else{
		vpbdiv=VPBDIV;
	}

	pclk=a[vpbdiv]*1000-1;
	T0PC=0;
	T0PR=pclk;
	T0TC=0;
	T0TCR=1;
	while(T0TC<ms);
	T0TCR=0;
}
void delay_us(const unsigned int us){
	unsigned int vpbdiv;
	unsigned int pclk;
	int a[]={15,60,30,15};
	
	if(VPBDIV>3){
		vpbdiv=VPBDIV%4;
	}
	else{
		vpbdiv=VPBDIV;
	}
	pclk=a[vpbdiv]-1;
	T0PC=0;
	T0PR=pclk;
	T0TC=0;
	T0TCR=1;
	while(T0TC<us);
	T0TCR=0;
}

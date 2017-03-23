#define F_CPU 8000000UL
#include <avr/io.h>

#include "USART_128.h"
#include <avr/sfr_defs.h>
int a[7]={0};
float err,last_err,cnt1=0,pidcalc=0,left_rpm,right_rpm;;
#define ki 0

#define kp 6000.0
#define kd 0

void read_sensor() {
	int i;
	for(i=0;i<7;i++)
		{
		if(bit_is_set(PINC,i))
			{
			a[i]=1;
			
			}
			else
			{
			a[i]=0;
			}
		}
	}

void error() {
	if(((a[0])+a[3]+(a[1])+(a[2])+(a[4])+(a[5])+(a[6]))>=4)
	{
	err=(float)((-18*a[0])+(-12*a[1])+(-6*a[2])+(6*a[4])+(12*a[5])+(18*a[6]))/((a[0])+a[3]+(a[1])+(a[2])+(a[4])+(a[5])+(a[6]));
	//err=(-9*a[0])+(-4*a[1])+(-1*a[2])+(1*a[4])+(4*a[5])+(9*a[6])/((a[0])+(a[1])+(a[2])+(a[4])+(a[5])+(a[6]));
	}
	//if(((a[0])+a[3]+(a[1])+(a[2])+(a[4])+(a[5])+(a[6]))==3)
	//{
	//err=(float)((-9*a[0])+(-6*a[1])+(-3*a[2])+(3*a[4])+(6*a[5])+(9*a[6]))/((a[0])+a[3]+(a[1])+(a[2])+(a[4])+(a[5])+(a[6]));
	//}//err=(-9*a[0])+(-4*a[1])+(-1*a[2])+(1*a[4])+(4*a[5])+(9*a[6])/((a[0])+(a[1])+(a[2])+(a[4])+(a[5])+(a[6]));
	
	if(((a[0])+a[3]+(a[1])+(a[2])+(a[4])+(a[5])+(a[6]))<4&&((a[0])+a[3]+(a[1])+(a[2])+(a[4])+(a[5])+(a[6]))>=0)
	err=(float)((-3*a[0])+(-2*a[1])+(-1*a[2])+(1*a[4])+(2*a[5])+(3*a[6]))/((a[0])+a[3]+(a[1])+(a[2])+(a[4])+(a[5])+(a[6]));
	
	//if(((a[0])+a[3]+(a[1])+(a[2])+(a[4])+(a[5])+(a[6]))==0)
	//err=last_err;
	

}

void pwm() {
	DDRB=0xFF;
	TCCR1A |= 1<<WGM11 | 1<<COM1A1| 1<<COM1B1;
	TCCR1B |= 1<<WGM12  | 1<<WGM13 | 1<<CS11;
	ICR1=20000;
}

void pid(float err) {
	
	pidcalc=(kp*err+kd*(err-last_err));

	last_err=err;
}


int main(void)
{
	DDRC=0b00000000;
	DDRD|=(1<<PD4)|(1<<PD5)|(1<<PD6)|(1<<PD7) | 1<<PD0;
	DDRA=0xFF;
	PORTA|= (1<<PA3) | (1<<PA1) | (0<<PA0) | (0<<PA2);
	TIMSK|=(1<<OCIE0);
	TIFR|=(1<<OCF0);
	TCCR0|=(1<<CS01)|(1<<CS00)|(1<<COM01)|(1<<WGM01);
	USART_Init(51,0);
	pwm();
	sei();
	OCR0=25;
 	PORTD=0b01010000;

		while(1)
		{
//USART_Transmitchar(" ");
USART_Transmitchar(0x0D,0);
USART_TransmitNumber(err,0);
USART_Transmitchar(0x0D,0);

USART_TransmitNumber(OCR1A,0);
USART_Transmitchar('B',0);
USART_TransmitNumber(OCR1B,0);
//USART_Transmitchar(" ");*/
		}
}

ISR(TIMER0_COMP_vect) {
	read_sensor();
	error();
	pid(err);
	if(err==0)
	{
		OCR1A=20000;
		OCR1B=20000;
	}
	else
	{	
		
		//OCR1A=10000;
		left_rpm=10000-pidcalc;
		right_rpm=10000+pidcalc;
		
		
		
		
		if(right_rpm<0)
		{
			PORTD|=1<<PD5;
			PORTD&=~(1<<PD4);	
			//right_rpm=15000;
			right_rpm=-right_rpm;
		
		}
		else{
			PORTD|=1<<PD4;
			PORTD&=~(1<<PD5);	
		}
		
		if(left_rpm<0)
		{
			PORTD|=1<<PD0;
			PORTD&=~(1<<PD6);	
			//right_rpm=15000;
			left_rpm=-left_rpm;
		
		}
		else{
			PORTD|=1<<PD6;
			PORTD&=~(1<<PD0);	
		}
						
		
		
		if(left_rpm>20000) left_rpm=20000;
		if(right_rpm>20000) right_rpm=20000;
		
		OCR1A=left_rpm;
		OCR1B=right_rpm;
		
		/*if(((a[0])+a[3]+(a[1])+(a[2])+(a[4])+(a[5])+(a[6]))>=4&&err>0)
		{
			OCR1A=20000;
			OCR1B=20000;
			PORTD|=1<<PD4;
			PORTD&=~(1<<PD5);	
			PORTD|=1<<PD0;
			PORTD&=~(1<<PD6);
		
			
		}
		if(((a[0])+a[3]+(a[1])+(a[2])+(a[4])+(a[5])+(a[6]))>=4&&err<0)
		{
			OCR1A=20000;
			OCR1B=20000;
			PORTD|=1<<PD6;
			PORTD&=~(1<<PD0);
			PORTD|=1<<PD5;
			PORTD&=~(1<<PD4);	
			
		}*/
		/*if(((a[0])+a[3]+(a[1])+(a[2])+(a[4])+(a[5])+(a[6]))==0 && err>0)
	{
	PORTD|=1<<PD0;
	PORTD&=~(1<<PD6);	
	PORTD|=1<<PD4;
	PORTD&=~(1<<PD5);	
	OCR1A=15000;
	OCR1B=15000;
						
	}
		if(((a[0])+a[3]+(a[1])+(a[2])+(a[4])+(a[5])+(a[6]))==0 && err<0)
	{
	PORTD|=1<<PD6;
	PORTD&=~(1<<PD0);	
	PORTD|=1<<PD5;
	PORTD&=~(1<<PD0);	
	OCR1A=15000;
	OCR1B=15000;
				
	}*/
	
	}

}



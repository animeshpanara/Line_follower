/*
 * GccApplication7.c
 *
 * Created: 2/18/2016 6:59:52 PM
 *  Author: ABCD
 */ 


#include <avr/io.h>

int a1,b1,c1,d1,e1,a,b,c,d,e,tp;
void rs()
{
	a1=PINB&0b01000000;
	if(a1==0b01000000)
	a=0;
	else
	a=1;
	b1=PINB&0b00100000;
	if(b1==0b00100000)
	b=0;
	else
	b=1;
	c1=PINB&0b00010000;
	if(c1==0b00010000)
	c=0;
	else
	c=1;
	d1=PINB&0b00001000;
	if(a1==0b00001000)
	d=0;
	else
	d=1;
	e1=PINB&0b00000100;
	if(e1==0b00000100)
	e=0;
	else
	e=1;
	
}
void pwm()
{
TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
TCCR1B |= 1<<WGM12  | 1<<WGM13 |1<<CS10;
ICR1=20000;
}
void right()
{
OCR1A=100000;
OCR1B=100000;	
PORTD=0b00111000;
tp=1;
}
void left()
{
	OCR1A=100000;
	OCR1B=100000;
	PORTD=0b00110001;
    tp=2;
}
void straight()
{
OCR1A=200000;
OCR1B=200000;
PORTD=0b00111001;
tp=3;
}
void sleft()
{
	OCR1A=200000;
	OCR1B=200000;
    PORTD=0b00110101;
    tp=4;
}
void sright()
{
OCR1A=200000;
OCR1B=200000;
PORTD=0b00111010;
tp=5;
}

void leftn()
{
	OCR1A=100000;
	OCR1B=200000;
	PORTD=0b00111001;
	tp=3;
}

void rightn()
{
	OCR1A=200000;
	OCR1B=100000;
	PORTD=0b00111010;
	tp=3;
}

int main(void)
{
	
	DDRB=0b00000000;
	DDRD=0b00111111;
    while(1)
    {
    rs();
	pwm();
	if((a==0 && b==0 && c==1 && d==0 && e==0))
	{
	straight();
	}
	else if((a==0 && b==0 && c==0 && d==0 && e==0 && tp==2)||(a==0 && b==0 && c==0 && d==0 && e==0 && tp==4))    //TODO:: Please write your application code 
    {
		sleft();
	}
	else if((a==0 && b==0 && c==0 && d==0 && e==0 && tp==1)||(a==0 && b==0 && c==0 && d==0 && e==0 && tp==5))    //TODO:: Please write your application code
	{
		sright();
	}
	else if((a==1 && b==0 && c==0 && d==0 && e==0)||(a==1 && b==1 && c==0 && d==0 && e==0)||(a==1 && b==1 && c==1 && d==0 && e==0))
	{
		left();
	}
	else if((a==0 && b==0 && c==0 && d==0 && e==1)||(a==0 && b==0 && c==0 && d==1 && e==1)||(a==0 && b==0 && c==1 && d==1 && e==1))
	{
		right();
	}
	else if((a==0 && b==1 && c==1 && d==0 && e==0)||(a==0 && b==1 && c==0 && d==0 && e==0))
	{
		leftn();
	}
	else if((a==0 && b==0 && c==1 && d==1 && e==0)||(a==0 && b==0 && c==0 && d==1 && e==0))
	{
		rightn();
	}
	else if((a==1 && b==1 && c==1 && d==1 && e==1))
	{
		straight();
	}
	}
	}

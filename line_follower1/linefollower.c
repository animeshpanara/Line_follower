#include <avr/io.h>       // include avr header file
#include <util/delay.h>   // include delay header file


int main(void)  		  // main function
{
DDRA=0b00000000;          // declare PortA as a input port connected to the sensors
DDRB=0b00001111;          // declare PortB as a output port connected to the motors

int s4,s5,left_sensor=0, right_sensor=0,ms=0,tp;

while(1)
{ // infinite loop
	s5=PINA&0b10000000;
	left_sensor=PINA&0b01000000;    // mask PA4 bit of Port A
	right_sensor=PINA&0b00010000;
	ms=PINA&0b00100000;   // mask PA5 bit of Port A
	s4=PINA&0b00001000;



	 
	if((s5==0b00000000) && (s4==0b00000000) && (left_sensor==0b00000000) && (right_sensor==0b00000000) && (ms==0b00000000) && (tp==2))     // if both sensors "off"
		{
		PORTB=0b00001010;   // stop	
		}
		else if((s5==0b00000000) && (s4==0b00000000) && (left_sensor==0b00000000) && (right_sensor==0b00000000) && (ms==0b00000000) && (tp==1))     // if both sensors "off"
		{
		PORTB=0b00000101;   // stop	
		}
	
		else if((s5==0b10000000) && (s4==0b00010000) && (left_sensor==0b01000000) && (right_sensor==0b00001000) && (ms==0b00100000))     // if both sensors "off"
		{
		PORTB=0b00000000;   // stop	
		}

    else if((s5==0b00000000) && (s4==0b00000000) && (left_sensor==0b00000000) && (right_sensor==0b00000000) && (ms==0b00100000))     // if both sensors "on"
		{
        PORTB=0b00001001;  // move straight
		}
			
	else if((s5==0b00000000) && (s4==0b00000000) && (left_sensor==0b01000000) && (right_sensor==0b00000000) && (ms==0b00100000)) 	// if left sensor off but right sensor on
        {
		PORTB=0b00000001;
		tp=1; // turn left
        }
	else if((s5==0b00000000) && (s4==0b00000000) && (left_sensor==0b01000000) && (right_sensor==0b00000000) && (ms==0b00000000)) 	// if left sensor off but right sensor on
        {
		PORTB=0b00000001;
		tp=1; // turn left
        }
	
	else if((s5==0b10000000) && (s4==0b00000000) && (left_sensor==0b01000000) && (right_sensor==0b00000000) && (ms==0b00100000)) 	// if left sensor off but right sensor on
        {
		PORTB=0b00000001;
		tp=1; // turn left
        }
		else if((s5==0b10000000) && (s4==0b00000000) && (left_sensor==0b01000000) && (right_sensor==0b00000000) && (ms==0b00000000)) 	// if left sensor off but right sensor on
        {
		PORTB=0b00000001;
		tp=1; // turn left
        }


	else if((s5==0b00000000) && (s4==0b00001000) && (left_sensor==0b00000000) && (right_sensor==0b00010000) && (ms==0b00100000))  ////if left sensor on but right sensor off
        {
		PORTB=0b00001000;
		tp=2; // turn right
		}
	else if((s5==0b00000000) && (s4==0b00001000) && (left_sensor==0b00000000) && (right_sensor==0b00010000) && (ms==0b00000000))  ////if left sensor on but right sensor off
        {
		PORTB=0b00001000;
		tp=2; // turn right
		}
	else if((s5==0b00000000) && (s4==0b00000000) && (left_sensor==0b00000000) && (right_sensor==0b00010000) && (ms==0b00000000))
		{
		PORTB=0b00001000;
		tp=2;  //TURN RYT
		} 
	
	else if((s5==0b00000000) && (s4==0b00000000) && (left_sensor==0b00000000) && (right_sensor==0b00010000) && (ms==0b00100000))
		{
		PORTB=0b00001000;
		tp=2;  //TURN RYT
		}
		 
	else if((s5==0b10000000) && (s4==0b00000000) && (left_sensor==0b00000000) && (right_sensor==0b00000000) && (ms==0b00000000))  ////if left sensor on but right sensor off
        {
		PORTB=0b00000101;
		tp=1; // turn  sharp 
		}
	else if((s5==0b00000000) && (s4==0b00001000) && (left_sensor==0b00000000) && (right_sensor==0b00000000) && (ms==0b00000000))  ////if left sensor on but right sensor off
        {
		PORTB=0b00001010;
		tp=2; // turn sharp 
		}
		else
		{
		PORTB=0b00001001;
		}
}      

}         //  main closed


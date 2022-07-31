/*
 * receiver.c
 *
 * Created: 7/29/2022 11:27:43 PM
 * Author : Dell
 */ 

#include <avr/io.h>
#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

char ReceivePassword(void);
void TransmitStatus(int status);


int main(void)
{
	char match = '5'; //original password
	//receiving and transmission declarations
	UBRR0H = 0X00;
	UBRR0L = 0X05;
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	DDRD&=~(1<<PD0);
	DDRD|=1<<PD1;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	char pass;
	DDRA=0xFF;
	PORTA=0b11000110;
	
	//PUSH Button declaration
	DDRB = 0x00;
	int push_button;
	
	//main declarations
	int status=0b11000110; //door status

	
	TransmitStatus(status);
	/* Replace with your application code */
	while (1)
	{
		pass=ReceivePassword();
		push_button=(PINB&0x01);
		PORTC=0;
		if (push_button==0) //if push button is not pressed and password matches original password unlatch the door
		{
			if (pass==match) //matching received password with original password
			{
				//Rotate Motor to 90 degree
				PORTC = 0x01;
				_delay_ms(1500);
				PORTC = 0x00;
				_delay_ms(2000);
				status=0b11000000;
			}
		}
		else //if push button is pressed latch the door
		{
			status=0b11000110;
		}
		TransmitStatus(status);
	}
}

char ReceivePassword(void){
	//receiver declarations
	PORTC=0;
	char receivePassword=0;
	while (!(UCSR0A&(1<<RXC0)));
	receivePassword=UDR0;
	_delay_ms(1000);
	return receivePassword;
}

void TransmitStatus(int status)
{
	//transmitter declarations
	//transmission code
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0 = status;
	_delay_ms(1000);
}


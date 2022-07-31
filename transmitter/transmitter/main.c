/*
 * transmitter.c
 *
 * Created: 7/29/2022 11:25:27 PM
 * Author : Dell
 */ 



#include <avr/io.h>
#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

int GetKeyPressed(void);
void TransmitPassword(char password);
int ReceiveStatus(void);

int main(void)
{
	//keypad declarations
	char digit[20]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','\0'};
	DDRD = 0x0F;
	DDRC = 0x00;
	DDRB = (1<<PINB1);
	int key;
	char password = digit[16];
	
	//receiving and transmission declarations
	UBRR0H = 0X00;
	UBRR0L = 0X05;
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	DDRD|=1<<PD1;
	DDRD&=~(1<<PD0);
	PORTD|=1<<PD0;
	//int UBBRValue=25;
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);

	
	//main declarations
	int receiveData;
	DDRA=0xFF;
	PORTA=0b11000110;
	
	TransmitPassword(password);
	/* Replace with your application code */
	while (1)
	{
		receiveData = ReceiveStatus();
		PORTA=receiveData;
		key = GetKeyPressed();
		if (key!=16){
			password = digit[key];
		}
		TransmitPassword(password);
	}
}

int GetKeyPressed(void)
{
	char x;
	PORTB=0x00;
	int data;
	x = PINC;
	if (x==0x01)
	{
		data = ((PIND>>4)&0x0F);
		return data;
	}
	return 16;
}


void TransmitPassword(char password)
{
	//transmitter declarations
	//transmission code
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0 = password;
	_delay_ms(1000);
}

int ReceiveStatus(void){
	//receiver declarations
	//DDRD&=~(1<<PD0);
	//DDRD|=1<<PD1;
	//UCSR0B = (1<<RXEN0);
	PORTC=0;
	int receiveData=0;
	while (!(UCSR0A&(1<<RXC0)));
	receiveData=UDR0;
	_delay_ms(1000);
	return receiveData;
}
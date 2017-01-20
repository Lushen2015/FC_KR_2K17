/*
 * Knight_Rider.c
 *
 * Created: 18-Jan-17 11:44:33 AM
 *  Author: Lushen
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>

char pt1[]= {0b00000001,0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000};
char pt3[]= {0b00000001,0b00000011,0b00000111,0b00001111,0b00011111,0b00111111,0b01111111,0b11111111};


void PT1() //This is the trailing LED pattern, just shifts to the right
{
	int var=50;
	int j=7;
	for(int i=0;i<8;i++)
	{
		PORTA=pt1[i];
		_delay_ms(var);	
	}
 	PORTA=0x00;
 	while(j>=0)
	 {
		 PORTC=pt1[j];
		 _delay_ms(var);
		 j--;
	 }
	 PORTC=0x00;
} 

void PT2()//This is the bouncing from one end to the other pattern, a variation of the first pattern
{
	double var=50;
	int j=7;
	int k=7;
	for(int i=0;i<8;i++)
	{
		PORTA=pt1[i];
		_delay_ms(var);
	}
	PORTA=0x00;
	while(j>=0)
	{
		PORTC=pt1[j];
		_delay_ms(var);
		j--;
	}
	PORTC=0x00;
	
	for(int i=0;i<8;i++)
	{
		PORTC=pt1[i];
		_delay_ms(var);
	}
	PORTC=0x00;
	while(k>=0)
	{
		PORTA=pt1[k];
		_delay_ms(var);
		k--;
	}
	PORTA=0x00;
}

void PT3()//This is a breathing from either side pattern 
{
double var =70;
for(int i=0;i<8;i++)
{
 PORTA=pt3[i];
 PORTC=pt3[i];	
 _delay_ms(var);
}
int j=7;
while(j>=0)
{
	PORTA=pt3[j];
	PORTC=pt3[j];
	_delay_ms(var);
	j--;
}


}

void PT4()//This is a breathing pattern that gradually increases 
{
	for(int i=0;i<8;i++)
	{
		Breathe(i);
	}
}

void Breathe(int stop)//sub method for Pattern 4, it lights up n LEDs and turns off n LEDs
{
	double var=60;
	for(int i=0;i<stop+1;i++)
	{
		PORTA=pt3[i];
		PORTC=pt3[i];
		_delay_ms(var);
	}
	int j=stop;
	while(j>=0)
	{
		PORTA=pt3[j];
		PORTC=pt3[j];
		_delay_ms(var);
		j--;
	}
	
}

void PT5()//Similar to Pattern 3,just with a single trailing LED
{
	double var =50;
	for(int i=0;i<8;i++)
	{
		PORTA=pt1[i];
		PORTC=pt1[i];
		_delay_ms(var);
	}
	int j=7;
	while(j>=0)
	{
		PORTA=pt1[j];
		PORTC=pt1[j];
		_delay_ms(var);
		j--;
	}
}


int main(void)
{
	DDRC=0xff;
	DDRA=0xff;
	DDRD=0x00;//This makes last pin of PORTD an input

	
while(1)
{
	PT2();
	//_delay_ms(20);
}

}
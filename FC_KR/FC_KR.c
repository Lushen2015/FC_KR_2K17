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


#define KEYPAD_PORT PORTD  
#define KEYPAD_DDR   DDRD
#define KEYPAD_PIN   PIND

char pt1[]= {0b00000001,0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000};
char pt3[]= {0b00000001,0b00000011,0b00000111,0b00001111,0b00011111,0b00111111,0b01111111,0b11111111};

#define LCD_DPRT PORTA
#define LCD_DDDR DDRA
#define LCD_DPIN PINA
#define LCD_CPRT PORTB
#define LCD_CDDR DDRB
#define LCD_CPIN PINB
#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 3

#define pad PORTD
#define r1 PD0
#define r2 PD1
#define r3 PD2
#define r4 PD3

#define c1 PD4
#define c2 PD5
#define c3 PD6

void check1(void);
void check2(void);
void check3(void);
void check4(void);

unsigned int press;



/***************************************************************
LCD INITAILISING
****************************************************************/
void lcdCommand(unsigned char cmnd)
{
	LCD_DPRT = cmnd;
	LCD_CPRT &= ~ (1<<LCD_RS);
	LCD_CPRT &= ~ (1<<LCD_RW);
	LCD_CPRT |= (1<<LCD_EN);
	_delay_us(1);
	LCD_CPRT &= ~ (1<<LCD_EN);
	_delay_us(100);
}

void LcdData (unsigned char data)
{
	_delay_us(100);
	LCD_DPRT = data;
	LCD_CPRT |=  (1<<LCD_RS);
	LCD_CPRT &= ~ (1<<LCD_RW);
	LCD_CPRT |= (1<<LCD_EN);
	_delay_us(1);
	LCD_CPRT &= ~ (1<<LCD_EN);
	_delay_us(100);
}

void lcd_init()
{
	_delay_ms(20);
	LCD_DDDR = 0xFF;
	LCD_CDDR = 0xFF;
	
	LCD_CPRT &= ~(1<<LCD_EN);
	_delay_us(2000);
	lcdCommand(0x38);
	lcdCommand(0x0C);
	lcdCommand(0x01);
	lcdCommand(0x06);
	lcdCommand(0x07);
	
}

void lcd_print(char *str)
{
	unsigned char i=0;
	while(str[i] !=0)
	{
		_delay_ms(4);
		LcdData(str[i]);
		i++;
	}
}
/*****************************************************************
*****************************************************************/

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

//////////////////////////////////////////////////////////////////////////////////////////////////////

char* arr;
void check1(void)
{
	//DDRD = 0xf0;
	pad =0b11111110;
	//pad &= (0<<r1);
	_delay_us(10);
	if(bit_is_clear(PIND,c1))
	arr = "1";
	else if(bit_is_clear(PIND,c2))
	arr = "2";
	else if(bit_is_clear(PIND,c3))
	arr = "3";
}


void check2(void)
{
	pad=0b11111101;
	//pad &= (0<<r2);
	_delay_us(10);
	if(bit_is_clear(PIND,c1))
	arr = "4";
	else if(bit_is_clear(PIND,c2))
	arr = "5";
	else if(bit_is_clear(PIND,c3))
	arr = "6";
}

void check3(void)
{
	pad=0b11111011;
	//pad &= (0<<r3);
	_delay_us(10);
	if(bit_is_clear(PIND,c1))
	 arr = "7";
	else if(bit_is_clear(PIND,c2))
	arr = "8";
	else if(bit_is_clear(PIND,c3))
	arr = "9";
}

void check4(void)
{
	pad =0b11110111;
	//pad &= (0<<r4);
	_delay_us(10);
	if(bit_is_clear(PIND,c1))
	arr = "*";
	else if(bit_is_clear(PIND,c2))
	arr = "0";
	else if(bit_is_clear(PIND,c3))
	arr = "#";
}












///////////////////////////////////////////////////////////////////////////////////////////////////////    
int main(void)
{
	DDRC=0xff;
	DDRA=0xff;
	 unsigned char value;
	lcd_init();
	DDRD=0x0F;
	pad=0xf0;
	
	while(1)
	{
		PORTD=0xF0; //set all the input to one
		value=PIND; //get the PORTD value in variable “value”
		if(value!=0xf0) //if any key is pressed value changed
		{
			check1();
			check2();
			check3();
			check4();
			
			_delay_ms(100);
			lcdCommand(0x80);
				//itoa(key, temp, 10);
			lcd_print(arr);
			_delay_ms(100);
		}
	}
// while(1)
// {
// 	
// 
// // 	_delay_ms(100);
// // 	lcdCommand(0x80);
// // 	itoa(key, temp, 10);
// // 	lcd_print(key);
// // 	_delay_ms(100);
// 
// }

}
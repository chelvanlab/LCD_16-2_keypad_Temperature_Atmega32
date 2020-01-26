/*
 * Kokis_maker_V1.c
 */ 

#define F_CPU 800000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define pad PORTD
#define r1 PD0
#define r2 PD1
#define r3 PD2
#define r4 PD3
#define c1 PD4
#define c2 PD5
#define c3 PD6
#define degree_sysmbol 0xdf

void check1(void);
void check2(void);  
void check3(void);
void hor_ver_move();
void ingredient_process();
int temp_measure();
void take_out();


bool status = false;
unsigned char value;
int a = 1;
char str[16];


int main(){
	
	DDRA=0xff; //LCD_DATA port as output port
	DDRB=0xff; //signal as out put
	PORTB=0x00;
	DDRD=0x0F;
	pad=0xf0;
	PORTB = 0b01111111; // take out motor working;
	lcd_init(LCD_DISP_ON); //initialization of LCD	
	lcd_gotoxy(0,0);
	lcd_puts("Welcome to kokis");
	lcd_gotoxy(0,1);
	lcd_puts("machine");
	_delay_ms(3000);
	
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts("Put ingredients");
	lcd_gotoxy(0,1);
	lcd_puts("Press * for start");
	_delay_ms(500);
	

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
		}
	}
	return 0;
	
}


void check1(){

	pad =0b11111110;
	_delay_us(10);
	
	if(bit_is_clear(PIND,c1))
	{
		lcd_gotoxy(0,1);
		lcd_puts("1 kokis");
		
		temp_measure();
		
		for(int i=1;i<=1;i++){
			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("Making kokis...");
			lcd_gotoxy(0,1);
			lcd_puts("1 kokis");
			hor_ver_move();
			take_out();
			temp_measure();
		}
		
		lcd_clrscr();
		lcd_puts("Number of kokis") ;
	}		
	
	
	else if(bit_is_clear(PIND,c2))
	{
		lcd_gotoxy(0,1);
		lcd_puts("2 kokis");
		
		temp_measure();
		
		for(int i=1;i<=2;i++){
			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("Making kokis...");
			lcd_gotoxy(0,1);
			lcd_puts("2 kokis");
			hor_ver_move();
			take_out();
			temp_measure();
		}
		
		lcd_clrscr();
		lcd_puts("Number of kokis") ;
		
	}
	
	
	else if(bit_is_clear(PIND,c3))
	{
		lcd_gotoxy(0,1);
		lcd_puts("3 kokis");
		
	}
}

void check2(){
	
	pad=0b11111101;
	_delay_us(10);
	
	
	if(bit_is_clear(PIND,c1))
	{
		lcd_gotoxy(0,1);
		lcd_puts("4 kokis");
		
		temp_measure();
		
		for(int i=1;i<=4;i++){
			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("Making kokis...");
			lcd_gotoxy(0,1);
			lcd_puts("4 kokis");
			hor_ver_move();
			take_out();
			temp_measure();
		}
		
		lcd_clrscr();
		lcd_puts("Number of kokis") ;
		
		
	}
	else if(bit_is_clear(PIND,c2))
	{
		lcd_gotoxy(0,1);
		lcd_puts("5 kokis");
				
	}
	
	else if(bit_is_clear(PIND,c3))
	{
		lcd_gotoxy(0,1);
		lcd_puts("6 kokis");
		
	}
}

void check3(){
	
	pad=0b11111011;
	_delay_us(10);
	
	if(bit_is_clear(PIND,c1))
	{
		lcd_gotoxy(0,1);
		lcd_puts("7 kokis");
		
	}
	
	else if(bit_is_clear(PIND,c2))
	{
		lcd_gotoxy(0,1);
		lcd_puts("8 kokis");

	}

	else if(bit_is_clear(PIND,c3))
	{
		
		lcd_gotoxy(0,1);
		lcd_puts("9 kokis");
		
	}
}

void check4(){
	pad=0b11110111;
	_delay_us(10);
	
	if(bit_is_clear(PIND,c1))
	{
		lcd_clrscr();
		lcd_gotoxy(0,0);
		lcd_puts("Mixing start...");
		_delay_ms(500);
		ingredient_process();
		lcd_clrscr();
		lcd_puts("Number of kokis") ;
		
	}
	
	else if(bit_is_clear(PIND,c2))
	{
		lcd_gotoxy(0,1);
		lcd_puts("0 kokis cannot");
		_delay_ms(1000);
		lcd_clrscr();
		lcd_gotoxy(0,0);
		lcd_puts("Number of kokis");

	}

	else if(bit_is_clear(PIND,c3))
	{
		lcd_clrscr();
		lcd_gotoxy(0,0);
		lcd_puts("Machine stoped");
		PORTB = 0b11111111; // up default
		_delay_ms(1000);
		lcd_clrscr();
		lcd_gotoxy(0,0);
		lcd_puts("Number of kokis");
			
	}
}


void hor_ver_move(){
	PORTB = 0b11111111; //up
	_delay_ms(5000);
	PORTB = 0b11111101; // down
	_delay_ms(8000);
	PORTB = 0b11111111; //up
	_delay_ms(5000);
	
	PORTB = 0b11111110; // -->
	_delay_ms(1500);
	PORTB = 0b11111100; // down
	_delay_ms(5000);
	PORTB = 0b11111110; //up
	_delay_ms(1000);
	
	PORTB = 0b11111111; // <--
	_delay_ms(1500);
	PORTB = 0b11111101; // down
	_delay_ms(15000);
	PORTB = 0b11111111; //up
	_delay_ms(2000);
	/*PORTB = 0b11111101; // down
	_delay_ms(1000);
	*/

}


void ingredient_process(){
	PORTB = 0b01111111; 
	_delay_ms(500);
	PORTB = 0b01111011; // coconut milk open
	_delay_ms(10000);
	PORTB = 0b01111111; // all are stoped
	_delay_ms(500);
	PORTB = 0b01011111; // mixing middle motor
	_delay_ms(1000);
	PORTB = 0b01001111; // floor motor working
	_delay_ms(30000);
	PORTB = 0b01011111; // all are stoped
	_delay_ms(30000);
	PORTB = 0b01111111; //stoped
	_delay_ms(500);
	PORTB = 0b01110111; // last valve open
	_delay_ms(30000);
	PORTB = 0b01111111; // all are stoped
}

void take_out(){
	PORTB = 0b00111111; // take out motor working;
	_delay_ms(2000);
	PORTB = 0b01111111; // al are stoped
}


int temp_measure()
{
	char printbuff[100],cdf[100];
	double d = 0;
	int a = 1;
	PORTB = 0b01111111;
	
	lcd_clrscr();

	while(a) {
		double real = 25;
		d = ds18b20_gettemp();
		
		real = ((d-16865)/3)+real;

		itoa(d, printbuff, 10);
		itoa(real,cdf,10);
		
		lcd_puts("Temp:- " );
		lcd_gotoxy(7,0);
		lcd_puts(cdf);
		lcd_gotoxy(10,0);
		lcd_puts("C");
		_delay_ms(500);
		lcd_clrscr();
		
		if(real>=115.0){
			lcd_clrscr();
			lcd_puts("Temp ok");
			_delay_ms(3000);
			PORTB = 0b11111111;
			a = 0;
		}
	}
}



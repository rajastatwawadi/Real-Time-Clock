#include<reg51.h>
#include"lcd1.h"

#define LCD_PORT P0

sbit RS=P2^4;
sbit RW=P2^5;
sbit EN=P2^6;

void usdelay(unsigned int ms){
	
	while(ms--){
		;
	}	
	
}

void lcd_cmd(unsigned char cmd){
	LCD_PORT=cmd;
	RS=0;
	RW=0;
	EN=1;
	usdelay(50);
	EN=0;
	usdelay(50);
}

void lcd_data(unsigned char dat){
	LCD_PORT=dat;
	RS=1;
	RW=0;
	EN=1;
	usdelay(50);
	EN=0;
	usdelay(50);
}

void lcd_init(){
	usdelay(2000);
	LCD_PORT=0x00;
	RS=0;
	RW=0;
	EN=0;
	lcd_cmd(0x38);
	usdelay(2000);
	lcd_cmd(0x01);
	usdelay(2000);
	lcd_cmd(0x0C);
	usdelay(2000);
	lcd_cmd(0x06);
	usdelay(2000);
}



void display_char_xy(unsigned char row, unsigned char col, unsigned char msg){
	unsigned char location;
	if(row==0){
		location= (0x80) | ((col) & (0x0F));
		lcd_cmd(location);
	}
	else{
		location= (0xC0) | ((col) & (0x0F));
		lcd_cmd(location);
	}
	lcd_data(msg);
}



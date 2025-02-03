#include<reg51.h>
#include"i2c.h"

sbit SDA=P3^7;
sbit SCL=P3^6;

//delay
void delay_i2c(void){
	unsigned char us=5;
	while(us>0){
		us--;
	}
}

void i2c_clk(void){
	//delay_i2c();
	SCL=1;
	//delay_i2c();
	SCL=0;
}


void i2c_start(){
	
	SDA=1;
	;//delay_i2c();
	SCL=1;
	;//delay_i2c();
	SDA=0; // Actual start
	;//delay_i2c();
	
	SCL=0;
}

void i2c_stop(){
	
	SDA=0;
	;//delay_i2c();
	
	SCL=1;
	;//delay_i2c();
	
	SDA=1;
}



void i2c_write(unsigned char dat){
	unsigned char i;
	for(i=0; i<8; i++){
		SDA=dat&0x80;
		i2c_clk();
		dat=dat<<1;
	}
	SDA=1;
	i2c_clk();
}

unsigned char i2c_read(bit ack){
	unsigned char i,dat=0x00;
	SDA=1;
	for(i=0; i<8; i++){
		delay_i2c();
		SCL=1;
		delay_i2c();
		
		dat=dat<<1;
		dat=dat|SDA;
		
		SCL=0;
	}
	SDA=!ack;
	i2c_clk();
	//SDA=1;
	return dat;
	
}

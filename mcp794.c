#include<reg51.h>
#include"i2c.h"
#include"mcp794.h"

#define MCP794_ID 0xDE

#define SEC_ADDRESS 0x00
#define MIN_ADDRESS 0x01
#define HR_ADDRESS 0x02

#define DATE_ADDRESS 0x04
#define MONTH_ADDRESS 0x05
#define YEAR_ADDRESS 0x06

#define CONTROL 0x07

unsigned char BCD_to_dec(unsigned char bcdByte)
{
    unsigned char a,b;
    a=(((bcdByte & 0xF0) >> 4) * 10);
    b=(bcdByte & 0x0F);
    return a+b;
}

unsigned char dec_to_BCD (unsigned char decimalByte)
{
  unsigned char a,b;
  a=((decimalByte / 10) << 4);
  b= (decimalByte % 10);
  return a|b;
}


void MCP794_init(){
	unsigned char temp;
	
	i2c_start();  //power bit to be cleared again at start
 	
	i2c_write(MCP794_ID);
	i2c_write(0x03);
	i2c_write(0x08);
	
	i2c_stop();
	
	
	i2c_start();
	i2c_write(MCP794_ID);
	i2c_write(SEC_ADDRESS);
	
	i2c_start();
	i2c_write(MCP794_ID | 0x01);
	temp=i2c_read(0);
	i2c_stop();
	
	temp=BCD_to_dec(temp);
	temp=temp&0x7F;
	
	delay_i2c();
	
	i2c_start();
	i2c_write(MCP794_ID);
	i2c_write(SEC_ADDRESS);
	i2c_write(dec_to_BCD(temp) | 0x80); 
	i2c_stop();
	
	i2c_start();
	
	i2c_write(MCP794_ID);
	i2c_write(CONTROL);
	i2c_write(0x00);
	
	i2c_stop();
		

}

void MCP794_set_time(unsigned char hour, unsigned char min, unsigned char sec){
	
	i2c_start();
	i2c_write(MCP794_ID);
	i2c_write(SEC_ADDRESS);
	i2c_write(sec | 0x80); 
	i2c_stop();
	
	i2c_start();
	i2c_write(MCP794_ID);
	i2c_write(MIN_ADDRESS);
	i2c_write(min);
	i2c_stop();
	
	i2c_start();
	i2c_write(MCP794_ID);
	i2c_write(HR_ADDRESS);
	i2c_write(hour);
	i2c_stop();
	
	
}

void MCP794_get_time(unsigned char *h_ptr, unsigned char *m_ptr, unsigned char *s_ptr){
	
	i2c_start();
	i2c_write(MCP794_ID);
	i2c_write(SEC_ADDRESS);
	
	i2c_start();
	i2c_write(MCP794_ID | 0x01);
	
	*s_ptr=i2c_read(1) & 0x7F;
	
	*m_ptr=i2c_read(1) & 0x7F;
	
	*h_ptr=i2c_read(0) & 0x3F;

	i2c_stop();
	
}

void MCP794_set_date(unsigned char date, unsigned char month, unsigned char year){
	
	i2c_start();
	i2c_write(MCP794_ID);
	i2c_write(DATE_ADDRESS);
	i2c_write(date); 
	i2c_stop();
	
	i2c_start();
	i2c_write(MCP794_ID);
	i2c_write(MONTH_ADDRESS);
	i2c_write(month);
	i2c_stop();
	
	i2c_start();
	i2c_write(MCP794_ID);
	i2c_write(YEAR_ADDRESS);
	i2c_write(year);
	i2c_stop();
	
	
}

void MCP794_get_date(unsigned char *d_ptr, unsigned char *m_ptr, unsigned char *y_ptr){
	i2c_start();
	i2c_write(MCP794_ID);
	i2c_write(DATE_ADDRESS);
	
	i2c_start();
	i2c_write(MCP794_ID | 0x01);
	
	*d_ptr=i2c_read(1) & 0x3F;
	
	*m_ptr=i2c_read(1) & 0x1F;
	
	*y_ptr=i2c_read(0) & 0xFF;

	i2c_stop();
	
}




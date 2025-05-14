#ifndef __I2C_H__
#define __I2C_H__

void i2c_clk(void);
void i2c_start();
void i2c_stop();
void i2c_write(unsigned char );
unsigned char i2c_read(bit ack);
void delay_i2c(void);

#endif

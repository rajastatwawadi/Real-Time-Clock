#ifndef __LCD1_H__
#define __LCD1_H__

void lcd_init();
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char dat);
void usdelay(unsigned int ms);
void display_char_xy(unsigned char row, unsigned char col, unsigned char msg);

#endif

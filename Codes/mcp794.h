#ifndef __MCP794_H__
#define __MCP794_H__

void MCP794_init();
void MCP794_set_time(unsigned char hour, unsigned char min, unsigned char sec);
void MCP794_set_date(unsigned char date, unsigned char month, unsigned char year);
void MCP794_get_time(unsigned char *h_ptr, unsigned char *m_ptr, unsigned char *s_ptr);
void MCP794_get_date(unsigned char *d_ptr, unsigned char *m_ptr, unsigned char *y_ptr);
unsigned char BCD_to_dec(unsigned char bcdByte);
unsigned char dec_to_BCD(unsigned char decimalByte);

#endif

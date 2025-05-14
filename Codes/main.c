#include<reg51.h>
#include"lcd1.h"
#include"i2c.h"
#include"mcp794.h"

unsigned char TIME[6]={1,8,0,0,0,0};
bit TIME_SET=0;



unsigned char blink=0;
unsigned char time_index=0;
unsigned char blink_ct=0;

sbit BUTTON1=P2^3;
sbit BUTTON2=P2^0;
sbit BUTTON3=P2^1;
sbit BUTTON4=P2^2;

bit DEBOUNCE1_FLAG;
bit DEBOUNCE2_FLAG;
bit DEBOUNCE3_FLAG;
bit DEBOUNCE4_FLAG;

unsigned char ct1=0;
unsigned char ct2=0;
unsigned char ct3=0;
unsigned char ct4=0;

bit BUTTON1_FLAG;
bit BUTTON2_FLAG;
bit BUTTON3_FLAG;
bit BUTTON4_FLAG;

unsigned char hour;
unsigned char min;
unsigned char sec;

void update_time_index(){
	if(blink==0){
		time_index=0;
		return;
	}
	if(blink==1){
		time_index=1;
		return;
	}
	if(blink==2){
		time_index=2;
		return;
	}
	if(blink==4){
		time_index=3;
		return;
	}
	if(blink==5){
		time_index=4;
		return;
	}
	if(blink==7){
		time_index=5;
		return;
	}
	if(blink==8){
		time_index=6;
		return;
	}
	
}


void isvalid(){
	
	if(TIME[0]==3){
		TIME[0]=0;
	}
	else if(TIME[0]==9){
		TIME[0]=2;
	}
	
	
	if(TIME[1]==4 && TIME[0]==2){
		TIME[1]=0;
	}
	else if(TIME[1]==9 && TIME[0]==2){
		TIME[1]=3;
	}
	
	
	if(TIME[2]==6){
		TIME[2]=0;
	}
	else if(TIME[2]==9){
		TIME[2]=5;
	}
	
	
	if(TIME[4]==6){
		TIME[4]=0;
	}
	else if(TIME[4]==9){
		TIME[4]=5;
	}
		
	if(TIME[0]==2 && TIME[1]>3){
		TIME[1]=0;
	}
}


void debounce_check(){
	
	if(!DEBOUNCE1_FLAG && BUTTON1==0){
		DEBOUNCE1_FLAG=1;
	}
	if(!DEBOUNCE2_FLAG && BUTTON2==0){
		DEBOUNCE2_FLAG=1;
	}
	if(!DEBOUNCE3_FLAG && BUTTON3==0){
		DEBOUNCE3_FLAG=1;
	}
	if(!DEBOUNCE4_FLAG && BUTTON4==0){
		DEBOUNCE4_FLAG=1;
	}
	
	if(DEBOUNCE1_FLAG){
		if(ct1==40){
			if(BUTTON1==1){
				ct1=0;
				DEBOUNCE1_FLAG=0;
				BUTTON1_FLAG=1;
			}
		}
		else{
			ct1++;
		}
	}
	
	if(DEBOUNCE2_FLAG){
		if(ct2==40){
			if(BUTTON2==1){
				ct2=0;
				DEBOUNCE2_FLAG=0;
				BUTTON2_FLAG=1;
			}
		}
		else{
			ct2++;
		}
	}
	
	if(DEBOUNCE3_FLAG){
		if(ct3==40){
			if(BUTTON3==1){
				ct3=0;
				DEBOUNCE3_FLAG=0;
				BUTTON3_FLAG=1;
			}
		}
		else{
			ct3++;
		}
	}
	
	if(DEBOUNCE4_FLAG){
		if(ct4==40){
			if(BUTTON4==1){
				ct4=0;
				DEBOUNCE4_FLAG=0;
				BUTTON4_FLAG=1;
			}
		}
		else{
			ct4++;
		}
	}
	
}


void button_press_check(){
	if(BUTTON1_FLAG){
		if(blink==2 || blink==5){
			blink+=2;
			update_time_index();
		}
		else{
			blink++;
			update_time_index();			
		}
		if(blink==9){
			blink=1;
			update_time_index();
		}
		BUTTON1_FLAG=0;
		TIME_SET=1;
	}
		
	if(blink>0){
		if(BUTTON2_FLAG){
			TIME[time_index-1]++;
			TIME[time_index-1]%=10;
			isvalid();
			BUTTON2_FLAG=0;
		}
			
		if(BUTTON3_FLAG){
				
			if(TIME[time_index-1]==0){
				TIME[time_index-1]=9;
				isvalid();
			}
			else{
				TIME[time_index-1]--;
				isvalid();
			}
			
			BUTTON3_FLAG=0;
		}	
			
		if(BUTTON4_FLAG){
			blink=0;
			update_time_index();
			BUTTON4_FLAG=0;
			TIME_SET=0;
		}
			
	}
			
}


unsigned char num_to_char(unsigned char num){
	return (num+48);
}

void display_time(){
	unsigned char i;
	unsigned char j=0;
	
	for(i=1; i<=8; i++){
		if(blink==0){
			
			if(i==3 || i==6){
				display_char_xy(0, i+3, ':');
			}
			else{
				display_char_xy(0, i+3, num_to_char(TIME[j]));
				j++;
			}
			
		}
		else{
			if(i==blink){
				if(blink_ct<15){
					display_char_xy(0, i+3, num_to_char(TIME[j]));
					blink_ct++;
				}
				else{
					display_char_xy(0,i+3, 32);
					blink_ct++;
					if(blink_ct==30){
						blink_ct=0;
					}
				}
				j++;
			}
			
			else{
				if(i==3 || i==6){
					display_char_xy(0, i+3, ':');
				}
				else{
					display_char_xy(0, i+3, num_to_char(TIME[j]));
					j++;
				}
			}
		}
		
	}
	
}


void timer0_isr() interrupt 1{
	
	TH0=0xD8;  //FC
	TL0=0xF0;  //18
	//TR0=1;
	
	debounce_check();
	
}	


void main(void)
{
	//Ports
	P0=0x00;
	P1=0x00;
	P2=0xFF;
	
	TMOD=0x01;
	TH0=0xD8;
	TL0=0xF0;
	IE=0x82;
	
	//Initialize
	lcd_init();
	MCP794_init();
	
	
	TR0=1;
	
	while(1){
		
		//MCP794 part
		if(TIME_SET==0){
			MCP794_get_time(&hour, &min, &sec);
			hour=BCD_to_dec(hour);
			min=BCD_to_dec(min);
			sec=BCD_to_dec(sec);
		
			//Update disp array
			TIME[0]=hour/10;
			TIME[1]=hour%10;
			
			TIME[2]=min/10;
			TIME[3]=min%10;

			TIME[4]=sec/10;
			TIME[5]=sec%10;
		
		}
		
		//In case of setting time
		else{
			MCP794_set_time(dec_to_BCD( (10*TIME[0]+TIME[1]) & 0x3F), dec_to_BCD(10*TIME[2]+TIME[3]), dec_to_BCD( (10*TIME[4]+TIME[5]) & 0x7F));
			
		}
		
	//Display function		
	display_time();
	
	//Update global if button pressed
	button_press_check();

	
	}
		
}

		

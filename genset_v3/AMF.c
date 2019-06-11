#include <avr/wdt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include "mymacro.h"

void delay_10ms(void){
_delay_ms(20);
}
/******************************************************************************/
unsigned char read_genset(void){
	unsigned char a=0xff;
	x3_in();
	x3_hi();
	delay_10ms();
	if(r_x3())a=0;
	delay_10ms();
	if(r_x3())a=0;
	delay_10ms();
	if(r_x3())a=0;
	return a;
}
/******************************************************************************/
unsigned char sensor(void){//return 1 jika sensor di tekan
	unsigned char a=0xff;
	x1_in();
	x2_in();
	x1_hi();
	x2_hi();
	delay_10ms();
	if(r_x1()&&r_x2())a=0;
	delay_10ms();
	if(r_x1()&&r_x2())a=0;
	delay_10ms();
	if(r_x1()&&r_x2())a=0;
	return a;
}
/******************************************************************************/
unsigned char read_pln(void){
	unsigned char a=0xff;
	x4_in();
	x4_hi();
	delay_10ms();
	if(r_x4())a=0;
	delay_10ms();
	if(r_x4())a=0;
	delay_10ms();
	if(r_x4())a=0;
	return a;
}
/******************************************************************************/
void delay(unsigned char wait){
unsigned char tunggu;
for ( tunggu=0;tunggu<wait;tunggu++){
	_delay_ms(500);
	wdt_reset();
	_delay_ms(500);
	wdt_reset();	
	}
}
/*
x1 = sensor 1
x2 = sensor 2
x3 = sensor genset
x4 = sensor pln
y1 = acc on
y2 = preheat
y3 = starter
y4 = genset
y5 = pln
y6 = buzer
1118 byte
*/
/******************************************************************************/
int main(void){
	unsigned char i;
	unsigned char acc_off;
	
	y1_lo();
	y2_lo();
	y3_lo();
	y4_lo();
	y5_lo();
	y6_lo();
	x1_hi();
	x2_hi();
	x3_hi();
	x4_hi();

	x1_in();
	x2_in();
	x3_in();
	x4_in();
	y1_out();
	y2_out();
	y3_out();
	y4_out();
	y5_out();
	y6_out();
	wdt_enable(WDTO_2S);
	_delay_ms(100);
	while(1){
		acc_off=30;
		while(read_pln()){
			while(read_pln()){		//pln hidup//
				y1_out();
				y2_out();
				y3_out();
				y4_out();
				y5_out();
				y6_out();
				delay_10ms();
				y2_lo();
				y3_lo();
				y4_lo();
				y5_hi();//pln on
				y6_lo();
				delay(1);
				if(acc_off>0)acc_off--;
				else y1_lo();//acc off			
			}
			delay(5);
		};
/******************************************************************************/
//	hidupkan acc dan preheat
/******************************************************************************/
		if(!read_pln()){			//pln mati
			y1_hi();//acc on
/******************************************************************************/
//			SETARTER 3 KALI
/******************************************************************************/
			for(i=0;i<3;i++){
				y2_hi();//pre heat on
				y3_lo();
				y4_lo();
				y5_lo();
				y6_lo();
				delay(4);
				y3_hi();//starter on
				delay(3);
				y3_lo();//starter off
				y2_lo();//pre heat off
				delay(10);
				if(read_pln()) break;
				if(read_genset())break;
			}
/******************************************************************************/
//			GENSET HIDUP DI SINI :D
/******************************************************************************/
			if(read_genset()) delay(4);//TUNDA SEBELUM KONTAKTOR GENSET ON
				do{
					delay(1);
					y1_out();
					y2_out();
					y3_out();
					y4_out();
					y5_out();
					y6_out();
					delay_10ms();
					if(read_genset()&&!sensor()){
						y1_hi();//acc on
						y2_lo();
						y3_lo();
						y4_hi();//genset on
						y5_lo();
						y6_lo();
				   }//genset hidup
/******************************************************************************/
//			ALARAM BUZER DI BAWAH SINI YA
/******************************************************************************/
					else{
						y1_lo();
						y2_lo();
						y3_lo();
						y4_lo();
						y5_lo();
						y6_hi();//buzer on
						delay(1);
						y6_lo();//buzer off
						}//genset mati
				}while(!read_pln());
				wdt_reset();
			}
/******************************************************************************/
//			PLN SUDAH HIDUP DI SINI :D
/******************************************************************************/
	y2_lo();
	y3_lo();
	y4_lo();
	y5_lo();
	y6_lo();
	delay(10);
/******************************************************************************/
	}//SUPER LOOOP
}

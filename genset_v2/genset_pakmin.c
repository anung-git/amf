#include <avr/wdt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>

#define port_sensor1		PORTD
#define pin_sensor1			PIND
#define ddr_sensor1			DDRD
#define bit_sensor1			PD0

#define port_sensor2		PORTD
#define pin_sensor2			PIND
#define ddr_sensor2			DDRD
#define bit_sensor2			PD1

#define port_genset_in		PORTD
#define pin_genset_in		PIND
#define ddr_genset_in		DDRD
#define bit_genset_in		PD2

#define port_pln_in			PORTD
#define pin_pln_in			PIND
#define ddr_pln_in			DDRD
#define bit_pln_in			PD3

#define port_buzer			PORTB
#define pin_buzer			PINB
#define ddr_buzer			DDRB
#define bit_buzer			PB4

#define port_acc			PORTB
#define pin_acc				PINB
#define ddr_acc				DDRB
#define bit_acc				PB6

#define port_preheat		PORTB

#define pin_preheat			PINB
#define ddr_preheat			DDRB
#define bit_preheat			PB3

#define port_starter		PORTB
#define pin_starter			PINB
#define ddr_starter			DDRB
#define bit_starter			PB2

#define port_genset_out		PORTB
#define pin_genset_out		PINB
#define ddr_genset_out		DDRB
#define bit_genset_out		PB1

#define port_pln_out		PORTB
#define pin_pln_out			PINB
#define ddr_pln_out			DDRB
#define bit_pln_out			PB0

/******************************************************************************/
unsigned char read_genset(void){
	cbi(ddr_genset_in,bit_genset_in);	//set pin input 
	sbi(port_genset_in,bit_genset_in);	//pull up input
	unsigned char i,a;
	for(i=0;i<10;i++){
		if(bit_is_set(pin_genset_in,bit_genset_in)){
			a=0;
			break;
		}
		a=0xff;
		_delay_ms(1);
	}
	return a;
}
/******************************************************************************/
unsigned char sensor(void){
	cbi(ddr_sensor2,bit_sensor2);	//set pin input 
	sbi(port_sensor2,bit_sensor2);	//pull up input
	cbi(ddr_sensor1,bit_sensor1);	//set pin input 
	sbi(port_sensor1,bit_sensor1);	//pull up input
	unsigned char i,a;
	for(i=0;i<10;i++){
		if(bit_is_set(pin_sensor1,bit_sensor1)&&bit_is_set(pin_sensor2,bit_sensor2)){
			a=0;
			break;
		}
		a=0xff;
		_delay_ms(1);
	}
	return a;
}
/******************************************************************************/
unsigned char read_pln(void){
	cbi(ddr_pln_in,bit_pln_in);		//set pin input 
	sbi(port_pln_in,bit_pln_in);	//pull up input
	unsigned char i,a;
	for(i=0;i<10;i++){
		if(bit_is_set(pin_pln_in,bit_pln_in)){
			a=0;
			break;
		}
		a=0xff;
		_delay_ms(1);
	}
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
/******************************************************************************/
int main(void){
	unsigned char i;
	unsigned char acc_off;
	cbi(ddr_genset_in,bit_genset_in);				//set pin input 
	sbi(port_genset_in,bit_genset_in);				//pull up input
	cbi(ddr_pln_in,bit_pln_in);						//set pin input 
	sbi(port_pln_in,bit_pln_in);					//pull up input
	sbi(ddr_starter,bit_starter);					//starter output
	cbi(port_starter,bit_starter);					//matikan starter
	sbi(ddr_pln_out,bit_pln_out);					//out pln set out
	cbi(port_pln_out,bit_pln_out);					//matikan out pln
	sbi(ddr_genset_out,bit_genset_out);				//output genset set out
	cbi(port_genset_out,bit_genset_out);			//matikan genset
	sbi(ddr_buzer,bit_buzer);						//out buzer set out
	cbi(port_buzer,bit_buzer);						//matikan out buzer
	sbi(ddr_preheat,bit_preheat);					//set preheat output
	cbi(port_preheat,bit_preheat);					//preheat mati
	sbi(ddr_acc,bit_acc);							//acc set out
	cbi(port_acc,bit_acc);							//acc off
	wdt_enable(WDTO_2S);
	_delay_ms(100);
	while(1){
		acc_off=60;
		while(read_pln()){
			while(read_pln()){		//pln hidup//
				sbi(ddr_starter,bit_starter);					//starter output
				cbi(port_starter,bit_starter);					//matikan starter		
				sbi(ddr_pln_out,bit_pln_out);					//out pln set out
				sbi(port_pln_out,bit_pln_out);					//hidupkan out pln
				sbi(ddr_genset_out,bit_genset_out);				//output genset set out
				cbi(port_genset_out,bit_genset_out);			//matikan genset	
				sbi(ddr_buzer,bit_buzer);						//out buzer set out
				cbi(port_buzer,bit_buzer);						//matikan out buzer
				sbi(ddr_preheat,bit_preheat);					//set preheat output
				cbi(port_preheat,bit_preheat);					//preheat mati
				sbi(ddr_acc,bit_acc);							//acc set out
				delay(1);
				if(acc_off>0)acc_off--;
				else cbi(port_acc,bit_acc);							//acc off			
			}
			delay(5);
		};
/******************************************************************************/
//	hidupkan acc dan preheat
/******************************************************************************/
		if(!read_pln()){			//pln mati
			sbi(ddr_starter,bit_starter);					//starter output
			cbi(port_starter,bit_starter);					//matikan starter
			sbi(ddr_pln_out,bit_pln_out);					//out pln set out
			cbi(port_pln_out,bit_pln_out);					//matikan out pln
			sbi(ddr_genset_out,bit_genset_out);				//output genset set out
			cbi(port_genset_out,bit_genset_out);			//matikan genset
			sbi(ddr_buzer,bit_buzer);						//out buzer set out
			cbi(port_buzer,bit_buzer);						//matikan out buzer
			sbi(ddr_preheat,bit_preheat);					//set preheat output
			sbi(port_preheat,bit_preheat);					//preheat hidup
			sbi(ddr_acc,bit_acc);							//acc set out
			sbi(port_acc,bit_acc);							//acc on
			delay(6);
/******************************************************************************/
//			SETARTER 3 KALI
/******************************************************************************/
			for(i=0;i<3;i++){
				sbi(ddr_starter,bit_starter);					//starter output
				sbi(port_starter,bit_starter);					//hidupkan starter
				delay(5);
				sbi(ddr_starter,bit_starter);					//starter output
				cbi(port_starter,bit_starter);					//matikan starter
				sbi(ddr_preheat,bit_preheat);					//set preheat output
				cbi(port_preheat,bit_preheat);					//preheat mati
				delay(10);
				if(read_pln()) break;
				if(read_genset())break;
			}

/******************************************************************************/
//			GENSET HIDUP DI SINI :D
/******************************************************************************/
			if(read_genset()) delay(4);//TUNDA SEBELUM KONTAKTOR GENSET ON
				do{
					if(read_genset()&&!sensor()){
						delay(1);
						sbi(ddr_starter,bit_starter);					//starter output
						cbi(port_starter,bit_starter);					//matikan starter
						sbi(ddr_pln_out,bit_pln_out);					//out pln set out
						cbi(port_pln_out,bit_pln_out);					//matikan out pln
						sbi(ddr_genset_out,bit_genset_out);				//output genset set out
						sbi(port_genset_out,bit_genset_out);			//hidupkan genset	
						sbi(ddr_buzer,bit_buzer);						//out buzer set out
						cbi(port_buzer,bit_buzer);						//matikan out buzer
						sbi(ddr_preheat,bit_preheat);					//set preheat output
						cbi(port_preheat,bit_preheat);					//preheat mati
						sbi(ddr_acc,bit_acc);							//acc set out
						sbi(port_acc,bit_acc);							//acc on
					}//genset hidup
/******************************************************************************/
//			ALARAM BUZER DI BAWAH SINI YA
/******************************************************************************/
					else{
						delay(1);
						sbi(ddr_starter,bit_starter);					//starter output
						cbi(port_starter,bit_starter);					//matikan starter
						sbi(ddr_pln_out,bit_pln_out);					//out pln set out
						cbi(port_pln_out,bit_pln_out);					//matikan out pln
						sbi(ddr_genset_out,bit_genset_out);				//output genset set out
						cbi(port_genset_out,bit_genset_out);			//matikan genset	
						sbi(ddr_buzer,bit_buzer);						//out buzer set out
						sbi(port_buzer,bit_buzer);						//hidupkan buzer
						sbi(ddr_preheat,bit_preheat);					//set preheat output
						cbi(port_preheat,bit_preheat);					//preheat mati
						sbi(ddr_acc,bit_acc);							//acc set out
						cbi(port_acc,bit_acc);							//acc off
						delay(1);
						sbi(ddr_starter,bit_starter);					//starter output
						cbi(port_starter,bit_starter);					//matikan starter
						sbi(ddr_pln_out,bit_pln_out);					//out pln set out
						cbi(port_pln_out,bit_pln_out);					//matikan out pln
						sbi(ddr_genset_out,bit_genset_out);				//output genset set out
						cbi(port_genset_out,bit_genset_out);			//matikan genset	
						sbi(ddr_buzer,bit_buzer);						//out buzer set out
						cbi(port_buzer,bit_buzer);						//matikan out buzer	
						sbi(ddr_preheat,bit_preheat);					//set preheat output
						cbi(port_preheat,bit_preheat);					//preheat mati		
						sbi(ddr_acc,bit_acc);							//acc set out
						cbi(port_acc,bit_acc);							//acc off
						}//genset mati
				}while(!read_pln());
				wdt_reset();
			}
/******************************************************************************/
//			PLN SUDAH HIDUP DI SINI :D
/******************************************************************************/
	sbi(ddr_starter,bit_starter);					//starter output
	cbi(port_starter,bit_starter);					//matikan starter	
	sbi(ddr_pln_out,bit_pln_out);					//out pln set out
	cbi(port_pln_out,bit_pln_out);					//matikan out pln
	sbi(ddr_genset_out,bit_genset_out);				//output genset set out
	cbi(port_genset_out,bit_genset_out);			//matikan genset	
	sbi(ddr_buzer,bit_buzer);						//out buzer set out
	cbi(port_buzer,bit_buzer);						//matikan out buzer
	sbi(ddr_preheat,bit_preheat);					//set preheat output
	cbi(port_preheat,bit_preheat);					//preheat mati
	delay(10);
/******************************************************************************/
	}//SUPER LOOOP
}

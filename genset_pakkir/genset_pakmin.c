#include <avr/wdt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
/*
#define PORTD	PORTD
#define PIND	PIND
#define DDRD	DDRD
#define PD3		PD3

#define PORTD		PORTD
#define PIND		PIND
#define DDRD		DDRD
#define PD4			PD4

#define PORTB	PORTB
#define PINB	PINB
#define DDRB    DDRB
#define PD4  	PD4

#define PORTB		PORTB
#define PINB		PINB
#define DDRB		DDRB
#define PB2			PB2

#define PORTB		PORTB
#define PINB		PINB
#define DDRB		DDRB
#define PB0			PB0

#define PORTB		PORTB
#define PINB		PINB
#define DDRB		DDRB
#define PB6			PB6

#define PORTB	PORTB
#define PINB	PINB
#define DDRB	DDRB
#define PB7		PB7
*/
/******************************************************************************/
unsigned char read_genset(void){
	cbi(DDRD,3);	//set pin input 
	sbi(PORTD,PD3);	//pull up input
	unsigned char i,a;
	for(i=0;i<10;i++){
		if(bit_is_set(PIND,PD3)){
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
	cbi(DDRD,PD4);		//set pin input 
	sbi(PORTD,PD4);	//pull up input
	unsigned char i,a;
	for(i=0;i<10;i++){
		if(bit_is_set(PIND,PD4)){
			a=0;
			break;
		}
		a=0xff;
		_delay_ms(1);
	}
	return a;
}
/******************************************************************************/
int main(void){
	unsigned char i;
	//(port) |= (1 << (bit))
	cbi(DDRD,PD3);			//set pin input 
	sbi(PORTD,PD3);			//pull up input
	cbi(DDRD,PD4);			//set pin input 
	sbi(PORTD,PD4);			//pull up input
	sbi(DDRB,PB6);			//starter output
	cbi(PORTB,PB6);			//matikan starter
	sbi(DDRB,PB4);			//out genset set out
	cbi(PORTB,PB4);			//matikan out genset
	sbi(DDRB,PB2);			//out pln set out
	cbi(PORTB,PB2);			//matikan out pln
	sbi(DDRB,PB7);			//output genset set out
	cbi(PORTB,PB7);			//matikan genset	
	sbi(DDRB,PB0);			//out buzer set out
	cbi(PORTB,PB0);			//matikan out buzer
	wdt_enable(WDTO_2S);
	_delay_ms(100);
	while(1){
		while(read_pln()){	//pln hidup
		//
		cbi(DDRD,PD3);			//set pin input 
		sbi(PORTD,PD3);			//pull up input
		cbi(DDRD,PD4);			//set pin input 
		sbi(PORTD,PD4);			//pull up input
		sbi(DDRB,PB6);			//starter output
		cbi(PORTB,PB6);			//matikan starter
		sbi(DDRB,PB4);			//out genset set out
		cbi(PORTB,PB4);			//matikan out genset
		sbi(DDRB,PB2);			//out pln set out
		sbi(PORTB,PB2);			//ON out pln
		sbi(DDRB,PB7);			//output genset set out
		cbi(PORTB,PB7);			//matikan genset	
		sbi(DDRB,PB0);			//out buzer set out
		cbi(PORTB,PB0);			//matikan out buzer
		wdt_reset();
		}
/******************************************************************************/
		if(!read_pln()){	//pln mati
			cbi(DDRD,PD3);			//set pin input 
			sbi(PORTD,PD3);			//pull up input
			cbi(DDRD,PD4);			//set pin input 
			sbi(PORTD,PD4);			//pull up input
			sbi(DDRB,PB6);			//starter output
			cbi(PORTB,PB6);			//matikan starter
			sbi(DDRB,PB4);			//out genset set out
			cbi(PORTB,PB4);			//matikan out genset
			sbi(DDRB,PB2);			//out pln set out
			cbi(PORTB,PB2);			//matikan out pln
			sbi(DDRB,PB7);			//output genset set out
			sbi(PORTB,PB7);			//on genset	
			sbi(DDRB,PB0);			//out buzer set out
			cbi(PORTB,PB0);			//matikan out buzer
			_delay_ms(100);
			for(i=0;i<3;i++){
				sbi(PORTB,PB6);	//hidupkan starter
				_delay_ms(1000);
				wdt_reset();
				_delay_ms(1000);
				wdt_reset();
				_delay_ms(1000);
				wdt_reset();
				_delay_ms(1000);
				wdt_reset();
				_delay_ms(1000);
				wdt_reset();
				cbi(PORTB,PB6);	//matikan starter
				_delay_ms(1000);
				wdt_reset();
				_delay_ms(1000);
				wdt_reset();
				_delay_ms(1000);
				wdt_reset();
				_delay_ms(1000);
				wdt_reset();
				_delay_ms(1000);
				wdt_reset();
				_delay_ms(1000);
				wdt_reset();
				_delay_ms(1000);
				wdt_reset();
				_delay_ms(1000);
				wdt_reset();
				_delay_ms(1000);
				wdt_reset();
				_delay_ms(1000);
				wdt_reset();
				if(read_pln()) break;
				if(read_genset()) break;
				}
				do{
					if(read_genset()){
						cbi(DDRD,PD3);			//set pin input 
						sbi(PORTD,PD3);			//pull up input
						cbi(DDRD,PD4);			//set pin input 
						sbi(PORTD,PD4);			//pull up input
						sbi(DDRB,PB6);			//starter output
						cbi(PORTB,PB6);			//matikan starter
						sbi(DDRB,PB4);			//out genset set out
						sbi(PORTB,PB4);			//on out genset
						sbi(DDRB,PB2);			//out pln set out
						cbi(PORTB,PB2);			//matikan out pln
						sbi(DDRB,PB7);			//output genset set out
						cbi(PORTB,PB7);			//matikan genset	
						sbi(DDRB,PB0);			//out buzer set out
						cbi(PORTB,PB0);			//matikan out buzer
						wdt_reset();
					}//genset hidup
					else{
						_delay_ms(1000);
						wdt_reset();
						cbi(DDRD,PD3);			//set pin input 
						sbi(PORTD,PD3);			//pull up input
						cbi(DDRD,PD4);			//set pin input 
						sbi(PORTD,PD4);			//pull up input
						sbi(DDRB,PB6);			//starter output
						cbi(PORTB,PB6);			//matikan starter
						sbi(DDRB,PB4);			//out genset set out
						cbi(PORTB,PB4);			//matikan out genset
						sbi(DDRB,PB2);			//out pln set out
						cbi(PORTB,PB2);			//matikan out pln
						sbi(DDRB,PB7);			//output genset set out
						cbi(PORTB,PB7);			//matikan genset	
						sbi(DDRB,PB0);			//out buzer set out
						sbi(PORTB,PB0);			//matikan out buzer
						_delay_ms(1000);
						wdt_reset();
						cbi(DDRD,PD3);			//set pin input 
						sbi(PORTD,PD3);			//pull up input
						cbi(DDRD,PD4);			//set pin input 
						sbi(PORTD,PD4);			//pull up input
						sbi(DDRB,PB6);			//starter output
						cbi(PORTB,PB6);			//matikan starter
						sbi(DDRB,PB4);			//out genset set out
						cbi(PORTB,PB4);			//matikan out genset
						sbi(DDRB,PB2);			//out pln set out
						cbi(PORTB,PB2);			//matikan out pln
						sbi(DDRB,PB7);			//output genset set out
						cbi(PORTB,PB7);			//matikan genset	
						sbi(DDRB,PB0);			//out buzer set out
						cbi(PORTB,PB0);			//matikan out buzer		
								
						}//genset mati
				}while(!read_pln());
			wdt_reset();
		}
	cbi(DDRD,PD3);			//set pin input 
	sbi(PORTD,PD3);			//pull up input
	cbi(DDRD,PD4);			//set pin input 
	sbi(PORTD,PD4);			//pull up input
	sbi(DDRB,PB6);			//starter output
	cbi(PORTB,PB6);			//matikan starter
	sbi(DDRB,PB4);			//out genset set out
	cbi(PORTB,PB4);			//matikan out genset
	sbi(DDRB,PB2);			//out pln set out
	cbi(PORTB,PB2);			//matikan out pln
	sbi(DDRB,PB7);			//output genset set out
	cbi(PORTB,PB7);			//matikan genset	
	sbi(DDRB,PB0);			//out buzer set out
	cbi(PORTB,PB0);			//matikan out buzer
		_delay_ms(1000);
		wdt_reset();
		_delay_ms(1000);
		wdt_reset();
		_delay_ms(1000);
		wdt_reset();
		_delay_ms(1000);
		wdt_reset();
		_delay_ms(1000);
		wdt_reset();
		_delay_ms(1000);
		wdt_reset();
		_delay_ms(1000);
		wdt_reset();
		_delay_ms(1000);
		wdt_reset();
		_delay_ms(1000);
		wdt_reset();
		_delay_ms(1000);
		wdt_reset();
/******************************************************************************/
	}//SUPER LOOOP
}

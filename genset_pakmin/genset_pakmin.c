#include <avr/wdt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>

#define port_genset PORTD
#define pin_genset PIND
#define ddr_genset DDRD
#define bit_genset 5

#define port_pln PORTD
#define pin_pln PIND
#define ddr_pln DDRD
#define bit_pln 4


//#define port_relay1 PORTB
//#define pin_relay1 PINB
//#define bit_relay1 4

//#define port_relay2 PORTB
//#define pin_relay2 PINB
//#define bit_relay2 4

#define port_buzer PORTB
#define pin_buzer PINB
#define bit_buzer 4

#define port_start PORTB
#define pin_start PINB
#define bit_start 6

#define port_on PORTB
#define pin_on PINB
#define bit_on 7
/******************************************************************************/
unsigned char read_genset(void){
	unsigned char i,a;
	for(i=0;i<10;i++){
		if(bit_is_set(pin_genset,bit_genset)){
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
	unsigned char i,a;
	for(i=0;i<10;i++){
		if(bit_is_clear(pin_pln,bit_pln)){
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
	DDRB=0xff;
	DDRD=0;
	wdt_enable(WDTO_2S);
	_delay_ms(100);
	while(1){
		while(read_pln()){	//pln hidup
			DDRB=0xff;
			DDRD=0;
			PORTD=0xef;
			PORTB=0x03;		
			wdt_reset();
		}
/******************************************************************************/
		if(!read_pln()){	//pln mati
			PORTB=0;		//matikan output
			DDRB=0xff;
			DDRD=0;
			PORTD=0xef;
			sbi(port_on,bit_on);	//hidupkan genset
			_delay_ms(100);
			for(i=0;i<3;i++){
				sbi(port_start,bit_start);	//hidupkan starter
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
				cbi(port_start,bit_start);	//matikan starter
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
						wdt_reset();
						PORTB=0x8f;
					}//genset hidup
					else{
						_delay_ms(1000);
						wdt_reset();
						sbi(port_buzer,bit_buzer);
						_delay_ms(1000);
						wdt_reset();
						PORTB=0;
					}//genset mati
				}while(!read_pln());
			wdt_reset();
		}
		PORTB=0;		//matikan output
		_delay_ms(1000);
/******************************************************************************/
		wdt_reset();
	}//SUPER LOOOP
}

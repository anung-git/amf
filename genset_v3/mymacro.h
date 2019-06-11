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
#define ddr_buzer			DDRB
#define bit_buzer			PB4

#define port_acc			PORTB
#define ddr_acc				DDRB
#define bit_acc				PB6

#define port_preheat		PORTB
#define ddr_preheat			DDRB
#define bit_preheat			PB3

#define port_starter		PORTB
#define ddr_starter			DDRB
#define bit_starter			PB2

#define port_genset_out		PORTB
#define ddr_genset_out		DDRB
#define bit_genset_out		PB1

#define port_pln_out		PORTB
#define ddr_pln_out			DDRB
#define bit_pln_out			PB0


#define x1_lo()				port_sensor1&=~_BV(bit_sensor1)
#define x1_hi()				port_sensor1|=_BV(bit_sensor1)
#define x1_in()				ddr_sensor1&=~_BV(bit_sensor1)
#define r_x1()				bit_is_set(pin_sensor1,bit_sensor1)
#define x2_lo()				port_sensor2&=~_BV(bit_sensor2)
#define x2_hi()				port_sensor2|=_BV(bit_sensor2)
#define x2_in()				ddr_sensor2&=~_BV(bit_sensor2)
#define r_x2()				bit_is_set(pin_sensor2,bit_sensor2)
#define x3_lo()				port_genset_in&=~_BV(bit_genset_in)
#define x3_hi()				port_genset_in|=_BV(bit_genset_in)
#define x3_in()				ddr_genset_in&=~_BV(bit_genset_in)
#define r_x3()				bit_is_set(pin_genset_in,bit_genset_in)
#define x4_lo()				port_pln_in	&=~_BV(bit_pln_in)
#define x4_hi()				port_pln_in	|=_BV(bit_pln_in)
#define x4_in()				ddr_pln_in&=~_BV(bit_pln_in)
#define r_x4()				bit_is_set(pin_pln_in,bit_pln_in)

#define y1_lo()				port_acc&=~_BV(bit_acc)
#define y1_hi()				port_acc|=_BV(bit_acc)
#define y1_out()			ddr_acc|=_BV(bit_acc)
#define y2_lo()				port_preheat&=~_BV(bit_preheat)
#define y2_hi()				port_preheat|=_BV(bit_preheat)
#define y2_out()			ddr_preheat|=_BV(bit_preheat)
#define y3_lo()				port_starter&=~_BV(bit_starter)
#define y3_hi()				port_starter|=_BV(bit_starter)
#define y3_out()			ddr_starter|=_BV(bit_starter)
#define y4_lo()				port_genset_out&=~_BV(bit_genset_out)
#define y4_hi()				port_genset_out|=_BV(bit_genset_out)
#define y4_out()			ddr_genset_out|=_BV(bit_genset_out)
#define y5_lo()				port_pln_out&=~_BV(bit_pln_out)
#define y5_hi()				port_pln_out|=_BV(bit_pln_out)
#define y5_out()			ddr_pln_out	|=_BV(bit_pln_out)
#define y6_lo()				port_buzer&=~_BV(bit_buzer)
#define y6_hi()				port_buzer|=_BV(bit_buzer)
#define y6_out()			ddr_buzer|=_BV(bit_buzer)

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
*/


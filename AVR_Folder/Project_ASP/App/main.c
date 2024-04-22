/*
 * GccApplicationTest.c
 *
 * Created: 4/22/2024 5:19:16 AM
 * Author : husse
 */ 

//CPU Configuration
#undef F_CPU //Disable internal clock
#define F_CPU 16000000 //Enable external clock
#include <avr/io.h> //Define internal register
#include <avr/interrupt.h> //define &enable internal & external interrupts
#include <util/delay.h> //Enable delay function
//Std Types
typedef signed char SINT8;
typedef signed short int SINT16;
typedef signed long int SINT32;

typedef unsigned char UINT8;
typedef unsigned short int UINT16;
typedef unsigned long int UINT32;

typedef float fint32_t;
typedef double fint64_t;
//Bit Math
#define SET_BIT(REG,BIT) REG|=(1<<BIT)
#define CLR_BIT(REG,BIT) REG&=~(1<<BIT)
#define GET_BIT(REG,BIT) ((REG>>BIT)&0x01)
#define TGL_BIT(REG,BIT) REG^=(1<<BIT)
/*
//Define DIO registers address
#define PORTA ((volatile uint8_t)(0x3B)) // Output register for PORTA
#define DDRA  ((volatile uint8_t)(0x3A)) // Data direction register for PORTA
#define PINA  ((volatile uint8_t)(0x39)) // Input register for PORTA

#define PORTB ((volatile uint8_t)(0x38)) // Output register for PORTB
#define DDRB  ((volatile uint8_t)(0x37)) // Data direction register for PORTB
#define PINB  ((volatile uint8_t)(0x36)) // Input register for PORTB

#define PORTC ((volatile uint8_t)(0x35)) // Output register for PORTC
#define DDRC  ((volatile uint8_t)(0x34)) // Data direction register for PORTC
#define PINC  ((volatile uint8_t)(0x33)) // Input register for PORTC

#define PORTD ((volatile uint8_t)(0x32)) // Output register for PORTD
#define DDRD  ((volatile uint8_t)(0x31)) // Data direction register for PORTD
#define PIND  ((volatile uint8_t)(0x30)) // Input register for PORTD
*/

#define LED0      2
#define LED0_DDR  DDRC
#define LED0_PORT PORTC

#define LED1      7
#define LED1_DDR  DDRC
#define LED1_PORT PORTC

#define LED2      3
#define LED2_DDR  DDRD
#define LED2_PORT PORTD

#define Relay 2
#define Relay_DDR  DDRA
#define Relay_PORT PORTA

#define Buzzer 3
#define Buzzer_DDR  DDRA
#define Buzzer_PORT PORTA
//Function Prototypes
void LED0_Initialize(void);
void LED0_ON(void);
void LED0_OFF(void);
void LED0_TGL(void);
void LED1_Initialize(void);
void LED1_ON(void);
void LED1_OFF(void);
void LED1_TGL(void);
void LED2_Initialize(void);
void LED2_ON(void);
void LED2_OFF(void);
void LED2_TGL(void);
void Relay_Initialize(void);
void Relay_ON(void);
void Relay_OFF(void);
void Relay_TGL(void);
void Buzzer_Initialize(void);
void Buzzer_ON(void);
void Buzzer_OFF(void);
void Buzzer_TGL(void);

int main(void)
{
	//Initialize direction for LED0 pin as output(Once)
	LED0_Initialize();
	LED1_Initialize();
	LED2_Initialize();
	Relay_Initialize();
	Buzzer_Initialize();
	
	/* Replace with your application code */
	while (1)
	{
		//ON LED0
		LED0_ON();
		LED2_ON();
		Relay_ON();
		Buzzer_ON();
		
		_delay_ms(1000);
		
		//OFF LED0
		LED0_OFF();
		LED2_OFF();
		Relay_OFF();
		Buzzer_OFF();
		
		_delay_ms(1000);
	}
}

void LED0_Initialize(void)
{
	SET_BIT(LED0_DDR, LED0);
}
void LED0_ON(void)
{
	SET_BIT(LED0_PORT, LED0);
}
void LED0_OFF(void)
{
	CLR_BIT(LED0_PORT, LED0);
}
void LED0_TGL(void)
{
	TGL_BIT(LED0_PORT, LED0);
}

void LED1_Initialize(void)
{
	SET_BIT(LED1_DDR, LED1);
}
void LED1_ON(void)
{
	SET_BIT(LED1_PORT, LED1);
}
void LED1_OFF(void)
{
	CLR_BIT(LED1_PORT, LED1);
}
void LED1_TGL(void)
{
	TGL_BIT(LED1_PORT, LED1);
}

void LED2_Initialize(void)
{
	SET_BIT(LED2_DDR, LED2);
}
void LED2_ON(void)
{
	SET_BIT(LED2_PORT, LED2);
}
void LED2_OFF(void)
{
	CLR_BIT(LED2_PORT, LED2);
}
void LED2_TGL(void)
{
	TGL_BIT(LED2_PORT, LED2);
}

void Relay_Initialize(void)
{
	SET_BIT(Relay_DDR, Relay);
}
void Relay_ON(void)
{
	SET_BIT(Relay_PORT, Relay);
}
void Relay_OFF(void)
{
	CLR_BIT(Relay_PORT, Relay);
}
void Relay_TGL(void)
{
	TGL_BIT(Relay_PORT, Relay);
}


void Buzzer_Initialize(void)
{
	SET_BIT(Buzzer_DDR, Buzzer);
}
void Buzzer_ON(void)
{
	SET_BIT(Buzzer_PORT, Buzzer);
}
void Buzzer_OFF(void)
{
	CLR_BIT(Buzzer_PORT, Buzzer);
}
void Buzzer_TGL(void)
{
	TGL_BIT(Buzzer_PORT, Buzzer);
}
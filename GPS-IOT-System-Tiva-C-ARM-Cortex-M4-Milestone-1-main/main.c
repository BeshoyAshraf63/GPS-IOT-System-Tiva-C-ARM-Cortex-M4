#include "stdint.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "tm4c123gh6pm.h"

#define PI 3.14159265359
#define R 6371000
#define DISTINATION_OFFSET 10


uint8_t  numbersArr[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
double distance = 0;
uint8_t currentNumber=0;
uint8_t reachedDistination=0;





void SystemInit(void){
	NVIC_CPAC_R |= 0x00F00000;		//enable FPU - Floating-point numbers
}

void delay(uint32_t times){
	int i ;
		for( i = 0; i < times/5 ; i++)
		{while((NVIC_ST_CTRL_R & 0x10000) == 0){}
		}
	}
void systick_init(){
		NVIC_ST_CTRL_R = 0;									//disable timer
		NVIC_ST_RELOAD_R = (16000*5 - 1);		//time, every (16000-1) = 1 millisec
		NVIC_ST_CURRENT_R = 0;							//clear current r, clear count flag
		NVIC_ST_CTRL_R |= 0x07;							//enable timer and set clck src and start inturrept
}
void portF_led_init()
{
  		SYSCTL_RCGCGPIO_R |= 0x20;   /* enable clock to GPIOF */
      while((SYSCTL_RCGCGPIO_R & 0x20)==0);

      GPIO_PORTF_LOCK_R = 0x4C4F434B; // unlock
  		GPIO_PORTF_CR_R = 0x0F;
  		GPIO_PORTF_AFSEL_R &=~(0x0E); // disable alternative functions
  		GPIO_PORTF_PCTL_R = 0;
  		GPIO_PORTF_DIR_R = 0x0E;        // set pins 1,2,3 as output

  		GPIO_PORTF_AMSEL_R &= ~(0x0E);
  		GPIO_PORTF_DEN_R = 0x0E;         /* set PORTF pins 1 to 4 as digital pins */



}


void portE_enables_init (void){
	SYSCTL_RCGCGPIO_R |=0x10;
		while (( SYSCTL_PRGPIO_R &0x10) == 0);
		GPIO_PORTE_LOCK_R=0x4c4f434b ;
		GPIO_PORTE_CR_R |=0X1E ;
		GPIO_PORTE_AFSEL_R &=~ 0X1E;
		GPIO_PORTE_PCTL_R = 0;
		GPIO_PORTE_AMSEL_R &=~0X1E;
		GPIO_PORTE_DEN_R |=0X1E;
		GPIO_PORTE_DIR_R |=0X1E;
		GPIO_PORTE_PUR_R |=0X00;

	}
void portB_segments_init(void){

			SYSCTL_RCGCGPIO_R |= 0x02;     //Enables port B
			while((SYSCTL_PRGPIO_R & 0x02) == 0){}  //waits until port is into clock
			GPIO_PORTB_LOCK_R = 0x4C4F434B;
			GPIO_PORTB_CR_R|= 0x7F; // unlock first seven pins
			GPIO_PORTB_AMSEL_R &= ~0x7F;
			GPIO_PORTB_AFSEL_R&=~0x7F;
			GPIO_PORTB_DEN_R|=0x7F;
			GPIO_PORTB_PCTL_R = 0x00000000; // used as GPIO so PCTL and AMSEL are reset
			GPIO_PORTB_DIR_R|=0x7F;
			GPIO_PORTB_PUR_R &=~0x7F;






}
double getDistance(double p1[],double p2[]){
   double lat1=p1[0];
   double lon1=p1[1];
   double lat2=p2[0];
   double lon2=p2[1];
	 double x1 = lat1*(PI/180);
   double x2 = lat2*(PI/180);
   double dx = (lat2-lat1)*(PI/180);
   double dy = (lon2-lon1)*(PI/180);

   double a=sin((dx/2))*sin((dx/2))+cos((x1))*cos((x2))
         *sin((dy/2))*sin((dy/2));
   double c=2*atan2(sqrt(a),sqrt((1-a)));
   double d=(R*c);

     return d;
}
void initFunc(void){

 systick_init();
 portE_enables_init();
 portB_segments_init();
 portF_led_init();


}

__irq void SysTick_Handler(){
	uint32_t number = 0;
	uint32_t intDistance = (uint32_t)distance;
	GPIO_PORTE_DATA_R &= ~(0x17);
	if(intDistance < 10000){
		if(currentNumber == 0){
			number = intDistance % 10;
		}else if(currentNumber == 1){
			number = intDistance % 100;
			number /= 10;
		}else if(currentNumber == 2){
			number = intDistance % 1000;
			number /= 100;
		}else{
			number = intDistance / 1000;
		}
		GPIO_PORTB_DATA_R = numbersArr[number];
		GPIO_PORTE_DATA_R = (1 << (currentNumber + 1));
	}else{
		GPIO_PORTB_DATA_R = numbersArr[1];
		GPIO_PORTE_DATA_R = (1 << 4);
	}
	if(currentNumber == 3) currentNumber = 0;
	else currentNumber++;
}
int main(void){
	initFunc();
	__enable_irq();
	delay(1000);
	while(1){
		double point1[2];
		double point2[2];
		double point3[2];

		distance = 1234;
		delay(5000);

		point1[0] = 30.06314876356195;	//lat 1
		point1[1] = 31.278634458791736;	//long 1
		point2[0] = 30.063654887314705;	//lat 2
		point2[1] = 31.280120463348382;	//long 2
		point3[0] = 30.063749460433865;	//lat 3
		point3[1] = 31.27837988633654;	//long 3

		distance  = getDistance(point1, point3);
		if(distance > 100){
			GPIO_PORTF_DATA_R |= 0x08;
		}
		delay(5000);
		distance  = getDistance(point1, point2);
		if(distance > 100){
			GPIO_PORTF_DATA_R |= 0x08;
		}
		delay(5000);
		GPIO_PORTF_DATA_R &= ~0x08;
	}
}

/*

Author: RK
Date: 1/03/2021
Program : Timer 2 all channels PWM


*/





#include <stm32f10x.h>

//USER DEFINED FUNCTION DECLARATIONS
void delay(void);


int main(void)
{
	
/*-------------------CLOCKS ENABLING-----------------------*/	
	
	
RCC->APB2ENR |=RCC_APB2ENR_IOPAEN;  //ENABLE CLOCK FOR GPIOA
RCC->APB2ENR |=RCC_APB2ENR_AFIOEN; //ENABLE CLOCK FOR ALTERNATE FUNCTION
RCC->APB1ENR |=RCC_APB1ENR_TIM2EN; //ENABLE CLOCK FOR TIMER3
RCC->APB1ENR |=RCC_APB1ENR_TIM3EN; //ENABLE CLOCK FOR TIMER3	

	
/*--------------------------END OF CLOCK ENABLING-----------*/	
	


	
/*--------------------GPIO CONFIGURATION---------------------------------*/	
  GPIOA->CRL &=~GPIO_CRL_CNF0_0;	
	GPIOA->CRL |=GPIO_CRL_CNF0_1;		
	GPIOA->CRL |= GPIO_CRL_MODE0_0;
	GPIOA->CRL |= GPIO_CRL_MODE0_1;


  GPIOA->CRL &=~GPIO_CRL_CNF1_0;	
	GPIOA->CRL |=GPIO_CRL_CNF1_1;		
	GPIOA->CRL |= GPIO_CRL_MODE1_0;
	GPIOA->CRL |= GPIO_CRL_MODE1_1;

  GPIOA->CRL &=~GPIO_CRL_CNF2_0;	
	GPIOA->CRL |=GPIO_CRL_CNF2_1;		
	GPIOA->CRL |= GPIO_CRL_MODE2_0;
	GPIOA->CRL |= GPIO_CRL_MODE2_1;
	
	
	GPIOA->CRL &=~GPIO_CRL_CNF3_0;	
	GPIOA->CRL |=GPIO_CRL_CNF3_1;		
	GPIOA->CRL |= GPIO_CRL_MODE3_0;
	GPIOA->CRL |= GPIO_CRL_MODE3_1;
	
	
GPIOA->CRL &=~GPIO_CRL_CNF7_0;    //ALTERNATE FUNCTION CONFIGURATION FOR PIN_7 PORTA
GPIOA->CRL |=GPIO_CRL_CNF7_1;	
GPIOA->CRL |=GPIO_CRL_MODE7_0;
GPIOA->CRL |=GPIO_CRL_MODE7_1;		



  AFIO->EVCR  &=~AFIO_EVCR_PIN_0; //PIN A0 SELECTION FOR AF
	AFIO->EVCR  &=~AFIO_EVCR_PIN_1;  
	AFIO->EVCR  &=~AFIO_EVCR_PIN_2;
	AFIO->EVCR  &=~AFIO_EVCR_PIN_3; 
	
	AFIO->EVCR  |=AFIO_EVCR_PIN_0; //PIN A1 SELECTION FOR AF
	AFIO->EVCR  &=~AFIO_EVCR_PIN_1;  
	AFIO->EVCR  &=~AFIO_EVCR_PIN_2;
	AFIO->EVCR  &=~AFIO_EVCR_PIN_3; 
	
	AFIO->EVCR  &=~AFIO_EVCR_PIN_0; //PIN A2 SELECTION FOR AF
	AFIO->EVCR |=AFIO_EVCR_PIN_1;  
	AFIO->EVCR &=~AFIO_EVCR_PIN_2;
	AFIO->EVCR  &=~AFIO_EVCR_PIN_3; 
	
	AFIO->EVCR  |=AFIO_EVCR_PIN_0; //PIN A3 SELECTION FOR AF
	AFIO->EVCR  |=AFIO_EVCR_PIN_1;  
	AFIO->EVCR  &=~AFIO_EVCR_PIN_2;
	AFIO->EVCR  &=~AFIO_EVCR_PIN_3; 
	
	
	


AFIO->EVCR  |=AFIO_EVCR_PIN_0;     // SELECT PIN_7 FOR AF
AFIO->EVCR  |=AFIO_EVCR_PIN_1;
AFIO->EVCR  |=AFIO_EVCR_PIN_2;
AFIO->EVCR  &=~AFIO_EVCR_PIN_3;	



	
	
/*-------------END OF GPIO CONFIGURATIONS-------------------------------*/



/*-------------------TIMER2 CONFIGURATION---------------------------*/

  TIM2->SR &=~TIM_SR_UIF; //clear the timer rollover bit
  TIM2->PSC =0x0023;    //values to 50 HZ frequency
	TIM2->ARR=0x9C3F;
	
	
	TIM2->CCMR1 &=~TIM_CCMR1_CC1S_0;
	TIM2->CCMR1 &=~TIM_CCMR1_CC1S_1;
	
	TIM2->CCMR1 |=TIM_CCMR1_OC1M_1; // PWM mode normal is selected (110 is for normal mode, 111 for inverted mode)
	TIM2->CCMR1 |=TIM_CCMR1_OC1M_2;
	TIM2->CCMR1 &=~TIM_CCMR1_OC1M_0;
	TIM2->CCMR1 |=TIM_CCMR1_OC1PE; //Preload enable for timer 2 channel 1
	TIM2->CCMR1 &=~TIM_CCMR1_OC1FE;
	
	
	TIM2->CCMR1 |=TIM_CCMR1_OC2M_1; // PWM mode normal is selected (110 is for normal mode, 111 for inverted mode)
	TIM2->CCMR1 |=TIM_CCMR1_OC2M_2;
	TIM2->CCMR1 &=~TIM_CCMR1_OC2M_0;
	TIM2->CCMR1 |=TIM_CCMR1_OC2PE; //Preload enable for timer 2 channel 2
	
	TIM2->CCER |=TIM_CCER_CC1E; //enabling channel 2 of Timer 2
	TIM2->CCER |=TIM_CCER_CC2E; //enabling channel 2 of Timer 2
	
	//TIM2->BDTR |=TIM_BDTR_MOE; 
	TIM2->CR1 |=TIM_CR1_ARPE;
	TIM2->CR1 |=TIM_CR1_CEN;      // Enable TIMER 3
	TIM2->EGR |=TIM_EGR_UG;      //Update event generation timer registers will reset after this update event generation
  
	TIM2->CCMR1 |= TIM_CCMR1_OC2CE;
	TIM2->CCMR1 |= TIM_CCMR1_OC1CE;

 
/*-------------------END OF TIMER2 CONFIGURATION---------------------------*/	
	
	
	
/*-------------------TIMER3 CONFIGURATION---------------------------*/

  TIM3->SR &=~TIM_SR_UIF; //clear the timer rollover bit
  TIM3->PSC =0x0023;
	TIM3->ARR=0x9C3F;
	TIM3->CCR2=0X0000;	
	
	
	TIM3->CCMR1 |=TIM_CCMR1_OC2M_1; // PWM mode normal is selected (110 is for normal mode, 111 for inverted mode)
	TIM3->CCMR1 |=TIM_CCMR1_OC2M_2;
	TIM3->CCMR1 &=~TIM_CCMR1_OC2M_0;
	TIM3->CCMR1 |=TIM_CCMR1_OC2PE; //Preload enable for timer 2 channel 2
	
	
	TIM3->CCER |=TIM_CCER_CC2E; //enabling channel 2 of Timer 2
	
	//TIM3->BDTR |=TIM_BDTR_MOE; 
	TIM3->CR1 |=TIM_CR1_CEN;      // Enable TIMER 3
	TIM3->EGR |=TIM_EGR_UG;      //Update event generation timer registers will reset after this update event generation
  
	TIM3->CCMR1 |= TIM_CCMR1_OC2CE;
	
/*-------------------END OF TIMER3 CONFIGURATION---------------------------*/		
	
	
	
/*---------------------SUPER LOOP----------------------*/	
	
	
	
while(1)
{

TIM2->CCR2=999; //0 degree rotation 799 0X31F
//TIM2->CCR1=999; //If enabling this Timer 2 all channels not working
TIM3->CCR2=999; 

	
delay();
	
TIM2->CCR2=2999;
//TIM2->CCR1=2999; //If enabling this Timer 2 all channels not working
TIM3->CCR2=2999;

delay();
	
TIM2->CCR2=4799;
//TIM2->CCR1=4799; //If enabling this Timer 2 all channels not working
TIM3->CCR2=4799;

delay();
	
}	

	
/*----------------------END OF SUPER ------------------*/	


}


/*--------------------------END OF MAIN---------------------*/


/*---------------USER DEFINED FUNCTIONS------------------*/


void delay(void)
{
  volatile unsigned int i;

  for (i = 0; i <8000000; i++)
    ;
}


/*------------END OF USER DEFINED FUNCTIONS----------------*/
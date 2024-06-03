#include <stdint.h>

// register address
#define RCC_BASE      0x40021000
#define GPIOC_BASE    0x40011000
#define TIM4_BASE     0x40000800

#define RCC_APB2ENR   *(volatile uint32_t *)(RCC_BASE   + 0x18)
#define RCC_APB1ENR   *(volatile uint32_t *)(RCC_BASE   + 0x1C)

// GPIO address
#define GPIOC_CRH     *(volatile uint32_t *)(GPIOC_BASE + 0x04)
#define GPIOC_ODR     *(volatile uint32_t *)(GPIOC_BASE + 0x0C)

// bits related with RCC enabling features
#define RCC_IOPCEN          (1<<4)
#define GPIOC13             (1UL<<13)
#define TIM4EN              (1<<2)


#define TIM4_SR      *(volatile uint32_t *)(TIM4_BASE + 0x10)
#define TIM4_CR1     *(volatile uint32_t *)(TIM4_BASE )
#define TIM4_CNT     *(volatile uint32_t *)(TIM4_BASE + 0x24)


#define TIM_CEN             1  
#define TIM_SR_UIF          1


void init_timer()
{
        
    RCC_APB1ENR |= TIM4EN;
    TIM4_CR1 |= TIM_CEN;
    TIM4_SR = 0;
    while (!(TIM4_SR & TIM_SR_UIF));

}

void init_config_io()
{
    RCC_APB2ENR |= RCC_IOPCEN;
    GPIOC_CRH   &= 0xFF0FFFFF;
    GPIOC_CRH   |= 0x00200000;
    
}


int main(void)
{
   init_config_io();
   init_timer();

    GPIOC_ODR |=  GPIOC13;
    
   uint32_t timer_reception = 0;
   while (1)
   {
        timer_reception = TIM4_CNT;
        if(timer_reception == 32000)
                GPIOC_ODR ^=  GPIOC13;
   }
   
    return 0;

}

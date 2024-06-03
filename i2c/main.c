#include <stdint.h>
/*
 *
 * Copyright (c) 2022 
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 * 
 * Author : Antonio ( Lord Feistel
 * e-mail : jr.overhead@gmail.com
 * repo   : https://github.com/lord-feistel/baremetal.git
 * 
 */


// register address
#define RCC_BASE      0x40021000
#define GPIOC_BASE    0x40011000
#define RCC_APB2ENR   *(volatile uint32_t *)(RCC_BASE   + 0x18)
#define GPIOC_CRH     *(volatile uint32_t *)(GPIOC_BASE + 0x04)
#define GPIOC_ODR     *(volatile uint32_t *)(GPIOC_BASE + 0x0C)

// bit fields
#define RCC_IOPCEN   (1<<4)
#define GPIOC13      (1UL<<13)
#define RCC_IOPBEN   (1<<3)
#define AFIO_EN      1


//i2c
#define RCC_APB1ENR   *(volatile uint32_t *)(RCC_BASE   + 0x1C)
#define GPIOB_BASE    0x40010C00
#define GPIOB_CRL    *(volatile uint32_t *)(GPIOB_BASE)
#define GPIOB_CHR    *(volatile uint32_t *)(GPIOB_BASE   + 0x04)


#define I2C1_BASE       0x40005400
#define I2C_CR1         *(volatile uint32_t *)(I2C1_BASE)
#define I2C_CR2         *(volatile uint32_t *)(I2C1_BASE+ 0x04)

#define I2C_OAR1        *(volatile uint32_t *)(I2C1_BASE + 0x08)
#define I2C_DR          *(volatile uint32_t *)(I2C1_BASE + 0x10)
#define I2C_CCR         *(volatile uint32_t *)(I2C1_BASE + 0x1C)
#define I2C_DR          *(volatile uint32_t *)(I2C1_BASE + 0x10)
#define I2C_SR1         *(volatile uint32_t *)(I2C1_BASE + 0x14)
#define I2C_SR2         *(volatile uint32_t *)(I2C1_BASE + 0x18)
#define I2C_TRISE       *(volatile uint32_t *)(I2C1_BASE + 0x20)




#define AFIO_BASE       0x40010000
#define AFIO_MAPR       *(volatile uint32_t *)(AFIO_BASE + 0x04)


#define I2C_CR1_START   (1<<8)
#define I2C_CR1_STOP    (1<<9)
#define I2C_BUSY        (1<<1)
#define I2C_SWRST       (1<<15)
#define I2C_EN_CR1      0x01
#define I2C1_REMAP      (1<<1)
#define I2C1_EN_APB  (1<<21)



void io_config()
{
    // related withthe blink led
    
    // enables GPIOC
    RCC_APB2ENR |= RCC_IOPCEN;

    // configure as output
    GPIOC_CRH   &= 0xFF0FFFFF;
    GPIOC_CRH   |= 0x00200000;





}


void i2c_config()
{


    // enables i2c
    RCC_APB1ENR |= I2C1_EN_APB;
    
    
    // related wioth i2c

    // enables GPIO B clock
    RCC_APB2ENR |= RCC_IOPBEN;
    // enable alternate function
    RCC_APB2ENR |= AFIO_EN;
  
    // Remaping to pin 8 and 9 
    //AFIO_MAPR   |= I2C1_REMAP;
    // configure as MODE9 = 00 (reset state) and CNF9 = 11 alternate function open drain
    
    // GPIOB_CHR   = 0x66;
    GPIOB_CRL = 0xEE000000;//(0xEE << 24);

    
    // set state busy
    // I2C_SR2 |= I2C_BUSY;

    // Reset I2C
    I2C_CR1 |= I2C_SWRST;
    I2C_CR1 &= ~I2C_SWRST;
    
    // Configure own address
    I2C_OAR1 = 0;

    // Clock speed
    I2C_CR2 = 0x10;
    //remap the pin PB8 and PB9 as I2C
    //configuring rise time
    I2C_TRISE = 0x12;   

    I2C_CCR = 0x45;

    //enable i2c
    I2C_CR1     |= I2C_EN_CR1;
    // Peripheral ready
    //I2C_SR2 &= ~I2C_BUSY;

    //I2C_CR1 |= (1<<10);

    I2C_CR1 |= I2C_CR1_START;
        
 
}


void main(void)
{

    io_config();
    i2c_config();

    while(1)
    {
        GPIOC_ODR |=  GPIOC13;
        for (int i = 0; i < 50000; i++); // arbitrary delay
        GPIOC_ODR &= ~GPIOC13;
        for (int i = 0; i < 50000; i++); // arbitrary delay
    

        //for(int i = 0 ;i < 500000; i++);



        //while (!(I2C_SR1 & (1<<7)));  // wait for TXE bit to set
        
        volatile uint32_t * a = I2C_SR1;      
        // if uncomment some signal appear
        I2C_DR = 0x21;
        //while (!(I2C_SR1 & (1<<2)));  // wait for BTF bit to set


        // I2C_CR1 |= I2C_CR1_START;

        // I2C_DR = 0x0F;

        // I2C_CR1 ^= I2C_CR1_START;


    }



}

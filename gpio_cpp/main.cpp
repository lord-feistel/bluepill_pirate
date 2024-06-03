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
 * Author : Antonio ( Lord Feistel )
 * e-mail : jr.overhead@gmail.com
 * repo   : https://github.com/lord-feistel/stm32_baremetal
 *
 */


#include <cstdint>

class Util{

    public:
      // On the next example we will replace it by a timer   
      static void getSomeSleep(uint32_t some)
      {

            for (int i {}; i < some; i++)
              // just to show that is 
              //possible use nop sequence 
              // for that
                __asm__("nop"); 
      }

};

class GPIO_LED {

public:

  // class constructor will arrange the pin configuration
  GPIO_LED() 
  {

    // I kept the almost the same names of the register
    // in the  reference manual. It makes easier
    // understanding what is happening.

    this->RCC_APB2ENR = (volatile uint32_t *)(RCC_BASE + RCC_APB2ENR_OFFSET);
    this->GPIOC_CRH = (volatile uint32_t *)(GPIOC_BASE + GPIOC_CRH_OFFSET);
    this->GPIOC_ODR = (volatile uint32_t *)(GPIOC_BASE + GPIOC_ODR_OFFSET);

    // Enables clock on GPIO C
    *(this->RCC_APB2ENR) |= RCC_IOPCEN;
    // Enabling only GPIOC 13 as output
    *(this->GPIOC_CRH) |= GPIO_13_CONF;
  }

  // set pin
  void setPin() { *(this->GPIOC_ODR) |= GPIOC13; }
  // unset pin
  void cleanPin() { *(this->GPIOC_ODR) &= ~GPIOC13; }


private:

  // Registers base address ///////////////////////////

  // please check the section 3.3 memory map
  // on the reference manual


  // Reset and clock control RCC
  // fromt 0x40021000 to 0x400213FF  

  // It's used to enable peripherals e.g. GPIO pins, i2c. 
  
  // The base address is the start address of certain group of 
  // control registers on this case
  
  // Start address of Reset and clock control RCC
  const uint32_t RCC_BASE = 0x40021000;

  // Start of address of GPIO C configurations
  const uint32_t GPIOC_BASE = 0x40011000;

  // Offsets inside registers /////////////////////////////
  // please check section 3.3 memory map
  // for further details.

  // APB2 peripheral clock enable register
  const uint32_t RCC_APB2ENR_OFFSET = 0x18;
  // Port configuration register high
  const uint32_t GPIOC_CRH_OFFSET = 0x04;
  // Port output data register
  const uint32_t GPIOC_ODR_OFFSET = 0x0C;
  // used to set the bit 21 of GPIOC_CRH
  // enabling the GPIOC pin 13 as output
  const uint32_t GPIO_13_CONF = (1<<21);


  // Bit labels ////////////////////////////////////////////
  // Used on bit manipulation
  const uint32_t RCC_IOPCEN = (1 << 4);
  const uint32_t GPIOC13 = (1UL << 13);

  // Variables used on the configuration //////////////////
  volatile uint32_t * RCC_APB2ENR;
  volatile uint32_t * GPIOC_CRH;
  volatile uint32_t * GPIOC_ODR;

};

int main(void) 
{

  GPIO_LED led;

  while (1) 
  {
    Util::getSomeSleep(50000);
    led.setPin();
    Util::getSomeSleep(50000);
    led.cleanPin();

  }
}

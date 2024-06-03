.cpu cortex-m3
.syntax unified

/**

Copyright (c) 2022 
  
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>. 
  
  
Author : Antonio ( Lord Feistel )

repo : https://github.com/lord-feistel/pytrade

e-mail : jr.overhead@gmail.com

About:

Simple programing to understand input and output
when A1 receive a input it sets A0 to 1 else set A0
to 0


**/



@used registers

/*
	check manual to understand the function
	of those special registers

*/

.equ	RCC		,	0x40021000;
.equ 	RCC_APB2RSTR	,	0x40021018;	
.equ	GPIOA_BASE	,	0x40010800
.equ 	GPIOA_CRL	,	0x40010800
.equ 	GPIOA_CRH	,	0x40010804
.equ 	GPIOA_ODR	,	0x4001080c
.equ 	GPIOA_IDR	,	0x40010808



.thumb_func

.global _start
_start:
    stacktop: .word 0x20001000
    .word main
    
.thumb_func
.global main

main:

	@configure port
	
	@enable port A
	ldr r0,	=(1<<2)	
	ldr r1, =#RCC_APB2RSTR
	str r0, [r1]
	
	/*	
		value to be loaded on GPIOA_CRL
		
		bits 0 to 4
		CNF0 +  MODE0
		mode = 01 to specify the maximum output
		cnf  = 00 to specify output
		
		bits 0 to 4
		CNF1 +  MODE1
		mode = 00 not important to input
		cnf  = 10 to specify input	
	
	*/
	
	
	ldr r0, =0b10000001
	ldr r1, =#GPIOA_CRL
	str r0, [r1]

init:	

	ldr r0,	=0	
	ldr r1, =GPIOA_ODR
	str r0, [r1]
	
loop:

	ldr r2, =#0x40010808
	ldr r3, [r2]
	and r3, r3,#0b10
	cmp r3, #2
	bne led_off

led_on:		
	ldr r0,	=1	
	ldr r1, =GPIOA_ODR
	str r0, [r1]
	b loop

led_off:
	ldr r0,	=0	
	ldr r1, =GPIOA_ODR
	str r0, [r1]
	b loop
	
 

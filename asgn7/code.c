#include "defines.h"
#include <stdbool.h>
#include <stdint.h>
#include "code.h"
#include <stdio.h>


Code code_init(void){
	Code c;
	(&c)->top = 0;
	for(uint32_t i = 0; i < MAX_CODE_SIZE; i++){
		(&c)->bits[i] = 0;
		}
	return c;
	}
	

uint32_t code_size(Code *c){
	if (c){
		return c->top;
		}
	return 0;
	}
	
	

bool code_empty(Code *c){
	if (c){
		if (c->top > 0){
			return false;
			}
		}
	return true;
	}

bool code_full(Code *c){
	if (c){
		if (c->top == 256){
			return true;
			}
		}
	return false;
	}

bool code_set_bit(Code *c, uint32_t i){

	if ((i < 0) || ( i > 255)){
		return false;
		}
	if(c){
		uint32_t index = i/8; 
		c->bits[index] = c->bits[index] | 1UL<<(i%8);
		//printf("the current bit index has a value of %u\n", c->bits[index]);
		return true;
		}

	return false;
	
	}
	
	

bool code_clr_bit(Code *c, uint32_t i){
	if ((i < 0) || ( i > 255)){
		return false;
		}
	if(c){

		uint32_t index = i/8;
		c->bits[index] = c->bits[index] & ~(1UL<<(i%8));
		return true;
		}
	return false;
	}
	

bool code_get_bit(Code *c, uint32_t i){
	if (( i > 255)){
		return false;
		}
	if(c){
		
		
		uint32_t index = i/8;

		uint8_t ival = c->bits[index];
		//printf("the current bit index has a value of %u\n", ival);
		ival = ival & (1UL<<(i%8));
		ival = ival >> (i%8);
		//printf("the current ival is now (should be 1 for last 4) for index 8-11 %u\n", ival);
		if (ival == 1){
			return true;
			}
		}
	return false;
	}
	

bool code_push_bit(Code *c, uint8_t bit){
	if (c->top == 256){
		return false;
		}
	if (c){
		if (bit == 0){
			c->top++;
			code_clr_bit(c, c->top-1); 
			return true;
			}
		else if (bit == 1){
			c->top++;
			code_set_bit(c, c->top-1);
			return true;
			}
		}
	return false;
	}
		
	

bool code_pop_bit(Code *c, uint8_t *bit){
	if(c->top == 0){
		return false;
		}
	if (c){
		if (code_get_bit(c,c->top-1) == true){
			*bit = 1;
			}
		else if(code_get_bit(c,c->top-1) == false){
			*bit = 0;
			}

		code_clr_bit(c,c->top-1);
		c->top -=1;
		return true;
		}
	return false;
	}
		
		

void code_print(Code *c){
	for(uint32_t i = 0; i < 20; i++){
		printf("%hhx", code_get_bit(c,i));
		}
	}

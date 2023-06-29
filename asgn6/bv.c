
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bv.h"

//typedef struct BitVector BitVector;

//this class will contain the implementation for bit vectors
//a data structor that will look like this
//  1    2    3    4   
//[0000,1000,0100,0111]

struct BitVector{
	uint32_t length;
	uint64_t *vector;
	};
	

BitVector *bv_create(uint32_t length){
	//BloomFilter * bf = (BloomFilter*) malloc (sizeof (BloomFilter))
	BitVector * bv = (BitVector*) malloc (sizeof(BitVector));
	bv->length = length;

	if (bv != NULL){
		uint32_t l_copy = length;
		uint32_t counter = 0;
		while (l_copy > 64){
			counter += 1;
			l_copy -=64;

			}
		if(l_copy != 0 && l_copy <= 64){
			counter++;
			}
			
		bv->vector = (uint64_t *)calloc(counter, sizeof(uint64_t));
		if(bv->vector != NULL){
			return bv;
			}
		free(bv);
		}
	return (BitVector *) NULL;
	}
		
		

void bv_delete(BitVector **bv){ //the destructor.
	if ((*bv) != NULL){
		free((*bv)->vector);
		free(*bv);
	}
}

uint32_t bv_length(BitVector *bv){
	return bv->length;
	}

void bv_set_bit(BitVector *bv, uint32_t i){
	//use %64 to get the position of the bit
	//use /64 to get the array of the bit. 
	uint32_t arr_index = i/64;
	bv->vector[arr_index] = bv->vector[arr_index] | 1UL<<((i%64)-1);
	}

void bv_clr_bit(BitVector *bv, uint32_t i){
	uint32_t arr_index = i/64;
	bv->vector[arr_index] = bv->vector[arr_index] & ~(1UL<<((i%64)-1));
	}
	

uint8_t bv_get_bit(BitVector *bv, uint32_t i){
	uint32_t arr_index = i/64;
	uint64_t ret_val = bv->vector[arr_index];
	ret_val = ret_val & (1UL<<((i%64)-1));
	ret_val = ret_val>>(i-1);
	return ret_val;
	}
	

void bv_print(BitVector *bv){
	for(uint32_t i = 0; i < bv->length; i++){
		printf("position i: %u ith-bit: %hhx\n",i,bv_get_bit(bv,i));
		}
	}
	


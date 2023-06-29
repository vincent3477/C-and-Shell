

#include "bv.h"
#include "bf.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "city.h"
#include <stdio.h>

#define N_HASHES 5

//typedef struct BloomFilter BloomFilter;
/*what will the bloom filter be for?
It will take a list of words, oldspeak in this case, and add it the bloom filter. 
If a badspeak is found in the bloom filter, then disicipline must be taken.
*/ 

static uint64_t default_salts[] = {
	0x5adf08ae86d36f21 ,
	0x419d292ea2ffd49e ,
	0x50d8bb08de3818df ,
	0x272347aea4045dd5 ,
	0x7c8e16f768811a21
	};

struct BloomFilter {
	uint64_t salts[N_HASHES]; //create an initalization key. We will use k=5 different salts.
	uint32_t n_keys;
	uint32_t n_misses;
	uint32_t n_bits_examined;
	uint32_t n_hits;

	BitVector *filter;
	};

BloomFilter *bf_create(uint32_t size){
	BloomFilter * bf = (BloomFilter*) malloc (sizeof (BloomFilter)) ;
	if (bf){
		//printf("value of s %u\n", size);
		bf -> n_keys = bf->n_hits = 0;
		bf-> n_misses = bf->n_bits_examined = 0;
		for (int i = 0; i < N_HASHES; i++){
			bf->salts[i] = default_salts[i];
			}
		bf->filter = bv_create(size);
		if (bf->filter == NULL){
			free(bf);
			bf = NULL;
			}
		}//what to free n_keys, n_misses, filter
	return bf;
	}
	
	

void bf_delete(BloomFilter **bf){
	if ((*bf) != NULL){
		if ((*bf)->filter != NULL){
			bv_delete(&(*bf)->filter);
			}
		free(*bf);
		}
	}		

uint32_t bf_size(BloomFilter *bf){
	return bv_length(bf->filter);
	}
	
void bf_insert(BloomFilter *bf, char *oldspeak){
	
	//hash with each of the 5 different salts
	for(int i = 0; i < 5; i ++){
		bv_set_bit(bf->filter,hash(bf->salts[i], oldspeak) % bf_size(bf));
		}
	bf->n_keys++;

	}
	
	

bool bf_probe(BloomFilter *bf, char *oldspeak){
	for(int i = 0; i < 5; i ++){
		bf->n_bits_examined ++;
		if ((bv_get_bit(bf->filter,hash(bf->salts[i], oldspeak) % bf_size(bf)))==0){
			bf->n_misses++;
			return false;
			
		}
	}
	bf->n_hits ++;
	return true;
}	

uint32_t bf_count(BloomFilter *bf){
	uint32_t counter = 0;
	for(uint32_t i = 0; i < bf_size(bf); i ++){
		if(bv_get_bit(bf->filter,i)==1){
			counter ++;
			}
		}
	return counter;
	}
	

void bf_print(BloomFilter *bf){
	bv_print(bf->filter);
	}

void bf_stats(BloomFilter *bf, uint32_t *nk, uint32_t *nh, uint32_t *nm, uint32_t *ne){

	*nk = bf->n_keys;
	*nh = bf->n_hits;
	*nm = bf->n_misses;
	*ne = bf->n_bits_examined;

	}

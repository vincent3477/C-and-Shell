
#include <stdio.h>
#include "ll.h"
#include "city.h"
#include <stdbool.h>
#include <stdint.h>
#include "ht.h"
#include "node.h"
struct HashTable {
	uint64_t salt;
	uint32_t size;
	uint32_t n_keys;
	uint32_t n_hits;
	uint32_t n_misses;
	uint32_t n_examined;
	bool mtf;
	LinkedList **lists;
	};

HashTable *ht_create(uint32_t size, bool mtf){
	HashTable * ht = ( HashTable *) malloc(sizeof(HashTable)) ;
	if (ht != NULL){
		ht->mtf = mtf;
		ht->salt =  0x9846e4f157fe8840;
		ht -> n_hits = ht -> n_misses = ht -> n_examined = 0;
		ht->n_keys = 0;
		ht->size = size;
		ht -> lists = (LinkedList **)calloc(size,sizeof ( LinkedList *)) ;
		if(!ht->lists){
			free(ht);
			ht = NULL;
			}
		}
	return ht;
	}
	
	
void ht_print(HashTable *ht){

	uint32_t index = 0;
	while(index < ht->size){
		if (ht->lists[index] != NULL){
			printf("%u ", index % ht->size);
			ll_print(ht->lists[index]);
			}
		index++;
		} 
	}

	

void ht_delete(HashTable **ht){
	if (*ht != NULL){
		if((*ht)->lists != NULL){
			for (uint32_t i = 0 ; i < (*ht)->size; i++){
				if((*ht)->lists[i] != NULL){
					ll_delete(&(*ht)->lists[i]);
					}
				}
			free((*ht)->lists);
			(*ht)->lists = NULL;
			}
		free(*ht);
		*ht = NULL;
		}
	}
				
		
	

uint32_t ht_size(HashTable *ht){
	return ht->size;
	}

Node *ht_lookup(HashTable *ht, char *oldspeak){
	uint32_t llseeks = 0; //number of times a linked lists looked up
	uint32_t lllinks = 0; //number of links we've traversed.
	ll_stats(&llseeks,&lllinks);
	ht->n_examined = lllinks;
	
	uint32_t l_index = hash(ht->salt,oldspeak) % ht->size; 
	
	if(ht->lists[l_index]){
		
		Node * f = ll_lookup(ht->lists[l_index], oldspeak);
		ll_stats(&llseeks,&lllinks);
		ht->n_examined = lllinks;

		if(f == NULL){
			ht->n_misses ++;
			}
		else{
			ht->n_hits ++;
			}
		return f;
		}
		
	ht->n_misses ++;
	return NULL;
	}
	
	
	
	

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak){
	uint32_t index = hash(ht->salt,oldspeak) % ht->size;
	if(ht->lists[index] != NULL){
		if(ll_lookup(ht->lists[index], oldspeak) == NULL){
		
		ht->n_keys ++;
		}
	}
	//uint32_t count = 0;
	if(ht->lists[index] == NULL){
		
		ht->lists[index] = ll_create(ht->mtf);
		ll_insert(ht->lists[index], oldspeak, newspeak);
		ht->n_keys++;
		}
	else{
		ll_insert(ht->lists[index], oldspeak, newspeak);

		}
	}

uint32_t ht_count(HashTable *ht){
	uint32_t count = 0;
	uint32_t index = 0;
	while(index < ht->size){
		if (ht->lists[index] != NULL){
			count++;
			}
		index++;
		}
	return count;
	}



void ht_stats(HashTable *ht, uint32_t *nk, uint32_t *nh, uint32_t *nm, uint32_t *ne){
	*nk = ht->n_keys;
	*nh = ht->n_hits;
	*nm = ht->n_misses;
	*ne = ht->n_examined;
	}
	



#include "messages.h"
#include "ht.h"
#include "parser.h"
#include <unistd.h>
#include <stdbool.h>
#include "bf.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define OPTIONS "ht:f:ms"
//REMEMBER TO RETURN 0!!! VERY IMPORTANT.
#define N_HASHES 5


void my_strcopy1(char * source, char * destination, uint32_t n){
	uint32_t i = 0; 
	for (i = 0; i < n && source[i]; i += 1){
		destination[i] = source[i];
		}
	for ( ; i < n; i ++){
		destination[i] = '\0';
		}
	return;
	}

int main(int argc, char **argv){
	int opt = 0;
	bool print_stats = false;
	uint32_t ht_size1 = 10000;
	uint32_t bf_size1 = 524288;
	bool mtf = false;
	while((opt = getopt(argc, argv, OPTIONS))!=-1){
		switch(opt){
			case 'h':
				fprintf(stderr,"Usage: ./banhammer [options]\n"
  "./banhammer will read in words from stdin, identify any badspeak or old speak and output an\n"
  "appropriate punishment message. The badspeak and oldspeak (with the newspeak translation)\n" 
  "that caused the punishment will be printed after the message. If statistics are enabled\n"
  "punishment messages are suppressed and only statistics will be printed.\n"
  "  -t <ht_size>: Hash table size set to <ht_size>. (default: 10000)\n"
  "  -f <bf_size>: Bloom filter size set to <bf_size>. (default 2^19)\n"
  "  -s          : Enables the printing of statistics.\n"
  "  -m          : Enables move-to-front rule.\n"
  "  -h          : Display program synopsis and usage.\n");
  				break;
  			case 't':
  				ht_size1 = strtoul(optarg, NULL, 10);
  				break;
  			case 'f':
  				bf_size1 = strtoul(optarg, NULL, 10);

  				break;
  			case 'm':
  				mtf = true;
  				break;
  			case 's':
  				print_stats = true;
  				break;
  			default:
  				fprintf(stderr,"Usage: ./banhammer [options]\n"
  "./banhammer will read in words from stdin, identify any badspeak or old speak and output an\n"
  "appropriate punishment message. The badspeak and oldspeak (with the newspeak translation)\n" 
  "that caused the punishment will be printed after the message. If statistics are enabled\n"
  "punishment messages are suppressed and only statistics will be printed.\n"
  "  -t <ht_size>: Hash table size set to <ht_size>. (default: 10000)\n"
  "  -f <bf_size>: Bloom filter size set to <bf_size>. (default 2^19)\n"
  "  -s          : Enables the printing of statistics.\n"
  "  -m          : Enables move-to-front rule.\n"
  "  -h          : Display program synopsis and usage.\n");
  				return 1;
  			}
  		}
  
  
    	char * bad_words = (char*)malloc(1000*sizeof(char));

  			
  		
  	//read in a list the badspeak.
  	FILE *f = fopen("badspeak.txt","r");
  	Parser * p = parser_create(f);
  	BloomFilter * bf = bf_create(bf_size1);
  	HashTable * ht = ht_create(ht_size1, mtf);

  	while(!feof(f)){
  		fgets(bad_words,1000,f);
  		while(next_word(p,bad_words) == true){
			
  			bf_insert(bf,bad_words);
			
  			ht_insert(ht, bad_words, NULL);
  			}
  		
  		}
  	fclose(f);
  	parser_delete(&p);
  	
	free(bad_words);
	char * copy = (char*)malloc(1000*sizeof(char));
	char * word = (char*)malloc(1000*sizeof(char)); //represents old words.
  	FILE * nf = fopen("newspeak.txt","r");
  	Parser * np = parser_create(nf);

  	//int times = 0;
  	while(!feof(nf)){
  		fgets(word,1000,nf);
  		while(next_word(np,word)){
  			
  			bf_insert(bf,word);
  			my_strcopy1(word,copy,1000);
  			next_word(np,word);
  			ht_insert(ht,copy,word);
  			}
  		}
  	
  		
  	parser_delete(&np);
  	fclose(nf);
  	
  	
  	FILE * nfs = stdin;
  	nfs = stdin;

  	
  	
  	Parser * nps = parser_create(nfs);
  	
  	char * input = (char*)malloc(1000*sizeof(char));

  	
  	LinkedList * oldspeaks = ll_create(mtf);//if the citizedn is caught using an oldspeak that has a newspeak translation, then they are guilty of not using RIGHTSPEAK.
  	LinkedList * badspeaks = ll_create(mtf);//if there is no newspeak translation, then the citiizen is guility of thoughht crime
  	//if both applies, then we have to print the mixspeak message.
  	
	

  	while(!feof(nfs)){
  		fgets(input,1000,nfs);
  		while(next_word(nps,input) == true){
			//printf("word being processed %s\n",input);
  			if(bf_probe(bf,input) == 1){
 				Node * f = ht_lookup(ht, input);
 				

 				if(f != NULL){
					
 					if((f->oldspeak != NULL) && (f->newspeak == NULL) && !print_stats){
 						ll_insert(badspeaks, f->oldspeak, NULL);


 						 						
 						}
 					else if((f->oldspeak != NULL) && (f->newspeak != NULL) && !print_stats ){

 						ll_insert(oldspeaks, f->oldspeak, f->newspeak);

 						}
 					}
 					
 				
  			}
  			
  		//fgets(word,1000,f);
  		}

  	}
  	
  	//printf("\n");
  	
  	//fclose(nfs);
  	
  	//printf("oldspeak length %u\n", ll_length(oldspeaks));
  	//printf("badspeak length %u\n", ll_length(badspeaks));
  	//printf("%u is equal to 0, %u\n",ll_length(badspeaks), ll_length(badspeaks)==0);
 	//printf("bad not equal 0? %u\n", ll_length(badspeaks)!=0);
 
  	
  	
  	
  	if((ll_length(oldspeaks) > 0) && (ll_length(badspeaks) > 0) && !print_stats){
  		printf("%s",mixspeak_message);
  		ll_print(badspeaks);
  		ll_print(oldspeaks);
  		
  		}

  	else if((ll_length(oldspeaks) != 0) && !print_stats){
  		printf("%s",goodspeak_message);
  		ll_print(oldspeaks);
  		}
  	else if((ll_length(badspeaks) != 0)&& !print_stats){
  		printf("%s",badspeak_message);
  		ll_print(badspeaks);
  		}
  	
  	
  	
  	if(print_stats){
  		
  		uint32_t nk = 0; //n_keys for hash table
  		uint32_t nh = 0; //n_hits for hash table. 
  		uint32_t nm = 0; //n_misses for hash table.
  		uint32_t ne = 0;//n_examined for hash table.	
  		
  		uint32_t nkb = 0; //n_keys for bloom filter.
  		uint32_t nhb = 0; //n_hits for bloom filter. 
  		uint32_t nmb = 0; //n_misses for bloom filter.
  		uint32_t neb = 0;//n_examined for bloom filter.	
  		
  		ht_stats(ht, &nk, &nh, &nm, &ne);
  		bf_stats(bf,&nkb, &nhb, &nmb, &neb);
  		
  		
  		//printf("nhb is %u\n",nhb);
  		//printf("nmb is %u\n",nmb);
  		//printf("bf count is %u\n",bf_count(bf));
		//printf("bf size is %u\n",bf_size(bf));
		//printf("nh is %u\n",nh);
		//printf("nm is %u\n",nm);
  		//printf("neb is %u\n",neb);
  		//print statements above used for debugging purposes.
  		
  		double bits_examined_per_miss = 0;
  		double f_positives = 0;
  		double avg_seek_length = 0;
  		double bf_load = 0;
  		if (nmb != 0){
  			bits_examined_per_miss = (double)(neb - (N_HASHES * nhb))/(double)nmb;
  			}
  		if(nhb != 0){
  			f_positives = (double)nm/(double)nhb;
  			}
  		if((nhb != 0)||(nm != 0)){
  			avg_seek_length = (double)ne/(double)(nh+nm);
  			}
  		if(bf_size(bf) != 0 ){
  			bf_load = (double)bf_count(bf)/(double)bf_size(bf); 
  			}
  			
  	
  		
  		
	
  		
  		printf("ht keys: %u\n"
			"ht hits: %u\n"
			"ht misses: %u\n"
			"ht probes: %u\n"
			"bf keys: %u\n"
			"bf hits: %u\n"
			"bf misses: %u\n"
			"bf bits examined: %u\n"
			"Bits examined per miss: %1.6f\n" //should be 0 for badspeak.txt
			"False positives: %1.6f\n" //should be 0
			"Average seek length: %1.6f\n" //should be 1.75
			"Bloom filter load: %1.6f\n",nk, nh,  nm,ne,nkb,nhb,nmb,neb,bits_examined_per_miss,f_positives,avg_seek_length,bf_load);
		}				//should be 0.1299
	
	free(word);
  	free(copy);
  	//free(f);
  	

  	
  	ll_delete(&oldspeaks);
  	ll_delete(&badspeaks);
  	
  	bf_delete(&bf);
  	
  	parser_delete(&nps);

  	
  		
  	
  			
  		
  	return 0;
  	}
  				

				
	

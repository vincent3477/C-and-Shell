#include "bubble.h"
#include "heap.h"
#include "quick.h"
#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include "mtrand.h"
#include <inttypes.h>
#include "set.h"
#include "stats.h"
#define OPTIONS "asbqn:r:p:Hh"
#include <stdlib.h>
int main(int argc, char **argv){
	Stats s;
	Stats *stats = &s;
	Stats h;
	Stats *hstats = &h;
	Stats q;
	Stats *qstats = &q;
	Stats b;
	Stats *bstats = &b;
	Set choices = 0;
	uint32_t num_elem = 100;
	uint32_t print_elements = 100;
	int opt = 0;
	uint32_t seed = 13371453;
	while((opt = getopt(argc, argv, OPTIONS))!=-1){
		switch(opt){
			case 'a':
				choices = set_insert(choices, 0);
				break;
			case 's':
				choices = set_insert(choices,1);
				break;
			case 'b':
				choices = set_insert(choices, 2);
				break;
			case 'h':
				choices = set_insert(choices, 3);
				break;
			case 'q':
				choices = set_insert(choices, 4);
				break;
			case 'r':
				seed = strtoul(optarg, NULL, 10);
				break;
			case 'n':
				num_elem = strtoul(optarg, NULL, 10);
				if (num_elem < 1 || num_elem > 250000000){
					
					printf("SYNOPSIS\n"
   					"   A collection of comparison-based sorting algorithms.\n"
					"\n"
					"USAGE\n"
   					"   ./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]\n"
   					"\n"
					"OPTIONS\n"
   					"   -H              Display program help and usage.\n"
   					"   -a              Enable all sorts.\n"
   					"   -b              Enable Bubble Sort.\n"
   					"   -h              Enable Heap Sort.\n"
   					"   -q              Enable Quick Sort.\n"
   					"   -s              Enable Shell Sort.\n"
   					"   -n length       Specify number of array elements (default: 100).\n"
   					"   -p elements     Specify number of elements to print (default: 100).\n"
   					"   -r seed         Specify random seed (default: 13371453).\n");

					return 1;
					}
				break;
			case 'p':
   				print_elements = strtoul(optarg, NULL, 10);
				break;
			case 'H':
				printf("SYNOPSIS\n"
   					"   A collection of comparison-based sorting algorithms.\n"
					"\n"
					"USAGE\n"
   					"   ./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]\n"
   					"\n"
					"OPTIONS\n"
   					"   -H              Display program help and usage.\n"
   					"   -a              Enable all sorts.\n"
   					"   -b              Enable Bubble Sort.\n"
   					"   -h              Enable Heap Sort.\n"
   					"   -q              Enable Quick Sort.\n"
   					"   -s              Enable Shell Sort.\n"
   					"   -n length       Specify number of array elements (default: 100).\n"
   					"   -p elements     Specify number of elements to print (default: 100).\n"
   					"   -r seed         Specify random seed (default: 13371453).\n");
   				break;
   				return 0;
   			default :
				printf("SYNOPSIS\n"
   					"   A collection of comparison-based sorting algorithms.\n"
					"\n"
					"USAGE\n"
   					"   ./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]\n"
   					"\n"
					"OPTIONS\n"
   					"   -H              Display program help and usage.\n"
   					"   -a              Enable all sorts.\n"
   					"   -b              Enable Bubble Sort.\n"
   					"   -h              Enable Heap Sort.\n"
   					"   -q              Enable Quick Sort.\n"
   					"   -s              Enable Shell Sort.\n"
   					"   -n length       Specify number of array elements (default: 100).\n"
   					"   -p elements     Specify number of elements to print (default: 100).\n"
   					"   -r seed         Specify random seed (default: 13371453).\n");
   				break;
   				return 1;
   			
   				
   			}
   		}
   	mtrand_seed(seed);

   	uint32_t *bptr = (uint32_t*)malloc(num_elem*sizeof(int));
   	uint32_t *hptr = (uint32_t*)malloc(num_elem*sizeof(int));
   	uint32_t *qptr = (uint32_t*)malloc(num_elem*sizeof(int));
   	uint32_t *sptr = (uint32_t*)malloc(num_elem*sizeof(int));
   	
   	
   	uint32_t gen_rand = 0;
	for (uint32_t i = 0; i < num_elem; i++){

		gen_rand = mtrand_rand64() & 0x3fffffff;
		
		//gen_rand = test[i];
		
		bptr[i] = gen_rand;
		hptr[i] = gen_rand;
		qptr[i] = gen_rand;
		sptr[i] = gen_rand;
		


		

	}
	
	//check to make sure the specified print elements fall within the bounds of the array
	if(print_elements > num_elem){
			print_elements = num_elem;
			}

	uint32_t nums_per_row = 0;
	uint32_t k = 0;
	
   	if (set_member(choices, 0)==1){ //order should be bubble, heap, quick, and shell.
   		
   		

   		uint32_t k = 0;
   		
   		bubble_sort(bstats, bptr, num_elem);
   		printf("Bubble Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n",num_elem, bstats->moves, bstats->compares);
		for ( k = 0; k < print_elements; k++){
			if (nums_per_row >= 5){
				printf("\n");
				nums_per_row = 0;
			}
			printf("%13" PRIu32, bptr[k]);
			nums_per_row += 1;
		}
		nums_per_row = 0;
		if(print_elements > 0){
			printf("\n");
			}
		

   		heap_sort(hstats, hptr, num_elem);
   		printf("Heap Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n",num_elem, hstats->moves, hstats->compares);
		for ( k = 0; k < print_elements; k++){
			if (nums_per_row >= 5){
				printf("\n");
				nums_per_row = 0;
			}
			printf("%13" PRIu32, hptr[k]);
			nums_per_row += 1;
		}
		nums_per_row = 0;
		if(print_elements > 0){
			printf("\n");
			}

		
   		
   		quick_sort(qstats, qptr, num_elem);
   		printf("Quick Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n",num_elem, qstats->moves, qstats->compares);
		for ( k = 0; k < print_elements; k++){
			if (nums_per_row >= 5){
				printf("\n");
				nums_per_row = 0;
			}
			printf("%13" PRIu32, qptr[k]);
			nums_per_row += 1;
		}
		nums_per_row = 0;
		if(print_elements > 0){
			printf("\n");
		}
		
		shell_sort(stats, sptr, num_elem);
		printf("Shell Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n",num_elem, stats->moves, stats->compares);
		for ( k = 0; k < print_elements; k++){
			if (nums_per_row >= 5){
				printf("\n");
				nums_per_row = 0;
			}
			printf("%13" PRIu32, sptr[k]);
			nums_per_row += 1;
		}
		printf("\n");
	  
	}
		
	else{
		
		
		if (set_member(choices, 2) ==1){
			bubble_sort(bstats, bptr, num_elem);
			printf("Bubble Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n",num_elem, bstats->moves, bstats->compares);
			for ( k = 0; k < print_elements; k++){
				if (nums_per_row >= 5){
					printf("\n");
					nums_per_row = 0;
					}
				printf("%13" PRIu32, bptr[k]);
				nums_per_row += 1;
				}
			if(print_elements > 0){
				printf("\n");
				}
			}
			nums_per_row = 0;
				
			
		if(set_member(choices, 3) == 1){
			heap_sort(hstats, hptr, num_elem);
			printf("Heap Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n",num_elem, hstats->moves, hstats->compares);
			for ( k = 0; k < print_elements; k++){
				if (nums_per_row >= 5){
					printf("\n");
					nums_per_row = 0;
					}		
				printf("%13" PRIu32, hptr[k]);
				nums_per_row += 1;
				}
			if(print_elements > 0){
				printf("\n");
				}
			}
			nums_per_row = 0;
			
		if(set_member(choices, 4) == 1){
			quick_sort(qstats, qptr, num_elem);
			printf("Quick Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n",num_elem, qstats->moves, qstats->compares);
			for ( k = 0; k < print_elements; k++){
				if (nums_per_row >= 5){
					printf("\n");
					nums_per_row = 0;
					}
				printf("%13" PRIu32, qptr[k]);
				nums_per_row += 1;
				}
			if(print_elements > 0){
				printf("\n");
				}
			}
			nums_per_row = 0;
			
		if (set_member(choices, 1) ==1){
			shell_sort(stats, sptr, num_elem);
			printf("Shell Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n",num_elem, stats->moves, stats->compares);
			for ( k = 0; k < print_elements; k++){
				if (nums_per_row >= 5){
					printf("\n");
					nums_per_row = 0;
				}
				printf("%13" PRIu32, sptr[k]);
				nums_per_row += 1;
			}
			if(print_elements > 0){
				printf("\n");
				}
			}
		}
	
		
		
	
		
	free(bptr);	
	free(hptr);
	free(sptr);
	free(qptr);
			
	
	}
		
	



		
		
   		

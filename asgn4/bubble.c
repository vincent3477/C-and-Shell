#include <stdlib.h>
#include "stats.h"
#include <stdio.h>
#include <inttypes.h>

void bubble_sort(Stats *stats, uint32_t *arr, uint32_t n_elements){
	
	int swap_occurred = 0;
	for (uint32_t i = 0; i < n_elements; i++){
		swap_occurred = 0;

		for (uint32_t j = n_elements - 1;j>i ; j-=1){

			if (cmp(stats, arr[j], arr[j-1]) == -1){
				swap(stats, &arr[j], &arr[j-1]);

				swap_occurred = 1;
				}
			}
		if (swap_occurred == 0){
			break;
			}
	}
}





	

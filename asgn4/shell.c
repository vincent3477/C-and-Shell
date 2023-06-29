#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h>
#include <inttypes.h>
#include "stats.h"

//reading or writing an array counts as a move.
int next_gap(int x){
	if (x > 1){
		if (x <= 2){
			return 1;
			}
		else{
			return ((5*x)/11);
			}
		}
	else{
		return 0;
		}
}

void shell_sort(Stats *stats, uint32_t *arr, uint32_t n_elements){
	uint32_t start = next_gap(n_elements);
	
	for (uint32_t gap = start; gap > 0; gap = next_gap(gap)){


		for (uint32_t j = gap; j < n_elements;  j++){

			uint32_t temp = j;
			uint32_t temp_index = move(stats, arr[j]);
			while (temp >= gap && cmp(stats, temp_index, arr[temp-gap])==-1){
				arr[temp] = move(stats, arr[temp - gap]);

				move(stats, arr[temp]);

				temp -= gap;
			}
			arr[temp] = move(stats, temp_index);

		}
	}
	   	
}


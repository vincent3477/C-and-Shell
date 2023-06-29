


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stats.h"
#include "quick.h"
#include "shell.h"


void quick_sort(Stats *stats,uint32_t *arr, uint32_t n_elements){
	uint32_t small = 8;
	
	if (n_elements < small){
		shell_sort(stats,arr,n_elements);
		return;
	}

	uint32_t pivot = (arr[0] + arr[n_elements/2] + arr[n_elements - 1])/3;
	uint32_t pivot_position = 251000000;
	uint32_t swap_counter = n_elements - 1;

	int first_go = 1;
	

	
	
	
	for (uint32_t i = 0; i < n_elements; i++){
		if ((cmp(stats, arr[i], pivot) == -1)||(cmp(stats, arr[i], pivot) == 0)){ 
			swap_counter += 1;
			if (first_go == 1){
				swap_counter = 0;
				first_go = 0;
				}
			if (i != swap_counter){
				swap(stats, &arr[i],&arr[swap_counter]);
				}
		}
		if (arr[i] == pivot){
			//swap_counter += 1;
			pivot_position = swap_counter + 1;	
			swap(stats, &arr[i], &arr[swap_counter + 1]);
			}
	}
	
	
	if (pivot_position == 251000000){ //if the pivot is NOT in the array
		quick_sort(stats, arr + swap_counter + 1, n_elements - swap_counter -1);
		quick_sort(stats, arr, swap_counter+1);
		}
	else{
		quick_sort(stats, arr + pivot_position + 1,n_elements - pivot_position -1);
		quick_sort(stats, arr, pivot_position);
		}
	
}




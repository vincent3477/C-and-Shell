#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
int left_child(int x){
	return 2 * x + 1;
}

int right_child(int x){
	return 2 * x + 2;
}

int parent(int x){
	return (x-1)/2;
}

void up_heap (Stats *stats,uint32_t *arr, int x){
	while (x > 0 && (cmp(stats, arr[x], arr[parent(x)]) == -1)){ 
		
		swap(stats, &arr[x], &arr[parent(x)]);
		x = parent(x);
	}
}

void down_heap (Stats *stats,uint32_t *arr, int heap_size){
	int node = 0;

	int smaller = 0;
	while (left_child(node)<heap_size){
		if (right_child(node) == heap_size) {
			smaller = left_child(node);
			}
		else{
			if (cmp(stats, arr[left_child(node)], arr[right_child(node)])==-1 ){	
				smaller = left_child(node);
				}	
			else{
				smaller = right_child(node);
				}
			}
		if (cmp(stats, arr[node], arr[smaller]) == -1){
			break;
			}
		
		swap(stats, &arr[node], &arr[smaller]);
	
		node = smaller;
	}
}	


void heap_sort(Stats *stats, uint32_t *arr, uint32_t n_elements){
	//build the heap
        uint32_t *ptr = (uint32_t*)malloc(n_elements * sizeof(int));
        for (uint32_t i = 0; i < n_elements; i++){
                ptr[i] = move(stats, arr[i]);
                move(stats, ptr[i]);
                up_heap(stats,ptr, i);
        }
        //sort the heap
	uint32_t *sorted_list = (uint32_t*)malloc(n_elements * sizeof(int));
	for (uint32_t j = 0; j < n_elements; j ++){
		sorted_list[j] = move(stats, ptr[0]);
		ptr[0] = move(stats, ptr[n_elements - j - 1]);
		move(stats, ptr[0]);
		move(stats, sorted_list[j]);
		down_heap(stats, ptr, n_elements - j);
	}
	
	//To update the original array.
	for (uint32_t k = 0; k < n_elements; k ++){ 
		arr[k] = sorted_list[k];
	}
	free(ptr);
	free(sorted_list);
	

} 

	

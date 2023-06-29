
#include "node.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "pq.h"
#include <stdio.h>

struct PriorityQueue{
	uint32_t capacity;
	uint32_t head;
	Node ** nodes;
	};

PriorityQueue *pq_create(uint32_t capacity){
	PriorityQueue * pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	if(pq){
		pq->capacity = capacity;
		pq->head = 0;
		pq->nodes = (Node**)calloc(capacity, sizeof(Node));
		if (!pq->nodes){
			free(pq->nodes);
			pq->nodes = NULL;
			free(pq);
			pq=NULL;
			return pq;
			}
		
		}
	return pq;
	
	}
		
//the following funcitons will be used to implement a min heap. The below 5 functions are not to be used outside of this class.
int left_child(int x){  
	return 2 * x + 1;
	}

int right_child(int x){
	return 2 * x + 2;
	}
	
int parent(int x){

	return (x-1)/2;
}		


void up_heap(Node **n, int x){
	while (x > 0 && node_cmp(n[x], n[parent(x)])==0){
		Node * tmp = n[x];
		n[x] = n[parent(x)];
		n[parent(x)] = tmp;
		x = parent(x);
		}
	}
	
void down_heap(PriorityQueue *q, int heap_size){
	int node = 0;
	int smaller = 0;
	while(left_child(node) < heap_size){
		if (right_child(node) == heap_size){
			smaller = left_child(node);
			}
		else{
			if(node_cmp(q->nodes[left_child(node)],q->nodes[right_child(node)])==0){
				smaller = left_child(node);
				}
			else{
				smaller = right_child(node);
				}
			}
		if(node_cmp(q->nodes[node], q->nodes[smaller]) == 0){
			break;
			}
		Node * tmp = q->nodes[node];
		q->nodes[node] = q->nodes[smaller];
		q->nodes[smaller] = tmp;
		node=smaller;
		}
	}
void build_heap(PriorityQueue *q){
	Node ** heap = (Node**)calloc(q->head, sizeof(Node));

	for(uint32_t i = 0; i < q->head; i ++){
		heap[i] = q->nodes[i];
		up_heap(heap, i);
		}
	for(uint32_t i = 0; i < q->head; i ++){
		q->nodes[i] = heap[i];
		}
	}
		

void pq_delete(PriorityQueue **q){
	if(*q){
		if((*q)->nodes){
			int i = 0;
			while((*q)->nodes[i]){
				node_delete(&(*q)->nodes[i]);
				}
			free((*q)->nodes);
			(*q)->nodes = NULL;
			}
		free(*q);
		q = NULL;
		}
	}

bool pq_empty(PriorityQueue *q){
	if (q->head == 0){
		return true;
		}
	else{
		return false;
		}
	}

bool pq_full(PriorityQueue *q){
	if (q->head == q->capacity){
		return true;
		}
	else{
		return false;
		}
	}

uint32_t pq_size(PriorityQueue *q){
	return q->head;
	}

bool enqueue(PriorityQueue *q, Node *n){
	if(pq_full(q)){
		return false;
		}
	q->nodes[q->head] = n;
	q->head ++;
	build_heap(q);
	
	return true;
	}

bool dequeue(PriorityQueue *q, Node **n){
	if(pq_empty(q)){
		return false;
		}

	*n = q->nodes[0];
	q->nodes[0] = NULL;
	uint32_t offset = 0;
	while(offset+1 < q->head){
		q->nodes[offset] = q->nodes[offset+1];
		offset++;
		} 
	
	
	
	
	q->head-=1;
	down_heap(q, q->head);

	return true;
	}

void pq_print(PriorityQueue *q){
	for(uint32_t i = 0; i < q->capacity; i ++){
		node_print(q->nodes[i]);
		}
	}
/*	
int main (void){
	PriorityQueue * pq = pq_create(13);
	Node * a = node_create(65, 2);
	Node * b = node_create(66, 3);
	Node * c = node_create(67, 4);
	Node * d = node_create(68, 5);
	Node * e = node_create(69, 5);
	Node * g = node_create(70, 7);
	Node * h = node_create(71, 10);
	Node * i = node_create(72, 36);
	Node * j = node_create(73, 74);
	Node * k = node_create(74, 23);
	Node * l = node_create(75, 12);
	Node * m = node_create(76, 65);
	Node * o = node_create(77, 45);
	Node * p = node_create(78, 14);
	
	Node * deq = NULL;
	Node * deq1 = NULL;
	Node * deq2 = NULL;
	Node * deq3 = NULL;
	Node * deq4 = NULL;
	
	enqueue(pq,a);
	enqueue(pq,b);
	enqueue(pq,c);
	enqueue(pq,d);
	enqueue(pq,e);
	enqueue(pq,g);
	enqueue(pq,h);
	enqueue(pq,i);
	enqueue(pq,j);
	enqueue(pq,l);
	enqueue(pq,m);
	enqueue(pq,o);
	enqueue(pq,p);
	enqueue(pq,k);
	dequeue(pq,&deq);
	dequeue(pq,&deq1);
	dequeue(pq,&deq2);
	dequeue(pq,&deq3);
	dequeue(pq,&deq4);
	node_print(deq);
	node_print(deq1);
	node_print(deq2);
	node_print(deq3);
	node_print(deq4);
	
	
	printf("size is %u\n",pq_size(pq));
	
	pq_print(pq);
	}
*/	
	

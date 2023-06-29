#include "node.h"
#include "ll.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


uint32_t seeks;
uint32_t links;

bool my_strcmp(char * op1, char * op2){
	
	if((op1 != NULL) && (op2 != NULL)){
		int len1 = 0;
		int len2 = 0;
		while (op1[len1]){
			len1++;
			}
		while (op2[len2]){
			len2++;
			}
		if (len1 != len2){
			return false;
			}
		int ind = 0;
		while(ind < len1){
			if(op1[ind] != op2[ind]){
				return false;
				}
			ind++;
			}
		return true;
		}
	return false;
	}
struct LinkedList{
	uint32_t length;
	Node *head;
	Node *tail;
	bool mtf;
	
	};

LinkedList *ll_create(bool mtf){
		//BitVector * bv = (BitVector*) malloc (sizeof(BitVector));
	LinkedList *ll = (LinkedList*)malloc(sizeof(LinkedList));
	if (ll != NULL){
		
		ll->mtf = mtf;
		//create the nodes for ll head and ll tail using node_create
		ll->head = node_create(NULL, NULL);
		ll->tail = node_create(NULL, NULL);
		ll->head->next = ll->tail;//initialize the head and tail nodes. They should point to eachother.
		ll->head->prev = NULL;
		ll->tail->next = NULL;
		ll->tail->prev = ll->head;
		seeks = 0;
		links = 0;
		}
	return ll;
	}

void ll_delete(LinkedList **ll){
	
	Node * curr = NULL;
	Node * t = NULL;
	if (*ll){
		curr = (*ll)->head;
		t = curr;
		}

	while(curr != NULL){
		t = curr;
		node_delete(&curr);

		curr = t->next;
		
		}
	(*ll) = NULL;
	return;
	}
		

uint32_t ll_length(LinkedList *ll){
	uint32_t counter = 0;
	/*while(ll->head != NULL){
		Node *next = ll->head->next;
		
		if (next != NULL){
			printf("counter is currently %u\n",counter);
			counter += 1;
			}
		ll->head = next;
	
		}
	*/
	
	for(Node * curr = ll->head; curr != NULL; curr = curr->next){
		counter ++;
		}

	counter -=2 ;
	//printf("counter is currently %u after -1\n ",counter);
	
	return counter;
	}
	
	
	

Node *ll_lookup(LinkedList *ll, char *oldspeak){
	//uint32_t orig = links;
	seeks++;
	if(ll->head != NULL){
		

		Node *curr = ll->head;
		while(curr->next != NULL){
			if(curr->next != ll->tail){
				links++;
				//printf("the value of links is %u\n",links);
			}
			curr = curr->next;
			//printf("checking %s against %s\n",oldspeak, curr->oldspeak);
			//printf("the results are %d\n",my_strcmp(curr->oldspeak, oldspeak));
			if (my_strcmp(curr->oldspeak, oldspeak) == true){
				if(ll->mtf == true){
				
					//take care of its next and previous nodes (BEFORE MOVEMENT).
					Node * t = curr-> next;
					curr->next->prev = curr->prev;//set its next's previous pointers to the previous of current.
					curr->prev->next = t;// set its previous's next equal to next.
					//set curr's nodes as its being moved to after the head's position.
					curr->next = ll->head->next;
					ll->head->next = curr;
					curr->prev = ll->head;
					curr->next->prev = curr;
					
					}
				
				

				//printf("the current linked list being transversed.\n");
				//ll_print(ll);
				//printf("num links transversed %u\n", links - orig);
				
				
				return curr;
				}
			}
		}
	return NULL;
	}
	

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak){
	//if it is not found, call NODE-CREATE and set its previous value to the head
	//this will also set its next value to first value's previous
	

	
	if (ll_lookup(ll,oldspeak) == NULL){

		Node *new = node_create(oldspeak, newspeak);
		new->next = ll->head->next;
		ll->head->next = new;
		new->prev = ll->head;
		new->next->prev = new;
		}
	}
		
	
	

void ll_print(LinkedList *ll){
	
	for(Node *c = ll->head; c != ll->tail; c = c->next){
		if (c != ll->head){
			//printf("current c being printed is %s\n", c->oldspeak);
			node_print(c);
		}
	}
}
void ll_stats(uint32_t *n_seeks, uint32_t *n_links){
	*n_seeks = seeks;
	*n_links = links;
	
	}
	
/*int main(void){
	LinkedList *l = ll_create(true);
	ll_insert(l,"bad", "old");
	ll_insert(l,"loren", "ipsum");
	ll_insert(l,"vom.", "in");
	ll_insert(l,"net", "online");
	ll_insert(l,"vom.", "in");
	ll_insert(l,"vom.", NULL); //this shall not be printed.
	ll_print(l);
	//ll_delete(l);
	}
*/

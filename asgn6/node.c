#include "node.h"
#include <stdlib.h>
#include <stdio.h>

int my_strlen(char * s){
	int length = 0;
	
	while(s[length]){
		length ++;
	}
	return length;
}



void my_strcopy(char * source, char * destination, int n){
	int i = 0; 
	for (i = 0; i < n && source[i]; i += 1){
		destination[i] = source[i];
		}
	for ( ; i < n; i ++){
		destination[i] = '\0';
		}
	return;
	}

Node *node_create(char *oldspeak, char *newspeak){

	Node * n  = (Node*)malloc(sizeof(Node));
	if (n != NULL){
		if(oldspeak != NULL){
		
			int length = my_strlen(oldspeak);
			n->oldspeak = (char *)calloc(length,sizeof(char));
			my_strcopy(oldspeak, n->oldspeak, length);
			if (newspeak != NULL){
				length = my_strlen(newspeak);
				n->newspeak = (char *)calloc(length,sizeof(char));
				my_strcopy(newspeak, n->newspeak, length);
			//n->newspeak = new_copy;
				}
			else{
				n->newspeak = NULL;
				}
			}
		if (oldspeak == NULL){
			n->oldspeak = NULL;
			n->newspeak = NULL;
			}
		
			
				
		//free(old_copy);
		//free(new_copy);
		//n->next = prev->next;
		//n->prev = next->prev;
		return n;
		}
	return NULL;
	}
	
	
void node_delete(Node **n){
	if(*n){
		if (((*n)->oldspeak)){
			free((*n)->oldspeak);	
			}
		if (((*n)->newspeak)){
			free((*n)->newspeak);
			
			}
		//Node *t = (*n)->next;
		//(*n)->next = (*n)->prev;
		//(*n)->prev = t;
		
		free(*n);
		*n = NULL;
		}
	}
		
	
	

void node_print(Node *n){
	if(n != NULL){
		if (n->newspeak == NULL){
			printf("%s\n", n->oldspeak);
			}
		else{
			printf("%s -> %s\n", n->oldspeak, n->newspeak);
			}
		}
	}	
	
	


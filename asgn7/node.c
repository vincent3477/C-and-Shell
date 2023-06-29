#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "node.h"
#include <stdio.h>


Node *node_create(uint8_t symbol, uint64_t frequency){
	Node * n  = (Node*)malloc(sizeof(Node));
	if (n != NULL){
		n->symbol = symbol;
		n->frequency = frequency;
		}
	return n;
	}

void node_delete(Node **n){
	if((*n) != NULL){
		free(*n);
		n = NULL;
		}
	}

Node *node_join(Node *left, Node *right){
	if ((left != NULL) && (right != NULL)) {
		Node * sym = NULL;
		sym = node_create(36, left->frequency + right->frequency);

		sym->left = left;
		sym->right = right;
		return sym;
		}
	return NULL;
	}
		
	

void node_print(Node *n){
	if (n){
		printf("Symbol: %c. Frequency: %lu\n", n->symbol, n->frequency);
		}
	}

bool node_cmp(Node *n, Node *m){
	if ((n != NULL) && (m != NULL)){
		if (n->frequency > m->frequency){
			return true;
			}
		return false;
		}
	return false;
	}
	

void node_print_sym(Node *n){
	if(n){
		printf("Symbol: %c\n",n->symbol);
		}
	}

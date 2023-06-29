#include "node.h"
#include "code.h"
#include "stack.h"
#include "defines.h"
#include <stdint.h>
#include "pq.h"
#include "io.h"
#include "huffman.h"
#include <stdlib.h>
#include <stdio.h>
Code c;
Node *build_tree(uint64_t hist[static ALPHABET]){
	//a histogram will consist of ALPHABET uint64_t each representing a certain character, 0- 256
	PriorityQueue * freq_queue = pq_create(ALPHABET);
	Node * n = NULL;
	int iterator = 0;
	while(iterator < 256){
		if (hist[iterator] != 0){
			n = node_create(iterator, hist[iterator]);
			enqueue(freq_queue,n);
			}
		iterator++;
		}
	
		
	Node *d1=NULL;
	Node *d2=NULL;
	Node * j = NULL;
	Node * root = NULL;
	while(pq_size(freq_queue) > 1){
		dequeue(freq_queue,&d1);
		dequeue(freq_queue,&d2);
		j = node_join(d1,d2);
		enqueue(freq_queue,j);
		}
	
	dequeue(freq_queue, &root);
	
	return root;
	}
		
		
		

void build_codes(Node *root, Code table[static ALPHABET]){
	
	uint8_t popped = 0;

	if(root){
		if(!(root->left) && !(root->right)){
		//This is the base case where we have reached to the leaf and that there are NO MORE CHILDREN.
			table[root->symbol]=c;
			
			
			}
		else{
			code_push_bit(&c,0);
			build_codes(root->left,table);
			code_pop_bit(&c,&popped);

			code_push_bit(&c,1);
			build_codes(root->right,table);
			code_pop_bit(&c,&popped);
			}
		}
	
	}
void dump_tree(int outfile, Node *root){

	uint8_t upper_l = 76;
	uint8_t upper_i = 73;
	
	

	if(root ){
		
		
		dump_tree(outfile, root->left);
		dump_tree(outfile, root->right);
		if(!(root->left) && !(root->right)){						
			write_bytes(outfile, &upper_l, 1);
			write_bytes(outfile, &root->symbol, 1);
			
			}
		else{
			write_bytes(outfile,&upper_i,1);
			
			}
		}
	
	}
			

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]){
	Stack * s = stack_create(nbytes);
	Node * right = NULL;
	Node * left = NULL;
	Node * j = NULL;
	Node * root = NULL;
	
	
	
	
	
	/*for(uint16_t i = 0 ; i < nbytes; i++){
		if (tree[i] == 76){
			if(i > 0){
				if(tree[i-1] != 76){	
					Node * sym = node_create(tree[i+1], 0);
					stack_push(s, sym);
					}
				}
			else{
				Node * sym = node_create(tree[i+1], 0);
				stack_push(s, sym);
				}
				
			}
		else if(tree[i] == 73){
			stack_pop(s, &right);
			stack_pop(s, &left);
	
			j = node_join(left, right);
			stack_push(s, j);
			}
		//printf("begin stack print\n");
		//stack_print(s);
		//printf("done stack print\n\n");
		
		}
		
	*/
	uint16_t iter = 0;
	while(iter < nbytes){
		if (tree[iter] == 76){
			Node * sym = node_create(tree[iter+1], 0);
			stack_push(s, sym);
			iter+=2;
			}
		else if(tree[iter] == 73){
			stack_pop(s, &right);
			stack_pop(s, &left);
	
			j = node_join(left, right);
			stack_push(s, j);
			iter++;
			}
		}
		

	stack_pop(s,&root);
	return root;
	}
		
		
		

void delete_tree(Node **root){
	if(*root){
		delete_tree(&(*root)->left);
		delete_tree(&(*root)->right);
		node_delete(root);
		}
	}

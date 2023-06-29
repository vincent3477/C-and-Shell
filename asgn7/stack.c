#include "node.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "stack.h"
#include <stdio.h>

struct Stack{
	uint32_t capacity;
	uint32_t top;
	Node ** nodes;
	};

Stack *stack_create(uint32_t capacity){
	Stack * s = (Stack*)malloc(sizeof(Stack));
	if(s){
		s->top = 0;
		s->capacity = capacity;
		s->nodes = (Node **)calloc(capacity,sizeof(Node*));
		if (!s->nodes){
			free(s);
			s = NULL;
			}
		return s;
		}
	return NULL;
	}
		
		

void stack_delete(Stack **s){
	if(*s){
		if((*s)->nodes){
			for(uint32_t i = 0; i < (*s)->capacity; i ++){
				node_delete(&(*s)->nodes[i]);
				}
			free((*s)->nodes);
			(*s)->nodes = NULL;
			}
		free(*s);
		*s = NULL;
		}
	}
	

bool stack_empty(Stack *s){
	if(s){
		if (s->top > 0){
			return false;
			}
		return true;
		}
	return true;
	}

bool stack_full(Stack *s){
	if(s){
		if(s->top == s->capacity){
			return true;
			}
		return false;
		}
	return false;
	}

uint32_t stack_size(Stack *s){
	if(s){
		return s->top;
		}
	return 0;
	}

bool stack_push(Stack *s, Node *n){
	if(s){
		if(!stack_full(s)){
			
			s->nodes[s->top] = n;
			s->top++;
			return true;
			}
		}
	return false;
	}

bool stack_pop(Stack *s, Node **n){
	if(s){
		if(!stack_empty(s)){
			(*n) = s->nodes[s->top-1];

			s->top -=1;
			return true;
			}
		}
	return false;
	}
	

void stack_print(Stack *s){
	if (s){
		for(uint32_t i = 0; i < s->top; i++){
			node_print(s->nodes[i]);

			}
		}
	}

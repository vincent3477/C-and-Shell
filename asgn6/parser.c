
#include "parser.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PARSER_LINE_LENGTH 1000

bool my_charcmp(char * op1, char op2, uint32_t i){
	if(op1[i] == op2){
		return true;
		}
	return false;
	}
	
struct Parser{
	FILE *f;
	char current_line[MAX_PARSER_LINE_LENGTH + 1];
	uint32_t line_offset;
	};

Parser *parser_create(FILE *f){
	Parser *p = (Parser*)malloc(sizeof(Parser));
	if(p == NULL){
		free(p);
		p = NULL;
		return NULL;
		}
	p->f = f;
	p->line_offset = 0;
	return p;
	}
	

void parser_delete(Parser **p){
	if(*p){
		free(*p);
		*p = NULL;
		}
	}
bool next_word(Parser *p, char *word){

	







	int i = 0;
	if (p->line_offset == 0){
		i = 0; 
		while (word[i] && (i < 1000)){
			p->current_line[i] = tolower(word[i]); 
			i++;
			}
		}
	bool found = false;
	



	
	//if this returns true, call next_word again, do not call fgets.
	//if this returns false, we may call fgets to get the next line and reset the offset.
	
	char d = '-';
	char a = '\'';

	i = 0; //
	while(p->current_line[p->line_offset]){
		//printf(" what is being checked right now %c\n", p->current_line[p->line_offset]);
		//printf("the current offset is %u\n", p->line_offset);
		if(isalnum(p->current_line[p->line_offset]) || my_charcmp(p->current_line, d,p->line_offset) || my_charcmp(p->current_line, a,p->line_offset)){
			found = true;
			
			word[i] = p->current_line[p->line_offset]; 
			i++;
			}
		else if((isalnum(p->current_line[p->line_offset])==false) && (found == true)){
			break;
			}
		p->line_offset++;
		}
	
	word[i] = '\0';	
	
	
	if(found == 0 && !(p->current_line[p->line_offset])){
		p->line_offset = 0; //reset if we have come to null.
		for(uint32_t i = 0; i < 1000; i ++){
			p->current_line[i]='\0'; 
			}
		return false;
		}

	
	

	return found;
	}
	
/*int main(void){
	FILE *f = fopen("newspeak.txt","r");
	Parser *p = parser_create(f);
	char * word = (char*)malloc(1000*sizeof(char));
	if(!feof(f)){
		fgets(word, 1000, f);
		}
	while(!feof(f)){
		while(next_word(p,word) == true){
			printf("%s\n", word);  
			}
		fgets(word,1000,f);
		}
	}
		 
*/	
			
			
			
				
			
		
	



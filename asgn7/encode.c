#include "huffman.h"
#include "io.h"
#include "node.h"
#include <stdlib.h>
#include <unistd.h>
#include "defines.h"
#include "header.h"
#include "stdint.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <inttypes.h>
#include <ctype.h>

#define OPTIONS "hi:o:v"


//IMPORTANT NOTICE: THE CODE TO PRINT TREE (LINES 20-38) IS FROM Athanasius Kircher#1515 ON THE CSE13S FALL-2022 DISCORD.
void printTree(Node *t, int depth) {
    if (t) {															
        printTree(t->left, depth + 1);										
        for(int i = 0; i < (depth * 4); i ++){
        	fprintf(stderr," ");
        	}
        if (!(t->left) && !(t->right)) {
            if (isgraph(t->symbol)) {
                fprintf(stderr, "'%c' (%" PRIu64 ")\n", t->symbol, t->frequency);
            } else {
                fprintf(stderr, "0x%02X (%" PRIu64 ")\n", t->symbol, t->frequency);
            }
        } else {
            fprintf(stderr, "$ (%" PRIu64 ")\n", t->frequency);
        }
        printTree(t->right, depth + 1);
    }
    return;
}
//##########################################################################################################################





int main(int argc, char **argv){
	char * infile = NULL;
	char * outfile = NULL;
	int print_stats = false;
	int infile_desc = 0;
	int outfile_desc = 0;
	int opt = 0;
	int tmp_file = 0;
	while((opt = getopt(argc, argv, OPTIONS))!=-1){
		switch(opt){
			case 'h':
				printf("SYNOPSIS\n"
  					"  A Huffman encoder.\n"
  					"  Compresses a file using the Huffman coding algorithm.\n"

					"USAGE\n"
  					   "./encode [-h] [-i infile] [-o outfile]\n"

					"OPTIONS\n"
  					"  -h             Program usage and help.\n"
  					"  -v             Print compression statistics.\n"
  					"  -i infile      Input file to compress.\n"
  					"  -o outfile     Output of compressed data.\n");
  				return 0;
  			case 'i':
  				infile = optarg;
  				printf("fault here?\n");
  				break;
  			case 'o':
  				outfile = optarg;
  				break;
  			case 'v':
  				print_stats = true;
  				break;
  			default:
				fprintf(stderr,"SYNOPSIS\n"
  					"  A Huffman encoder.\n"
  					"  Compresses a file using the Huffman coding algorithm.\n\n"

					"USAGE\n"
  					"  ./encode [-h] [-i infile] [-o outfile]\n\n"
  					                                          
					"OPTIONS\n"
  					"  -h             Program usage and help.\n"
  					"  -v             Print compression statistics.\n"
  					"  -i infile      Input file to compress.\n"
  					"  -o outfile     Output of compressed data.\n");
  				return 1;
  			}
  		}

  		
  	//open any files if there were specified, otherwise we can read directly from stdin
  	if(infile != NULL){
  		infile_desc = open(infile, O_RDONLY);
  		}
  	else{
  		tmp_file = open("tmp.txt",O_CREAT|O_RDWR|O_TRUNC);
  		
  		}
  		
  	if(outfile != NULL){
  		outfile_desc = open(outfile, O_CREAT|O_WRONLY|O_TRUNC);
  		}
  	

  	//make a histogram and initialze it.	
  	uint64_t histogram[ALPHABET];
  	int i = 0;
  	while(i < ALPHABET){
  		histogram[i] = 0;
  		i++;
  		}
  		
  		
  	//read the infile
  	uint8_t num_read_bytes[8192];
  	while(i < 8192){
  		num_read_bytes[i] = 0;
 
  		i++;
  		}
  	uint64_t bytes_to_encode = 0;	
  	while(read_bytes(infile_desc, num_read_bytes, 8192) != 0){
		bytes_to_encode += bytes_read;

 		if(infile == NULL){
 			write_bytes(tmp_file, num_read_bytes, bytes_to_encode+1);
 			infile = "tmp.txt";
 			}	
  		for(int i = 0; i < ALPHABET; i++){
  			for(int j = 0; j < 8192;j++){
  				if (i == num_read_bytes[j]){
  					histogram[i] += 1;
  					}
  				if(num_read_bytes[j] == 0){
  					break;
  					}
  				}

  			}
  		while(i < 8192){
  			num_read_bytes[i] = 0;
  			}
  		}

  	
  	if(tmp_file != 0){
  		infile_desc = tmp_file;
  		}



  	int num_symbols = 0;
  	for(int i = 0 ; i < ALPHABET; i++){
  		
  		if (histogram[i] != 0){

  			num_symbols ++;
  			}
  		}
  		
  	
  		
  		
  		
  	if(histogram[0]==0){
  		histogram[0] = 1;
  		num_symbols ++;
  		}
  	if(histogram[1]==0){
  		histogram[1] = 1;
  		num_symbols ++;
  		}
	/*printf("num_symbols %d\n",num_symbols);
	for(int i = 0 ; i < 256; i ++){
		printf("i is %d num %lu\n",i,histogram[i]);
		}
  	*/
	Node * new_tree = build_tree(histogram);
	//Node * nt_copy =  node_create(new_tree->symbol, new_tree->frequency);
	//nt_copy->left = new_tree->left;
	//nt_copy->right = new_tree->right;
	
	//int depth = 0;
	
	//Code table[ALPHABET];
	//build_codes(nt_copy, &table);
	
		
	struct stat statf;
	if(infile != NULL){
		fstat(infile_desc, &statf);
		}
	else{
		fstat(tmp_file, &statf);
		}

	Header h;
	(&h)->permissions = (&statf)->st_mode;	
	(&h)->file_size = (&statf)->st_size;
	(&h)->magic = MAGIC;
	(&h)->tree_size = ((3 * num_symbols) -1);
	fchmod(outfile_desc, (&h)->permissions);

	write_bytes(outfile_desc, (uint8_t*)&h, sizeof(h));
	//write(outfile_desc, (uint8_t*)&h, sizeof(h));
	
	
	//printTree(new_tree,5);
	
	
	
	dump_tree(outfile_desc, new_tree); //dump the contents of the tree and write to outfile.
	Code table[ALPHABET];
	for(int i = 0; i < ALPHABET;i++){
		table[i] = code_init();

		}
	//code init is done for safety purposes.
	build_codes(new_tree, table);
	
	

	//write_code(outfile_desc, &table[1]);

  	//while(i < 20){
  	//	num_read_bytes[i] = 0;
  	//	i++;
  	//	}
  		
  		


  	Code lcodes[bytes_to_encode+10];
 
	
	lseek(infile_desc,0,SEEK_SET);
		

	int iter1 = 0;
	while(read_bytes(infile_desc, num_read_bytes, 8192) != 0){
		
		for(int i = 0 ; i < 8192; i++){
			for(int j = 0; j < ALPHABET;j++){
				if(code_size(&table[j])!=0 && num_read_bytes[i] == j){

					lcodes[iter1] = code_init();			
					lcodes[iter1] = table[j];
						
					//code_print(&lcodes[iter1]);
					//printf("\n");
					iter1++;
						
						
						

					}
				
				}
				if(num_read_bytes[i] == 0){
						break;
				
				}
				
			}
			
			
			
			
		}
			
			
	bytes_read = bytes_to_encode;
	write_code(outfile_desc, lcodes);
	flush_codes(outfile_desc);
		
		
	
	
  	

	//flush_codes(outfile_desc);				
	
	
	//write_code(outfile_desc, &table[0]);
	
	if(print_stats == true){
		printf("something\n");
		}
	
	if(infile != NULL){
  		close(infile_desc);
  		}

  	if(outfile != NULL){
  		close(outfile_desc);
  		}
  	return 0;
  	}
	
	
	
  	

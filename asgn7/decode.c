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
	int tmp_file = 0;
	int opt = 0;
	int isstdin = 0;
	while((opt = getopt(argc, argv, OPTIONS))!=-1){
		switch(opt){
			case 'h':
				printf("SYNOPSIS\n"
  					"  A Huffman decoder.\n"
  					"  Decompresses a file using the Huffman coding algorithm.\n\n"

					"USAGE\n"
  					"  ./decode [-h] [-i infile] [-o outfile]\n\n"

					"OPTIONS\n"
  					"  -h             Program usage and help.\n"
  					"  -v             Print compression statistics.\n"
  					"  -i infile      Input file to decompress.\n"
  					"  -o outfile     Output of decompressed data.\n");
  				return 0;
  			case 'i':
  				infile = optarg;
  				break;
  			case 'o':
  				outfile = optarg;
  				break;
  			case 'v':
  				print_stats = true;
  				break;
  			default:
				fprintf(stderr,"SYNOPSIS\n"
  					"  A Huffman decoder.\n"
  					"  Decompresses a file using the Huffman coding algorithm.\n\n"

					"USAGE\n"
  					"  ./decode [-h] [-i infile] [-o outfile]\n\n"

					"OPTIONS\n"
  					"  -h             Program usage and help.\n"
  					"  -v             Print compression statistics.\n"
  					"  -i infile      Input file to decompress.\n"
  					"  -o outfile     Output of decompressed data.\n");
  				return 1;
  			}
  		}
  	
  	//open any files if there were specified, otherwise we can read directly from stdin
  	uint8_t num_read_bytes[4096];
  	
  	if(infile != NULL){
  		infile_desc = open(infile, O_RDONLY);
  		}
  	else{
  		tmp_file = open("temp.txt",O_CREAT|O_RDWR|O_TRUNC); //CITE THIS LINE OF CODE from IBM
  		infile = "temp.txt";
  		isstdin = 1;
  		}
  		
  	if(outfile != NULL){
  		outfile_desc = open(outfile, O_WRONLY|O_CREAT|O_TRUNC);
  		}
  		
  		
  	if(isstdin == 1){	
  		while(read_bytes(infile_desc, num_read_bytes, 4096) != 0){
 
 			write_bytes(tmp_file, num_read_bytes, 4096);
 			}
 		}
	
 		
 	struct stat statf;
	if(!isstdin){
		fstat(infile_desc, &statf);
		}
	else{
		fstat(tmp_file, &statf);
		
		}
		
	Header h;
	
		
	read_bytes(infile_desc, (uint8_t*)&h, sizeof(h));	
	(&h)->permissions = (&statf)->st_mode;	
	uint64_t infile_size = (&statf)->st_size;
	fchmod(outfile_desc, (&h)->permissions);
 

 	
 	if((&h)->magic != MAGIC){
 		printf("Invalid magic number.\n");
 		return 1;
 		}

 	
 	
 	
 	uint16_t tree_size = (&h)->tree_size;
 	
 	uint8_t * dumped_tree = (uint8_t*)malloc(tree_size * sizeof(uint8_t));
 	

 	
 	read_bytes(infile_desc, dumped_tree, tree_size);

 	

 	
 	Node * recon = rebuild_tree(tree_size, dumped_tree);
 	//printTree(recon, 0);
 	Node * ref = recon;
 	uint8_t root = 37;
 	ref->symbol = root;
 	uint8_t bit = 0;
 	

 	
 	
	uint64_t wr = 0;
 	while (read_bit(infile_desc, &bit)==1 && wr < (&h)->file_size){
		
 		
 		//fprintf(stderr,"%hx",bit);
		//node_print(recon);
 		if(bit == 0){
 			
 			recon = recon->left;

 			if (!(recon->left) && !(recon->right)){
 				write_bytes(outfile_desc,&recon->symbol,1);
 				//node_print(recon);
 				wr+=1;
 				recon = ref;
 				
 			//	printf("we are at bit %d",bitpos);
 				//printf("leaf \n");
 				}
 			}
 		else if(bit == 1){
 			recon = recon->right;
 			if (!(recon->left) && !(recon->right)){
 				write_bytes(outfile_desc,&recon->symbol,1);
 				//node_print(recon);
 				recon = ref;
 				wr+=1;
 			//	printf("we are at bit %d",bitpos);
 				//printf("leaf \n");
 				}
 			}
 		

 		}
 	if(print_stats){
 		double savings = ((double)infile_size) / (double)wr;
 		savings *= 100;
 		double percentage = 100 - savings;
 		fprintf(stderr,"Compressed file size: %lu bytes\n",wr);
 		fprintf(stderr,"Decompressed file size: %lu bytes\n",infile_size);
 		fprintf(stderr,"Space saving: %3.2f%%\n",percentage);
 		
 		}

 	close(outfile_desc);
 	close(infile_desc);
 	
 	
  	}
  		

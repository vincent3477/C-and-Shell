#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <unistd.h>
#include "rsa.h"
#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv){
	int v_out = 0;
	char * infilename = NULL;
	char * outfilename = NULL;
	char * privkeyfilename = "rsa.priv";
	int opt = 0;
	while((opt = getopt(argc, argv, OPTIONS))!=-1){
		switch(opt){
			case 'i':
				infilename = optarg;
				break;
			case 'o':
				outfilename = optarg;
				break;
			case 'n':
				privkeyfilename = optarg;
				break;
			case 'v':
				v_out = 1;
				break;
			case 'h':
				fprintf(stderr,"Usage: ./decrypt [options]\n"
  "  ./decrypt decrypts an input file using the specified private key file,\n"
  "  writing the result to the specified output file.\n"
  "    -i <infile> : Read input from <infile>. Default: standard input.\n"
  "    -o <outfile>: Write output to <outfile>. Default: standard output.\n"
  "    -n <keyfile>: Private key is in <keyfile>. Default: rsa.priv.\n"
  "    -v          : Enable verbose output.\n"
  "    -h          : Display program synopsis and usage.\n");
				return 0;
				break;
			default:
				fprintf(stderr,"Usage: ./decrypt [options]\n"
  "  ./decrypt decrypts an input file using the specified private key file,\n"
  "  writing the result to the specified output file.\n"
  "    -i <infile> : Read input from <infile>. Default: standard input.\n"
  "    -o <outfile>: Write output to <outfile>. Default: standard output.\n"
  "    -n <keyfile>: Private key is in <keyfile>. Default: rsa.priv.\n"
  "    -v          : Enable verbose output.\n"
  "    -h          : Display program synopsis and usage.");
  				
				return 1;
				
			}
		}
	
	if(fopen(privkeyfilename, "r") == NULL){
		fprintf(stderr,"./decrypt: couldn't open %s to read private key.\n",privkeyfilename);
		fprintf(stderr,"Usage: ./decrypt [options]\n"
  "  ./decrypt decrypts an input file using the specified private key file,\n"
  "  writing the result to the specified output file.\n"
  "    -i <infile> : Read input from <infile>. Default: standard input.\n"
  "    -o <outfile>: Write output to <outfile>. Default: standard output.\n"
  "    -n <keyfile>: Private key is in <keyfile>. Default: rsa.priv.\n"
  "    -v          : Enable verbose output.\n"
  "    -h          : Display program synopsis and usage.\n");
  		return 1;
  		}
  	FILE * infile = stdin;
  	FILE * outfile = stdout;
	
	FILE *privkeyfile = fopen(privkeyfilename, "r");
	mpz_t n,d;
	mpz_inits(n,d,NULL);
	
	
	rsa_read_priv(n,d,privkeyfile);
	
	if (v_out == 1){
  		
  		
  		size_t d_size = mpz_sizeinbase(d, 2);
  		size_t n_size = mpz_sizeinbase(n, 2);
  		

  		gmp_fprintf(stderr, "n - modulus (%d bits): %Zd\n",n_size,n);
  		gmp_fprintf(stderr, "d - private exponent (%d bits): %Zd\n",d_size,d);
  		}
  		
  		
	if (infilename == NULL){
		infile = stdin;
		}
	else{
		if(fopen(infilename, "r") == NULL){
			fprintf(stderr,"./decrypt: couldn't open %s to read read plaintext: No such file or directory\n",infilename);
			return 1;
  			}

		infile = fopen(infilename, "r");
		}
		
		
	if (outfilename == NULL){
		outfile = stdout;
		}
	else{
		outfile = fopen(outfilename, "w");
		}
	 
	
	rsa_decrypt_file(infile, outfile, n, d);
	
	fclose(infile);
	fclose(outfile);
	fclose(privkeyfile);

	mpz_clears(n,d,NULL);
	}

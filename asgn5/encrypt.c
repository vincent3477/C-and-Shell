#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <unistd.h>
#include "rsa.h"
#define OPTIONS "i:o:n:vh"
#include "randstate.h"


int main(int argc, char **argv){
	int v_out = 0;
	char * infilename = NULL;
	char * outfilename = NULL;
	char * pubkeyfilename = "rsa.pub";
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
				pubkeyfilename = optarg;
				break;
			case 'v':
				v_out = 1;
				break;
			case 'h':
				fprintf(stderr,"Usage: ./encrypt [options]\n"
  "  ./encrypt encrypts an input file using the specified public key file,\n"
  "  writing the result to the specified output file.\n"
  "    -i <infile> : Read input from <infile>. Default: standard input.\n"
  "    -o <outfile>: Write output to <outfile>. Default: standard output.\n"
  "    -n <keyfile>: Public key is in <keyfile>. Default: rsa.pub.\n"
  "    -v          : Enable verbose output.\n"
  "    -h          : Display program synopsis and usage.\n");
				return 0;
				break;
			default:
				fprintf(stderr,"Usage: ./encrypt [options]\n"
  "  ./encrypt encrypts an input file using the specified public key file,\n"
  "  writing the result to the specified output file.\n"
  "    -i <infile> : Read input from <infile>. Default: standard input.\n"
  "    -o <outfile>: Write output to <outfile>. Default: standard output.\n"
  "    -n <keyfile>: Public key is in <keyfile>. Default: rsa.pub.\n"
  "    -v          : Enable verbose output.\n"
  "    -h          : Display program synopsis and usage.\n");
  				
				return 1;
			}
		}
	
	mpz_t n,e,s,u;
	mpz_inits(n,e,s,u,NULL);
	char * username = "";
	
	if(fopen(pubkeyfilename, "r") == NULL){
		fprintf(stderr,"./encrypt: couldn't open %s to read public key.\n",pubkeyfilename);
		fprintf(stderr,"Usage: ./encrypt [options]\n"
  "  ./encrypt encrypts an input file using the specified public key file,\n"
  "  writing the result to the specified output file.\n"
  "    -i <infile> : Read input from <infile>. Default: standard input.\n"
  "    -o <outfile>: Write output to <outfile>. Default: standard output.\n"
  "    -n <keyfile>: Public key is in <keyfile>. Default: rsa.pub.\n"
  "    -v          : Enable verbose output.\n"
  "    -h          : Display program synopsis and usage.\n");
  		return 1;
  		}
	
	FILE * pbfile = fopen(pubkeyfilename, "r");
	
	rsa_read_pub(n,e,s,username,pbfile);
	
	FILE* infile = stdin;
	FILE * outfile = stdout;
	
	username = getenv("USER");
  	(void)mpz_set_str(u, username,62);

	
	if (v_out == 1){
  		
  		
  		size_t s_size = mpz_sizeinbase(s, 2);
  		size_t e_size = mpz_sizeinbase(e, 2);
  		size_t n_size = mpz_sizeinbase(n, 2);
  		
  		fprintf(stderr, "username: %s\n",username);
  		gmp_fprintf(stderr, "user signature (%d bits): %Zd\n",s_size,s);
  		gmp_fprintf(stderr, "n - modulus (%d bits): %Zd\n",n_size,n);
  		gmp_fprintf(stderr, "e - public exponent (%d bits): %Zd\n",e_size,e);

  		}
		
	if (infilename == NULL){
		infile = stdin;
		}
	else{
		if(fopen(infilename, "r") == NULL){
			fprintf(stderr,"./encrypt: couldn't open %s to read read plaintext: No such file or directory\n",infilename);
			
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
	
	if (!rsa_verify(u, s, e, n)){
		fprintf(stderr,"Unable to verify signature. Exiting now.\n");
		return 1;
		}

	
	rsa_encrypt_file(infile, outfile, n, e);
	
	fclose(infile);
	fclose(outfile);
	fclose(pbfile);

	mpz_clears(n,e,s,u,NULL);
	}
	

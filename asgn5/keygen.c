
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "rsa.h"
#include <time.h>
#include "randstate.h"
#include <sys/stat.h>
#include <gmp.h>

#define OPTIONS "b:i:n:d:s:vh"

int main(int argc, char **argv){
	

	uint64_t nbits = 1024;
	uint64_t iters = 50;
	char * pubkeyfilename = "rsa.pub";
	char * privkeyfilename = "rsa.priv";
	uint64_t seed = time(NULL); //what is this?
	int v_out = 0;
	int opt = 0;
	

	
	while((opt = getopt(argc, argv, OPTIONS))!=-1){
		switch(opt){
			case 'b': //specifies the number of bits needed
				nbits = strtoul(optarg,NULL, 10);
				break;
			case 'i': //specifies the number of miller rabin iterations
				iters = strtoul(optarg,NULL,10);
				break;
			case 'n': //specifies the pub key file.
				pubkeyfilename = optarg;
				break;
			case 'd': //specifies the priv key file
				privkeyfilename = optarg;
				break;
			case 's': //specifies the seed
				seed = strtoul(optarg,NULL,10);
				break;
			case 'v'://enable verbose output
				v_out = 1;
				break;
			case 'h': //print help.
				printf("Usage: ./keygen [options]\n"
  "  ./keygen generates a public / private key pair, placing the keys into the public and private key files as specified below. The keys have a modulus (n) whose length is specified in the program options.\n"
  "    -s <seed>   : Use <seed> as the random number seed. Default: time()\n"
  "    -b <bits>   : Public modulus n must have at least <bits> bits. Default: 1024\n"
  "    -i <iters>  : Run <iters> Miller-Rabin iterations for primality testing. Default: 50\n"
  "    -n <pbfile> : Public key file is <pbfile>. Default: rsa.pub\n"
  "    -d <pvfile> : Private key file is <pvfile>. Default: rsa.priv\n"
  "    -v          : Enable verbose output.\n"
  "    -h          : Display program synopsis and usage.\n");
  				
  				return 0;
  				break;
  			default:
  				printf("Usage: ./keygen [options]\n"
  "  ./keygen generates a public / private key pair, placing the keys into the public and private\n"
  "  key files as specified below. The keys have a modulus (n) whose length is specified in\n"
  "  the program options.\n"
  "    -s <seed>   : Use <seed> as the random number seed. Default: time()\n"
  "    -b <bits>   : Public modulus n must have at least <bits> bits. Default: 1024\n"
  "    -i <iters>  : Run <iters> Miller-Rabin iterations for primality testing. Default: 50\n"
  "    -n <pbfile> : Public key file is <pbfile>. Default: rsa.pub\n"
  "    -d <pvfile> : Private key file is <pvfile>. Default: rsa.priv\n"
  "    -v          : Enable verbose output.\n"
  "    -h          : Display program synopsis and usage.\n");
  				break;
  			}
  		}

  	
  	randstate_init(seed);

  		
  	
  
  	mpz_t p,q,n,e,d,u,s;
  	mpz_inits(p,q,n,e,d,u,s,NULL);
  	

  	//mpz_set_ui(n,nbits);
  	//open file first
  	FILE * pubkey = fopen(pubkeyfilename,"w");
  	FILE * privkey = fopen(privkeyfilename,"w");
  	
  	int file_specs = fileno(privkey);
  	fchmod(file_specs, 0600);
  	
  	rsa_make_pub(p,q,n,e,nbits,iters);
  	
  	rsa_make_priv(d,e,p,q);
  	
  	//gmp_printf("d is after private %Zd\n",d);
  	
  	char * username = getenv("USER");
  	(void)mpz_set_str(u, username,62);

  	rsa_sign(s,u,d,n);

  	rsa_write_pub(n,e,s,username,pubkey);
  	
  	rsa_write_priv(n,d,privkey);

  	if (v_out == 1){
  		
  		
  		size_t s_size = mpz_sizeinbase(s, 2);
  		size_t p_size = mpz_sizeinbase(p, 2);
  		size_t q_size = mpz_sizeinbase(q, 2);
  		size_t e_size = mpz_sizeinbase(e, 2);
  		size_t d_size = mpz_sizeinbase(d, 2);
  		size_t n_size = mpz_sizeinbase(n, 2);
  		
  		fprintf(stderr, "username: %s\n",username);
  		gmp_fprintf(stderr, "user signature (%d bits): %Zd\n",s_size,s);
  		gmp_fprintf(stderr, "p (%d bits): %Zd\n",p_size,p);
  		gmp_fprintf(stderr, "q (%d bits): %Zd\n",q_size,q);
  		gmp_fprintf(stderr, "n - modulus (%d bits): %Zd\n",n_size,n);
  		gmp_fprintf(stderr, "e - public exponent (%d bits): %Zd\n",e_size,e);
  		gmp_fprintf(stderr, "d - private exponent (%d bits): %Zd\n",d_size,d);
  		}
  	
  	fclose(pubkey);
  	fclose(privkey);
  	mpz_clears(p,q,n,e,d,u,NULL);
  	}
  	

						

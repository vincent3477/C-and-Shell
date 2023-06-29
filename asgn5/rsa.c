#include "rsa.h"
#include <stdlib.h>
#include "numtheory.h"
#include "randstate.h"
#include <stdio.h>
#include <gmp.h>

// Generates the components for a new public RSA key.
// p and q will be large primes with n their product.
// The product n will be of a specified minimum number of bits.
// The primality is tested using Miller-Rabin.
// The public exponent e will have around the same number of bits as n.
// All mpz_t arguments are expected to be initialized.
//
// p: will store the first large prime.
// q: will store the second large prime.
// n: will store the product of p and q.
// e: will store the public exponent.
//
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters){
	//p = prime, q = prime, n = product of p and q, e = public exponent, nbits = number of bits, iters = number of miller rabin iterations to run.
	uint64_t n_bits = (random() % ((3 * nbits/4)+1));
	while (n_bits < (nbits/4)){
		n_bits = (random() % ((3 * nbits/4)+1));
		}
	uint64_t p_bits = nbits - n_bits;
	make_prime(p, n_bits, iters);
	make_prime(q, p_bits, iters);
	mpz_t p_copy;
	mpz_t q_copy;
	mpz_t temp;
	mpz_init(temp);
	mpz_init(p_copy);
	mpz_init(q_copy);
	mpz_sub_ui(p_copy, p, 1); //p_copy = p-1
	mpz_sub_ui(q_copy, q, 1); //q_copy = q-1
	mpz_t lambda_n;
	mpz_init(lambda_n);
	
	gcd(lambda_n, p, q);
	mpz_mul(temp, p_copy, q_copy);
	mpz_div(lambda_n, temp, lambda_n);
	mpz_clear(p_copy);
	mpz_clear(q_copy);
	mpz_t gcd_result;
	mpz_init (gcd_result);
	mpz_mul(n,p,q);
	
	while (1){
		mpz_urandomb(temp, state, nbits);
		gcd(gcd_result, temp, lambda_n);
		if (mpz_cmp_ui(gcd_result, 1) == 0){
			mpz_set(e, temp);
			break;
			}
		}
	}
	
// Writes a public RSA key to a file.
// Public key contents: n, e, signature, username.
// All mpz_t arguments are expected to be initialized.
//
// n: the public modulus.
// e: the public exponent.
// s: the signature of the username.
// username: the username that was signed as s.
//
void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile){
	//FILE *file;
	//file = fopen(pbfile, "w");
	(void)gmp_fprintf(pbfile, "%Zx\n%Zx\n%Zx\n%s",n,e,s,username);

	}
	
	
	
void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile){
	//FILE *file;
	//file = fopen(pbfile,"r");
	(void)gmp_fscanf(pbfile,"%Zx\n%Zx\n%Zx\n%s",n,e,s,&username);

	}
	
void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q){
	//d = the new key to be made, e = public exponent, p & q are primes given.
	mpz_t pdif1,qdif1,prod;
	mpz_inits(pdif1,qdif1,prod, NULL);
	mpz_sub_ui(pdif1,p,1);
	mpz_sub_ui(qdif1,q,1);
	gcd(d, pdif1, qdif1);//compute (a*b)/d
	mpz_mul(prod,pdif1,qdif1);
	mpz_fdiv_q(d,prod,d);
	
	mod_inverse(d, e, d);

	mpz_clears(pdif1,qdif1,prod, NULL);
	}
	
void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile){
	//FILE *file;
	//file = fopen(pvfile,"w");
	gmp_fprintf(pvfile, "%Zx\n%Zx\n",n,d);

	}
	
void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile){
	// n: will store the public modulus.
	// d: will store the private key. n & d are the private key contents.
	gmp_fscanf(pvfile, "%Zx\n%Zx\n",n,d);

	}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n){
	//c = cipher_text, m = message to encrypt, e = public exponent, n = modulus.
	pow_mod(c,m,e,n);
	}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e){
	mpz_t m;
	mpz_init(m);
	
	size_t log2n = mpz_sizeinbase(n,2);
	log2n = ((log2n-1)/8);
	uint8_t *blocks = (uint8_t*)malloc(log2n*sizeof(uint8_t));
	blocks[0] = 0xFF;
	size_t j = 0;

	
	while(!feof(infile)){
		

		j = fread(blocks+1, 1, log2n-1, infile);//blocks+1 specifies the pointer to the block of memory. This will add stuff to the block of memory from what is read in the file.
			
		mpz_import(m,j+1, 1, sizeof(uint8_t), 1,0,blocks); //get everything from the block and import all of these to convert data of type mpz, therefore represented as m.
		
		rsa_encrypt(m,m,e,n);  //encrypt the message m.
			
		gmp_fprintf(outfile, "%Zx\n",m);
		
		}
	mpz_clear(m);
	free(blocks);

		
		

		
	}
void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n){
	//computes message m by decrypting ciphertext c. private key is d and n is modulo.
	pow_mod(m,c,d,n);
	}
		
void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d){
	mpz_t l,m;
	mpz_inits(l,m,NULL);

	size_t log2n = mpz_sizeinbase(n,2);
	log2n = ((log2n-1)/8);

	uint8_t *blocks = (uint8_t*)malloc(log2n*sizeof(uint8_t));
	size_t countp;
	//size_t j = 0;
	
	
	
	while (!feof(infile)){
		gmp_fscanf(infile, "%Zx\n", l); //scan the file
		//gmp_printf("%Zd\n",l);
		rsa_decrypt(m,l,d,n); //convert to bytes
		//gmp_printf("message m: %Zd\n",m);
		//we want to turn this mpz value, l, back in to an array, the opposite of what we did in encrypt.
		//j = &blocks;
		mpz_export(blocks, &countp,1, sizeof(uint8_t), 1,0,m); 
		//printf("what hapenns RIGHT AFTER EXPORT, where countp is equal %zu\n\n",countp);
		//for (size_t i = 0; i <= countp; i++){
		//	printf("i is at %zu this block of memory contains: %c \n",i,blocks[i]);
		//	}
		//j+=countp;
		
		fwrite(blocks+1, sizeof(uint8_t), countp-1, outfile);

		}
	mpz_clears(l,m,NULL);
	free(blocks);
	
	
	}
		
		
		
void rsa_sign(mpz_t s, mpz_t m, mpz_t d,mpz_t n){
	pow_mod(s,m,d,n);
	}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n){
	//s^e mod n must be the same as m.
	mpz_t t;
	mpz_init(t);
	pow_mod(t,s,e,n);
	if (mpz_cmp(t,m) == 0){
		return true;
		}
	return false;
	}
		
	
	
	
		
		
	
	
	
	
	
	
	
	

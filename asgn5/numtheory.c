#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <stdlib.h>
#include "randstate.h"


void gcd(mpz_t d, mpz_t a, mpz_t b){
	
	mpz_t t,a_copy,b_copy;
	mpz_inits(t,a_copy,b_copy, NULL);
	mpz_set(a_copy, a);
	mpz_set(b_copy, b);
	while (mpz_cmp_ui(b_copy, 0) != 0){
		mpz_set(t, b_copy);
		mpz_fdiv_r(b_copy, a_copy, b_copy);
		mpz_set(a_copy, t);
		}
	mpz_set(d, a_copy);	
	mpz_clears(a_copy,b_copy,t, NULL);
	}
	
void mod_inverse(mpz_t o, mpz_t a, mpz_t n){
	mpz_t r, r_prime;
	mpz_inits(r,r_prime, NULL);
	mpz_set(r, n);//r,r_prime = a,n
	mpz_set(r_prime, a);
	mpz_t t, t_prime;
	mpz_inits(t,t_prime, NULL);
	mpz_set_ui(t, 0);
	mpz_set_ui(t_prime, 1);
	mpz_t q;
	mpz_init(q);//this will the quotient results from the division floor(r/r_prime)
	mpz_t temp;
	mpz_init(temp);

	

	
	while (mpz_cmp_ui(r_prime, 0) != 0){

			
		mpz_fdiv_q(q, r, r_prime);

		mpz_set(temp,r);

		mpz_set(r, r_prime);
		mpz_mul(r_prime, q, r_prime);
		mpz_sub(r_prime, temp, r_prime);

		mpz_set(temp,t);

		mpz_set(t, t_prime);
		mpz_mul(t_prime, q, t_prime);
		mpz_sub(t_prime, temp, t_prime); 
	

		}


	if (mpz_cmp_ui(r, 1) > 0){
		mpz_set_ui(o,0);
		mpz_clears(r,r_prime, NULL);
		mpz_clears(t,t_prime, NULL);
		mpz_clear(temp);
		mpz_clear(q);
		return;
		}
	if (mpz_cmp_ui(t, 0) < 0){
		mpz_add(t,t,n);

		
		}

	mpz_set(o, t);

	
	mpz_clears(r,r_prime, NULL);
	mpz_clears(t,t_prime, NULL);
	mpz_clear(temp);
	mpz_clear(q);
	}
	
	
	

void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n){
	mpz_t v;
	mpz_init(v);
	mpz_set_ui(v,1);
	mpz_t d_copy;
	mpz_init(d_copy);
	mpz_set(d_copy,d);
	mpz_t p;
	mpz_init(p);
	mpz_set(p,a);
	mpz_t rmdr;
	mpz_init(rmdr);
	
	
	
	while (mpz_cmp_ui(d_copy, 0) > 0){
		mpz_fdiv_r_ui(rmdr, d_copy, 2);
		if(mpz_cmp_ui(rmdr, 0) != 0){
			mpz_mul(v, v, p);
			mpz_fdiv_r(v,v,n);
			}
		mpz_mul(p,p,p);
		mpz_fdiv_r(p,p,n);
		mpz_fdiv_q_ui(d_copy,d_copy,2);
		}
	mpz_set(o,v);
	mpz_clear(v);
	mpz_clear(p);
	mpz_clear(rmdr);
	mpz_clear(d_copy);
	}
bool is_prime(mpz_t n, uint64_t iters){//n is the number to test and k is the number of iterations.
	mpz_t rmdr;
	mpz_init(rmdr);

	mpz_fdiv_r_ui(rmdr,n,2);
	
	if(mpz_cmp_ui(rmdr,0)==0){
		return false;
		}
		
	mpz_fdiv_r_ui(rmdr,n,5);
	
	if(mpz_cmp_ui(rmdr,0)==0){
		return false;
		}
	if(mpz_cmp_ui(n,1)==0){
		return false;
		}
		
	
	
	
	int divs_by_2 = 0;
	mpz_t r;
	mpz_init(r); 
	mpz_set(r, n); //r = n
	mpz_sub_ui(r,r,1); //r = n - 1 or r = r - 1
	
	mpz_t a;
	mpz_init(a);
	int j = 0;
	mpz_t y;
	mpz_init(y);
	mpz_t ndif1;
	mpz_init(ndif1);
	mpz_sub_ui(ndif1,n,1); //ndif = n - 1
	mpz_t two; //two = 2
	mpz_init(two);
	mpz_set_ui(two,2);
	mpz_t one; //one = 1
	mpz_init(one);
	mpz_set_ui(one,1);
	mpz_t n_copy; //n_copy is for = n - 3 in generator function
	mpz_init(n_copy);
	mpz_sub_ui(n_copy,n,3);
	
		
		
	while(1){
		mpz_fdiv_q_ui(r,r,2);
		//gmp_printf("the current r is %Zd\n", r);
		
		divs_by_2 += 1;
		//printf("number of divs %d\n",divs_by_2);
		mpz_fdiv_r_ui(rmdr,r,2);
		if (mpz_cmp_ui(rmdr,0) != 0){
			break;
			}
		}
		
	for (uint64_t i = 1; i <= iters; i++){
		
		mpz_urandomm(a, state, n_copy); //generate a number from 0 to n - 4
		mpz_add_ui(a,a,2); //add two to the random number generated
		
		
		pow_mod(y,a,r,n); //y = powmod(generated a, odd r, testee n)

		if ((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp(y, ndif1) != 0)){
			j = 1;
			while ((j <= divs_by_2-1) && (mpz_cmp(y, ndif1) != 0)){
				pow_mod(y,y,two,n);
				if (mpz_cmp(y, one) == 0){
					mpz_clear(r);
					mpz_clear(rmdr);
					mpz_clear(a);
					mpz_clear(y);
					mpz_clear(ndif1);
					mpz_clear(two);
					mpz_clear(one);
					mpz_clear(n_copy);
					return false;
					}
				j++;
				}
			if (mpz_cmp(y, ndif1) != 0){
				mpz_clear(r);
				mpz_clear(rmdr);
				mpz_clear(a);
				mpz_clear(y);
				mpz_clear(ndif1);
				mpz_clear(two);
				mpz_clear(one);
				mpz_clear(n_copy);
				return false;
				}
			}
		
		}
		mpz_clear(r);
		mpz_clear(rmdr);
		mpz_clear(a);
		mpz_clear(y);
		mpz_clear(ndif1);
		mpz_clear(two);
		mpz_clear(one);
		mpz_clear(n_copy);
		return true;
	}
		
void make_prime(mpz_t p, uint64_t bits, uint64_t iters){
	//randstate_init(seed);
	mpz_urandomb(p, state, bits);
	while (is_prime(p, iters) != true){
		mpz_urandomb(p, state, bits);
		}
	}
	


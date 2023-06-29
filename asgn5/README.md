Assignment 5

How to run the encryption, decryption, and keygen program.
	

	1. Type make to combine all included files together.

	2. Typing ./encrypt will encrypt a file or whatever is taken from stdin. This program accepts options -i -o -n -v -h. Option i will set the input file whole option o will set the output file. Option v will enable verbose output. Option n will set the file for the public rsa key. Type in -h to see detsailed specifics of each of the options.
	
	3. Typing ./decrypt will decrypt a file or whatever is taken from stdin. This program accepts options -i -o -n -v -h. Option i will set the input file whole option o will set the output file. Option v will enable verbose output. Option n will set the file for the private rsa key. Type in -h to see detsailed specifics of each of the options.
	
	4. Typing ./keygen will generate two RSA keys, one public and one private. Option s will set the seed of which to generate the key. Option b will allocate the number of bits for the key. Option i set the iters. Option n sets the pubkey file while d set the priv key file to put their respective keys in. v will enable verbose output. Type -h to see specified help options.
	
	
Errors: None known lately.

Sources of help: mpz_sizeinbase() came from Ben (UCSC CSE13s Tutor.). All other sources of help come from the gmp library. 

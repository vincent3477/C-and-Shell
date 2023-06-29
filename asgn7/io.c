#include <stdbool.h>
#include <stdint.h>
#include "defines.h"
#include <unistd.h>
#include <stdio.h>
#include "code.h"
#include "io.h"
#include <fcntl.h>
#include <stdlib.h>

uint64_t bytes_read=0;
uint64_t bytes_written=0;
uint32_t c_index = 0;
uint8_t wbuff[BLOCK]; //This BLOCK will be written to outfile.
int b_index = 0;

int read_bytes(int infile, uint8_t *buf, int nbytes){
	//read takes these arguments (infile, buf, bytes). Attempt to read up to bytes from infile to buf.	
	int read_prog = 0;
	int read_bytes = 0;

	while(read_bytes < nbytes ){
		read_prog = read(infile,buf,nbytes);
		//printf("%d read prog\n",read_prog);
		if(read_prog == 0){

		        break;
		}
		read_bytes += read_prog;
		}
	bytes_read += read_bytes;//updateing the extern
	
	return read_bytes;
	}

int write_bytes(int outfile, uint8_t *buf, int nbytes){
    //we will write from the buffer to the outfile
    
    	int max = 0;
    	while (&buf[max] != NULL && (nbytes >= max)){
    		max++;
		}

    	
    	if (max < nbytes){
    		nbytes = max;
    		}
    		
	int written_bytes = 0;
	int write_prog = 0;
	while(written_bytes < nbytes ){
		write_prog = write(outfile,buf,nbytes);
		written_bytes += write_prog;
		
		
		}
	
	
	/*int write_prog = 0;
	write_prog = write(outfile,buf,nbytes);
	int written_bytes = write_prog;
	while(write_prog != 0){
		write_prog = write(outfile,buf,nbytes);
		printf("%d\n",write_prog);
		written_bytes += write_prog;
		printf("writing\n");
		}
*/	
	written_bytes += bytes_written;//updatging the extern

	return written_bytes;
	}
bool read_bit(int infile, uint8_t *bit){
	static uint8_t sbuff[BLOCK];
	static int i = 0;
	//static int max = 32768;
	static bool max_def = false;
	static int bytes_read = 0;
	static int max_bits = 0;
	
	if(!max_def){
		bytes_read = read_bytes(infile, sbuff, BLOCK);
		max_bits = (8 * (bytes_read));
		//printf("now sarting to read %d\n", max_bits);
		//for(int i = 0 ; i < 832; i++){
		//	int ind = i/8;
		//	uint8_t ival = sbuff[ind];
		//	ival = ival & (1UL<<(i%8));
		//	ival = ival >> (i%8);
		//	printf("%u",ival);
		//	}
		//printf("\n");

		
		max_def = true;
		}

	if(i<max_bits && bytes_read != 0){
		
		int index = i/8; //index represents the byte, that is the index of the array.
		uint8_t curr_byte = sbuff[index];
		curr_byte = curr_byte & (1UL<<(i%8));
		curr_byte = curr_byte >> (i%8);
		*bit = curr_byte;
		i++;
		//printf("%u",curr_byte);
		return true;
		}
	else{
		for(int i = 0 ; i < (BLOCK); i++){
			sbuff[i] = 0;
			}
		
		bytes_read = read_bytes(infile, sbuff, BLOCK);
		if(bytes_read != 0){
			max_bits = 8 * (bytes_read);
			//printf("the max is %d\n", max_bits);
			i = 0;
			int index = i/8; //index represents the byte, that is the index of the array.
			uint8_t curr_byte = sbuff[index];
			curr_byte = curr_byte & (1UL<<(i%8));
			curr_byte = curr_byte >> (i%8);
			*bit = curr_byte;
			i++;

			return true;
			}
		
		

		return false;
		}

	}
void flush_codes(int outfile){
	while(b_index%8!=0){
		int index = b_index/8;
		wbuff[index] = wbuff[index] & ~(1UL<<(b_index%8));
		}
	
	write_bytes(outfile, wbuff, BLOCK);
	for(int i = 0; i < BLOCK; i ++){
		wbuff[i] = 0;
		}
	
	}
	
void write_code(int outfile, Code * c){

	
	//int c_index = 0;
	int max = (BLOCK*8);//change to 4096*8 when done

	
	
		
	//uint8_t ival = 0;
	//popoff bits from a code.
	//set the bits to the 4096 buffer based on the value that was popped off
	//if its is full, then write.
	//uint8_t ival = 0;
	//printf("cize is %u\n",code_size(c));
	static uint64_t bytes_index = 0;
	while(code_size(&c[bytes_index])!=0){
		//printf("we are at byte %lu\n", bytes_index);
		//printf("we have read %lu\n",bytes_read);
		c_index = 0;
		while(c_index < code_size(&c[bytes_index])){
			//printf("cize is %u\n",code_size(&c[codes_index]));
			uint32_t index = b_index/8; 
			if(code_get_bit(&c[bytes_index], c_index) == 1){
				wbuff[index] = wbuff[index] | 1UL<<(b_index%8);
				//printf("1 was obtained\n");
				}
		
			else if(code_get_bit(&c[bytes_index], c_index) == 0){
				wbuff[index] = wbuff[index] & ~(1UL<<(b_index%8));
				//printf("0 was obtained\n");
				}
			
			b_index++;
			c_index++;
			//printf("bindex %u\n",b_index);


			if(b_index == max){
				//printf("the wbuff befoire the we functinb is %u\n",wbuff[0]);
				//write_bytes(outfile, wbuff, BLOCK);
				//printf("the wbuff after the we functinb is %u\n",wbuff[0]);
				flush_codes(outfile);
				//printf("done fluishing\n");
				b_index = 0;
				}
			
			}
			bytes_index++;
			
		}
	/*for(int i = 0; i < b_index;i++){
		ival = 0;
		int index = i/8;
		ival = wbuff[index];
		ival = ival & (1UL<<(i%8));
		ival = ival >> (i%8);
		printf("the ival is %u\n",ival);
		}
	printf("stop.\n");
	*/
		

	if (b_index < max){
	
		if((b_index / 8) ==0){
			write_bytes(outfile, wbuff, 1);
			//in such cases where we are writing less than a byte.
			}
		else{
			write_bytes(outfile, wbuff, (b_index / 8));
			}
			
		c_index = 0;
		b_index = 0;
		for(int i = 0; i < BLOCK; i ++){
			wbuff[i] = 0;
			}
		}
	}
	

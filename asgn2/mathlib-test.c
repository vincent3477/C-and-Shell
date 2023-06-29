#include <stdio.h>
#include <unistd.h>
#include "mathlib.h"
#define OPTIONS "ascSCTl"
#include <math.h>

int main(int argc, char **argv){
	double two_pi = M_PI * 2.0;
	int opt = 0;
	int num_sin_tests = 0; //each shows the number of times the test is run. Each of these tests cannot be run more than once.
	int num_cos_tests = 0;
	int num_arcsin_tests = 0;
	int num_arccos_tests = 0;
	int num_arctan_tests = 0;
	int num_log_tests = 0;
	
	while((opt = getopt(argc, argv, OPTIONS))!=-1){
		switch(opt){
		case 'a':
			if (num_sin_tests == 0){
			
				printf("  x            sin           Library        Difference\n");
				printf("  _            ______           _______        __________\n"); 
				for(double i = 0.0;i <= two_pi ; i+=(0.05*M_PI)){
					printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n",i , my_sin(i), sin(i), my_sin(i)-sin(i));
					}

				num_sin_tests++;
				}
			
			if (num_cos_tests == 0){
				printf("  x            cos            Library       Difference\n");
                        	printf("  _            ______            _______       __________\n");
			
				for(double i = 0.0;i <= two_pi; i+=(0.05*M_PI)){
  					printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", i, my_cos(i), cos(i), my_cos(i)-cos(i));	
					}
				num_cos_tests++;

				}

			if (num_arcsin_tests == 0){
			
				printf("  x            arcsin            Library       Difference\n");
                        	printf("  _            ______            _______       __________\n");

				for(double i = -1.0;i <=1.0; i+=0.05){
                                	printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", i, my_arcsin(i), asin(i), my_arcsin(i)-asin(i));
					}

				num_arcsin_tests++;
			}
			
			if (num_arccos_tests == 0){
				printf("  x            arccos            Library       Difference\n");
                        	printf("  _            ______            _______       __________\n");

				for(double i = -1.0;i <= 1.0; i+=0.05){
                                	printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", i, my_arccos(i), acos(i), my_arccos(i)-acos(i));
					}

				num_arccos_tests++;
			}
			
			if (num_arctan_tests == 0){	
				printf("  x            arctan            Library       Difference\n");
                        	printf("  _            ______            _______       __________\n");

				for(double i = 1.0;i < 10.0; i+=0.05){
                                	printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n",i, my_arctan(i), atan(i), my_arctan(i)-atan(i));
				}

				num_arctan_tests++;
			}
			
			if(num_log_tests == 0){
				printf("  x            log            Library       Difference\n");
                        	printf("  _            ______            _______       __________\n");

				for(double i = 1.0;i < 10.0; i+=0.05){
                                	printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", i, my_log(i), log(i), my_log(i)-log(i));               
					}

				num_log_tests++;
			}	
			break;
		case 's':
			if (num_sin_tests == 0){
			
				printf("  x            sin           Library        Difference\n");
				printf("  _            ______           _______        __________\n"); 
				for(double i = 0.0;i <= two_pi ; i+=(0.05*M_PI)){
					printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n",i , my_sin(i), sin(i), my_sin(i)-sin(i));
					}

				num_sin_tests++;
				}
                        break;
		case 'c':
			
			if (num_cos_tests == 0){
				printf("  x            cos            Library       Difference\n");
                        	printf("  _            ______            _______       __________\n");
			
				for(double i = 0.0;i <= two_pi; i+=(0.05*M_PI)){
  					printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", i, my_cos(i), cos(i), my_cos(i)-cos(i));	
					}
				num_cos_tests++;

				}


			break;	
		case 'S':
			if (num_arcsin_tests == 0){
			
				printf("  x            arcsin            Library       Difference\n");
                        	printf("  _            ______            _______       __________\n");

				for(double i = -1.0;i <=1.0; i+=0.05){
                                	printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", i, my_arcsin(i), asin(i), my_arcsin(i)-asin(i));
					}

				num_arcsin_tests++;
			}
			break;	
		case 'C':
			if (num_arccos_tests == 0){
				printf("  x            arccos            Library       Difference\n");
                        	printf("  _            ______            _______       __________\n");

				for(double i = -1.0;i <= 1.0; i+=0.05){
                                	printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", i, my_arccos(i), acos(i), my_arccos(i)-acos(i));
					}

				num_arccos_tests++;
			}
			break;	
		case 'T':
			if (num_arctan_tests == 0){	
				printf("  x            arctan            Library       Difference\n");
                        	printf("  _            ______            _______       __________\n");

				for(double i = 1.0;i < 10.0; i+=0.05){
                                	printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n",i, my_arctan(i), atan(i), my_arctan(i)-atan(i));
				}

				num_arctan_tests++;
			}
			
			break;
		case 'l':
			if(num_log_tests == 0){
				printf("  x            log            Library       Difference\n");
                        	printf("  _            ______            _______       __________\n");

				for(double i = 1.0;i < 10.0; i+=0.05){
                                	printf(" %7.4lf % 16.9lf % 16.9lf % 16.12lf\n", i, my_log(i), log(i), my_log(i)-log(i));               
					}

				num_log_tests++;
			}
 			break;	
		}
	}
	return 0;
}

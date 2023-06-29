#include <math.h>
#include <stdio.h>
#include "mathlib.h"
static const double epsilon = 1e-10;
static double abs_val(double x){

	if (x > 0){
		return x;
	}
	else{
		return x * -1.0;
	}
} 

double square_root (double x) {
        double m, l = 0.0;
  	double h = (x < 1) ? 1 : x;
  	double range = 0.0;
  	do {
    		m = (l + h) / 2.0;
    		if (m * m < x) {
     		   l = m;
   		 } else {
      		   h = m;
    		 }
    	range = (l > h) ? l - h : h - l;
  	} while (range > epsilon);
  	return m;
}

static double Exp(double x){
	double t = 1.0;
	double y = 1.0;
	for (double k = 1.0; t > epsilon; k+=1.0){
		t *= x/k;
		y += t;
		
	}
	return y;

}

double my_log(double x){
	double previous = 1.0; 
	


	double exp_x = Exp(1.0);
	
	double current = 0;

	while(abs_val(exp_x - x) > epsilon){
		exp_x = Exp(previous);
		current = previous + ((x - exp_x)/exp_x);

		previous = current; 
	}
	return current;	
}	

double my_sin(double x){


	double abs_x = abs_val(x);


	
	
	int iterator = 1;

	double current_a_n = abs_val((abs_x/(2*iterator)) * (abs_x/((2*iterator)+1)) * abs_x/iterator);
		
	current_a_n *= -1;


	double my_sin_sequence = current_a_n + abs_x;
	
	double previous = current_a_n;
	


	while (abs_val(current_a_n) > epsilon){
	
		iterator++;

		
		current_a_n = abs_val((abs_x/(2*iterator)) * (abs_x/((2*iterator)+1)) * abs_val(previous));

		
	

		if (iterator % 2 != 0){
			current_a_n *= -1;
			
			
				

		}

		my_sin_sequence += current_a_n;

		previous = current_a_n;
	}
	
	if (x < 0){
		return my_sin_sequence * -1;
	}else{
	
		return my_sin_sequence;
	}
	
}


double my_cos(double x){


	double my_cos_sequence = 0.0;
	my_cos_sequence += my_sin((M_PI/2)-x);
	return my_cos_sequence;
}

double my_arcsin(double x){
	
	double previous = 0;

	double current = (previous - ((my_sin(previous)-x)/my_cos(previous))); 

	while(abs_val(current - previous) > epsilon){
		previous = current;
		current = (previous - ((my_sin(previous)-x)/my_cos(previous)));

		
	}
	return current;
}
double my_arccos(double x){

	return (M_PI/2.0 - my_arcsin(x));
}
double my_arctan(double x){
	return (my_arcsin(x/square_root((x*x)+1)));
}	

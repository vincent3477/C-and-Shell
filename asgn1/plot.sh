#!/bin/bash

make clean && make collatz

#Start of code that is used to provide date to print figures 2,3, and 4.
for i in {2..10000};do 
	
	./collatz -n $i > /tmp/collatz.dat

	coordinates1=$i
	coordinates1+=" "
	
	coordinates2=$i
	coordinates2+=" "
	
	
	count=$(wc -l < /tmp/collatz.dat)
	count=$(($count - 1))
	coordinates1+=$count
	echo $coordinates1 >> /tmp/collatzplot.dat
	
	sort -n -r -o /tmp/collatz.dat /tmp/collatz.dat
	highNumReached=$(head -n 1 /tmp/collatz.dat)
	coordinates2+=$highNumReached
	echo $coordinates2 >> /tmp/collatzplot_2.dat
	
	echo $count >> /tmp/seqLengths.dat
	
	
        done

        
sort -n -o /tmp/seqLengths.dat /tmp/seqLengths.dat

uniq -c /tmp/seqLengths.dat /tmp/collatzplot_3.dat 

#Start of code that is used to draw a house

xstart=0
ystart=250

#drawing the left roof of the house
for i in {0..150}; do
	houseCoordinates=$i
	houseCoordinates+=" "
	yCoordinates=$(($i+150))
	houseCoordinates+=$yCoordinates
	echo $houseCoordinates >> /tmp/houseplot.dat
	done
	
	
#drawing the right roof of the house
yCoordinates=300
for j in {150..300};do
	houseCoordinates=$j
	houseCoordinates+=" "
	
	yCoordinates=$((yCoordinates-1))
	
	houseCoordinates+=$yCoordinates
	echo $houseCoordinates >> /tmp/houseplot.dat
	done
	

#drawing the side walls of the house as well as the left of the chimney.
for k in {0..215};do
	houseCoordinates=20
	houseCoordinates+=" "
	houseCoordinates+=$k
	echo $houseCoordinates >> /tmp/houseplot.dat
	
	if (($k <= 170));then
		houseCoordinates=280
		houseCoordinates+=" "
		houseCoordinates+=$k
		echo $houseCoordinates >> /tmp/houseplot.dat
		fi
	done
	
#outlining the top of the chimney,the horizontal aspect of the window, and the top of the door.
for l in {20..45};do

	if (($l <= 40));then
		houseCoordinates=$l
		houseCoordinates+=" "
		houseCoordinates+=215
	
		echo $houseCoordinates >> /tmp/houseplot.dat
	
	
		houseCoordinates=$l
		houseCoordinates=$(($l+160))
		houseCoordinates+=" "
		houseCoordinates+=125
	
		echo $houseCoordinates >> /tmp/houseplot.dat
	
		houseCoordinates=$l
		houseCoordinates=$(($l+160))
		houseCoordinates+=" "
		houseCoordinates+=95
	
		echo $houseCoordinates >> /tmp/houseplot.dat
	
		houseCoordinates=$l
		houseCoordinates=$(($l+160))
		houseCoordinates+=" "
		houseCoordinates+=65
		echo $houseCoordinates >> /tmp/houseplot.dat
		fi
	
	houseCoordinates=$l
	houseCoordinates=$(($l+30))
	houseCoordinates+=" "
	houseCoordinates+=125
	echo $houseCoordinates >> /tmp/houseplot.dat
	
	done
for m in {190..215};do
	houseCoordinates=40
	houseCoordinates+=" "
	houseCoordinates+=$m
	echo $houseCoordinates >> /tmp/houseplot.dat
	done
	
for n in {0..125};do


	houseCoordinates=50
	houseCoordinates+=" "
	houseCoordinates+=$n
	echo $houseCoordinates >> /tmp/houseplot.dat
	
	houseCoordinates=75
	houseCoordinates+=" "
	houseCoordinates+=$n
	echo $houseCoordinates >> /tmp/houseplot.dat
	
	
	done

for o in {65..125};do
	houseCoordinates=180
	houseCoordinates+=" "
	houseCoordinates+=$o
	echo $houseCoordinates >> /tmp/houseplot.dat
	
	houseCoordinates=200
	houseCoordinates+=" "
	houseCoordinates+=$o
	echo $houseCoordinates >> /tmp/houseplot.dat
	
	done
	
houseCoordinates=65 
houseCoordinates+=" "
houseCoordinates+=65
echo $houseCoordinates >> /tmp/houseplot.dat
	
gnuplot <<END
	 
	set terminal pdf
	set output "collatz.pdf" 
	set xrange [0:10000] 
	set yrange [0:300] 
	set title "Collatz sequence lengths" 
	set xlabel "n"
	set ylabel "length"
	set zeroaxis
	plot "/tmp/collatzplot.dat" with dots	 
	
	set xrange [0:10000]  
	set yrange [0:100000]  
	set title "Maximum Collatz Sequence Values" 
	set xlabel "n"
	set ylabel "value"
	set zeroaxis
	plot "/tmp/collatzplot_2.dat" with dots	

	set style histogram columnstacked
	set xrange [0:225] 
	set yrange [0:200] 
	set xlabel "lengths"
	set ylabel "frequency"  
	set zeroaxis

	plot "/tmp/collatzplot_3.dat" using 2:1 with boxes
	set xrange[0:500]
	set yrange[0:500]
	set zeroaxis
	set title "House"
	plot "/tmp/houseplot.dat" with dots
	
END


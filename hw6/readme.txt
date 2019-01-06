Assignment 6 Report

After finishing the homework assignment for parallelism,
I think I learned a lot on the process of parallelizing things in 
C code.  
Coming into the problem, I had no idea where to go and what to start
with, but after reading up on the POSIX documentation, I realized it
needed only a few functions to create threads that ran the process 
quicker.

One issue I ran into was trying to keep the source code completely the
same, since I didn't want to complicate it further, but realized that a
single dimension array wasn't going to work if I was working on multiple
columns at once when I was running it in parallel.  While something minute,
it helped me realize that when running in parallel, there are specific 
variables and options that need to be completely changed to make the process
run faster.



time ./srt 1-test.ppm >1-test.ppm.tmp

real    0m40.653s
user    0m40.640s
sys     0m0.001s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real    0m20.483s
user    0m40.896s
sys     0m0.001s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real    0m11.000s
user    0m43.205s
sys     0m0.002s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real    0m5.764s
user    0m44.306s
sys     0m0.003s

In conclusion, the timing of one thread compared to that of 8 threads is
such a drastic change.  Starting from 40s from the first to only 5, is a 
factor 8, a huge difference.  This makes sense though, since there are
8x the amount of threads processing the same information.
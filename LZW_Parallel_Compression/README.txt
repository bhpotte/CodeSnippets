Section 1: functions

Our project makes use of two incredibly important functions: namely encoding() and decoding() which starts the entire process!
encoding() wants to read a line through character by character and append those new characters to a substring which is added to 
the character encoding table as a new entry. Rinse and repeat until we reach the end of the file encoding() is reading from.

decoding() works in the opposite way to encoding(). It will read each output code generated from encoding() in order and translate
those codes back to the original text dependent on what substring that output code points to. We continue this until we read through
all codes and the result should be the original text without any lost text.


Section 2: files

- seqLzw.cpp -
This is essentially the sequential version of our project and is just a slight modification of the one we found from GeeksForGeeks. 
It will ask for 3 files: the sample.txt/gutenfile.txt file you want to read from, the compFile.txt to write the output codes from 
the sample.txt/gutenfile.txt by using encoding(), and the decompFile.txt to write the text by reading the output codes from the 
compFile using decoding().

To compile, type in: g++ -o seqLzw seqLzw.cpp

Then, you can run it by typing: ./seqLzw sample.txt (or gutenfile.txt) compFile.txt decompFile.txt


- lzwMPI.cpp -
This is our MPI parallel version of our project and utilizes gather(), gatherv(), and scatter() for our MPI operations.
It will ask for the same 3 files as specified eariler in seqLzw.cpp, but now you can add in processes/threads.

To compile, type in: mpic++ -fopenmp lzwMPI.cpp -o lzwMPI

Then, you can run it by typing: mpiexec -n <numberProcessors> ./lzwMPI sample.txt compFile.txt decompFile.txt
Example:                        mpiexec -n 2 ./lzwMPI sample.txt (or gutenfile.txt) compFile.txt decompFile.txt


- lzwOMP.cpp -
This is our OMP parallel version of our project and utilizes pragmas (omp parallel for, critical and num_threads)
It will ask for the same 3 files as specified eariler in seqLzw.cpp, but now you can add in processes/threads.

To compile, type in: g++ -fopenmp lzwOMP.cpp -o lzwOMP
                                                                      
Then, you can run it by typing: ./lzwOMP <num_threads> <input_file> <compressed_output_file> <decompressed_output_file>
Example:                        ./lzwOMP 5 sample.txt (or gutenfile.txt) compFile.txt decompFile.txt


- lzwScriptOMP.sb -
This is our job script that we would run in expanse to get our data. It currently runs both parLzwOMP.cpp
with 1, 2, 5, 10, 20, 40 threads respectively. You don't need to load any modules as the modules are defined in the batch file
already.

to run it, simply type in expanse: sbatch lzwScriptOMP.sb


- lzwScriptMPI.sb -
This is our job script that we would run in expanse to get our data. It currently runs both parLzwMPI.cpp
with 1, 2, 5, 10, 20, 40 threads respectively. You don't need to load any modules as the modules are defined in the batch file
already.

to run it, simply type in expanse: sbatch lzwScriptMPI.sb
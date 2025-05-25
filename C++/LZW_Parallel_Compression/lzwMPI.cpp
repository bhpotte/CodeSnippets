//Geeks for Geeks LZW coding
//Modified by group
//parallel version

// compile: mpic++ -fopenmp -o lzwMPI lzwMPI.cpp
// Usage: mpiexec -n <nproc> ./lzwMPI sample.txt compFile.txt decompFile.txt

#include <bits/stdc++.h> 
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdint>
#include <vector>
#include "mpi.h"

using namespace std; 

/* 
	Encoding will take a sequence of chars, symbols, etc, then group them into
	strings, then convert those strings into output codes. It will then place those 
	codes into the comp file. 
*/
vector<int> encoding(string s1) 
{
	unordered_map<string, int> table; 

	// go from 0 to 255 - 256 string values in the table
	for (int i = 0; i <= 255; i++) { 
		string ch = ""; 
		ch += char(i);
		table[ch] = i; 
	}
        
	// initialize p, c, code and output_code
	string p = "", c = ""; 
	p += s1[0]; 
	int code = 256; 
	vector<int> output_code; 
	
	//compFile << "String\tOutput_Code\tAddition\n";
	// go through s1
    //#pragma omp parallel for num_threads(10) private(p, c)
	for (int i = 0; i < s1.length(); i++) { 
		if (i != s1.length() - 1){

		// if i is not the last value, then append the next value from s1 to c
			c += s1[i + 1];
		}
		if (table.find(p + c) != table.end()) { 
			p = p + c; 
		} 
		else { 
			//compFile << p << "\t" << table[p] << "\t\t"
				//<< p + c << "\t" << code << endl;
			output_code.push_back(table[p]); 
			table[p + c] = code++;
			p = c; 
			
		} 

		// empty c for the next i iteration
		c = ""; 
	} 
	//compFile << p << "\t" << table[p] << endl; 
	output_code.push_back(table[p]); 
	return output_code; 
} 

/* 
	Decoding will take the output codes generated from encoding and translate
	into the decomp file through the code table 
*/
void decoding(vector<int> op, ofstream &decompFile) 
{ 
	//decompFile << "\nDecoding\n"; 
	// Table to modify
	unordered_map<int, string> table; 

	// append integers 0-255 as a char to the table
	for (int i = 0; i <= 255; i++) { 
		string ch = ""; 
		ch += char(i); 
		table[i] = ch; 
	} 

	// initialize c, then set it as the oldest value from the vector table
	// then send to the decomp file.
	int old = op[0], n; 
	string s = table[old]; 
	string c = ""; 
	c += s[0]; 
	decompFile << s; 
	int count = 256; 

	// go through vector table
	for (int i = 0; i < op.size()-1; i++) { 
		// specify bounds
		if(op[i]==-1 && i < op.size()-1){
			// if we hit a -1, clear the table and build a new one for the next code
			table.clear(); 
			for (int j = 0; j <= 255; j++) { 
				string ch = ""; 
				ch += char(j); 
				table[j] = ch; 
			} 
			old = op[i+1], n; 
			string s = table[old]; 
			string c = ""; 
			c += s[0];  
			count = 256;
		}
		// else we go through the current code and translate it
		else{
			n = op[i + 1]; 

			// if we find the code that matches n, then append old value to s, then
			// add c to s.
			if (table.find(n) == table.end()) { 
				s = table[old]; 
				s = s + c; 
			} 
			else { 
				// else we set s to the value at table in the nth index
				s = table[n]; 
			} 
			decompFile << s; 
			c = ""; 
			c += s[0]; 
			table[count] = table[old] + c; 
			count++;
			old = n; 
		}
		
	} 
    //decompFile << endl;
}

int main(int argc, char* argv[]) 
{ 
    // mpi variables
    int rank, nproc, totalLength=0, padding;
	ifstream file;	/* sample file to work with */
	ofstream compFile, decompFile;
	stringstream buffer; /* Read into the file */
	string content; /* store read data into */
	int receiveAmount;
	int length;
	char *localBlock;
	vector<int> localEncoded; /* Local variables to work with each individual rank */
	vector<int> globalEncoded;
	vector<int> allSizes;
	vector<int> displs;

    MPI_Init (&argc, &argv); /* Intialize MPI*/
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &nproc); // return number of processes
    MPI_Comm_rank(comm, &rank); // returns rank

	//error checking
	if(argc!=4){
		if(rank==0){
			cout << "Usage: mpiexec -n <numberProcessors> ./lzwMPI sample.txt compFile.txt decompFile.txt" << endl;
		}
		MPI_Finalize();
		return 0;
	}

	// Get start time
	MPI_Barrier(comm);
	double startTime = MPI_Wtime();
	
	if(rank==0){
		// files to work with
		file.open(argv[1]);
		buffer << file.rdbuf();
		content = buffer.str();
		file.close();
		totalLength=content.size();

		// add padding to work with non-evenly divisible work
		if(totalLength%nproc!=0){
			padding = nproc - (totalLength % nproc);
			content.append(padding, ' ');
			totalLength+=padding;
		}
	}

	MPI_Bcast(&totalLength, 1, MPI_INT, 0, comm);

	// work
	receiveAmount = totalLength/nproc;
	localBlock = new char[receiveAmount+1];

	// divide work to each rank
	MPI_Scatter(content.data(), receiveAmount, MPI_CHAR, localBlock, receiveAmount, MPI_CHAR, 0,comm);
	localBlock[receiveAmount]='\0';
	
	
	string localString(localBlock);
	localEncoded = encoding(localString);

	//Experimental adding of -1 to indicate end of table
	localEncoded.push_back(-1);


	int localSize = localEncoded.size();

	if(rank==0){
		allSizes.resize(nproc);
	}

	// gather all the work back to rank 0
	MPI_Gather(&localSize, 1, MPI_INT, allSizes.data(), 1, MPI_INT, 0, comm);

	if(rank==0){
		displs.resize(nproc);
		displs[0]=0;
		for(int i=1; i<nproc; i++){
			displs[i] = displs[i-1]+allSizes[i-1];
		}
		globalEncoded.resize(displs[nproc-1]+allSizes[nproc-1]);
	}

	MPI_Gatherv(localEncoded.data(), localSize, MPI_INT, globalEncoded.data(), allSizes.data(), displs.data(), MPI_INT, 0, comm);
	
	MPI_Barrier(comm);
	double elapsed = MPI_Wtime() - startTime;

	
	if(rank==0){
		// write into the compiled file each code
		compFile.open(argv[2]);
		compFile << "Encoding\n"; 
		for(int code:globalEncoded){
			//Experimental adding of new line to indicate new table
			compFile<<code<<" ";
		}

		// write into decompiled file the translated codes from encoding()
		decompFile.open(argv[3]);
		decoding(globalEncoded, decompFile);

		cout<<"Time elasped: "<<elapsed<<" Sec\n";

		compFile.seekp(0, std::ios::end);
		double file_size1 = compFile.tellp() * .001 * .001;
		cout<<"Size of the comp file is"<<" "<< file_size1<<" "<<"MB\n";

		decompFile.seekp(0, std::ios::end);
		double file_size2 = decompFile.tellp() * .001 * .001;
		cout<<"Size of the decomp file is"<<" "<< file_size2<<" "<<"MB\n";

		double percentDiff = ((file_size1 - file_size2) / file_size2) * 100;

		// Compression rate is negative when compressed is larger than decompressed
		cout <<"Compression rate : "<<percentDiff<<"%"<<endl;

		compFile.close();
		decompFile.close();
	}
	//if(rank==0){
	//	vector<int> output_code = encoding(content, compFile); 
	//	compFile << "Output Codes are: "; 
	//	for (int i = 0; i < output_code.size(); i++) { 
	//		compFile << output_code[i] << " "; 
	//	} 
	//	compFile << endl;
	//}
	// assign codes to each unique letter comboniations that LZW handles
 
	//decoding(output_code, decompFile); 

	// clear up used block and finalize
	delete[] localBlock;
	MPI_Finalize();
	return 0;

} 

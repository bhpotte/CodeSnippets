//Geeks for Geeks LZW coding
//Modified by group


#include <bits/stdc++.h> 
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdint>
#include <omp.h>

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
    #pragma omp parallel for 
	for (int i = 0; i <= 255; i++) { 
		string ch = ""; 
		ch += char(i); 
        #pragma omp critical
		table[ch] = i; 
	} 

	// initialize p, c, code and output_code
	string p = "", c = ""; 
	p += s1[0]; 
	int code = 256; 
	vector<int> output_code; 

	// go through s1
	for (int i = 0; i < s1.length(); i++) { 
		if (i != s1.length() - 1) 
			// if i is not the last value, then append the next value from s1 to c
			c += s1[i + 1]; 
		if (table.find(p + c) != table.end()) { 
			p = p + c; 
		} 
		else { 
			//compFile << p << "\t" << table[p] << "\t\t"
				//<< p + c << "\t" << code << endl; 
			output_code.push_back(table[p]); 
			table[p + c] = code; 
			code++; 
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
	unordered_map<int, string> table; 

	// append integers 0-255 as a char to the table
    #pragma omp parallel for
	for (int i = 0; i <= 255; i++) { 
		string ch = ""; 
		ch += char(i); 
        #pragma omp critical
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
	for (int i = 0; i < op.size() - 1; i++) { 
		// specify bounds
		if(op[i]==-1 && i < op.size()-1){
			// if we hit a -1, clear the table and build a new one for the next code
			table.clear(); 
			#pragma omp parallel for
			for (int j = 0; j <= 255; j++) { 
				string ch = ""; 
				ch += char(j); 
				// updating table leads to critical section; we want to prevent that
				#pragma omp critical
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
    //decompFile << endl;
	}
}

int main(int argc, char* argv[]) 
{ 
	//error checking
	if(argc!=5){
		cout<<"Usage: ./lzwOMP <num_threads> <input_file> <compressed_output_file> <decompressed_output_file>"<<endl;
		return 0;
	}

	// time measurers
    double start;
    double duration;

	// files to work with
    ifstream file(argv[2]);
    ofstream compFile(argv[3]);
    ofstream decompFile(argv[4]);
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

	// measure start time
    start = omp_get_wtime();

    int num_threads = stoi(argv[1]);
    int n = content.size();
    int chunkSize = n/num_threads;
    int remainder = n%num_threads;

    vector<vector<int>> compressedChunks(num_threads);

	// assign codes to each unique letter comboniations that LZW handles to each thread
	#pragma omp parallel num_threads(num_threads)
    {
        int tid = omp_get_thread_num();
        int start = tid * chunkSize;
        if(tid<remainder){
            start+=tid;
        }
        else{
            start+=remainder;
        }
        int end = start + chunkSize;
        if(tid<remainder){
            end+=1;
        }

        string chunk = content.substr(start, end-start);

        vector<int> localEncoded = encoding(chunk);

        compressedChunks[tid] = localEncoded;
    }
    compFile<<"Encoding\n";
    vector<int> globalEncoded;

	// write into the compiled file each code
    for(int i=0; i<num_threads; i++){
        for(int code:compressedChunks[i]){
            compFile<<code<<" ";
            globalEncoded.push_back(code);
        }
	    //Experimental adding of new line to indicate new table
        compFile<<"-1 ";
        globalEncoded.push_back(-1);
    }
	compFile << endl; 

	// write into decompiled file the translated codes from encoding()
	decoding(globalEncoded, decompFile); 
	
	// measure time elapsed
    duration = omp_get_wtime()-start;
    cout<<"Time Taken: " <<duration<<" seconds"<<endl;


	
	// Get compression percentage
   compFile.seekp(0, std::ios::end);
   double file_size1 = compFile.tellp() * .001 * .001;
   cout<<"Size of the comp file is"<<" "<< file_size1<<" "<<"MB\n";

   decompFile.seekp(0, std::ios::end);
   double file_size2 = decompFile.tellp() * .001 * .001;
   cout<<"Size of the decomp file is"<<" "<< file_size2<<" "<<"MB\n";

   double percentDiff = ((file_size1 - file_size2) / file_size2) * 100;

	// Compression rate is negative when compressed is larger than decompressed
   cout <<"Compression rate : "<<percentDiff<<"%"<<endl;
	
} 

//Geeks for Geeks LZW coding
//Modified by group


#include <bits/stdc++.h> 
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdint>

using namespace std; 

/* 
	Encoding will take a sequence of chars, symbols, etc, then group them into
	strings, then convert those strings into output codes. It will then place those 
	codes into the comp file. 
*/
vector<int> encoding(string s1, ofstream &compFile) 
{
    
    compFile << "Encoding\n"; 
	unordered_map<string, int> table; 
	for (int i = 0; i <= 255; i++) { 
		string ch = ""; 
		ch += char(i); 
		table[ch] = i; 
	} 

	string p = "", c = ""; 
	p += s1[0]; 
	int code = 256; 
	vector<int> output_code; 
	//compFile << "String\tOutput_Code\tAddition\n"; 
	for (int i = 0; i < s1.length(); i++) { 
		if (i != s1.length() - 1) 
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
	for (int i = 0; i <= 255; i++) { 
		string ch = ""; 
		ch += char(i); 
		table[i] = ch; 
	} 
	int old = op[0], n; 
	string s = table[old]; 
	string c = ""; 
	c += s[0]; 
	decompFile << s; 
	int count = 256; 
	for (int i = 0; i < op.size() - 1; i++) { 
		n = op[i + 1]; 
		if (table.find(n) == table.end()) { 
			s = table[old]; 
			s = s + c; 
		} 
		else { 
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

int main(int argc, char* argv[]) 
{ 
	//error checking
	if(argc!=5){
		cout<<"Usage: ./a.out <nodes> <readFile> <compiledFile> <decompiledFile>"<<endl;
		return 0;
	}

	// time measurers
    clock_t start;
    double duration;

	// files to work with
    ifstream file(argv[2]);
    ofstream compFile(argv[3]);
    ofstream decompFile(argv[4]);
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

	// measure start time
    start = clock();

	// assign codes to each unique letter comboniations that LZW handles
	vector<int> output_code = encoding(content, compFile); 
	compFile << "Output Codes are: "; 
	for (int i = 0; i < output_code.size(); i++) { 
		compFile << output_code[i] << " "; 
	} 
	compFile << endl; 
	decoding(output_code, decompFile); 
	
	// measure time elapsed
    duration = (clock()-start)/(double)CLOCKS_PER_SEC;
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

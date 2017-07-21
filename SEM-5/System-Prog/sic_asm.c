#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>
#include <random>
#include <iomanip>
#define MEMORY_SIZE 8192
using namespace std;

unsigned char memory[MEMORY_SIZE]; // model for the memory
map <string, string> op_tab;

void operator_table()
{
	op_tab["ADD"] = "18";
	op_tab["SUB"] = "1C";
	op_tab["MUL"] = "20";
	op_tab["DIV"] = "24";
	op_tab["LDA"] = "00";
	op_tab["LDX"] = "04";
	op_tab["STA"] = "0C";
	op_tab["COMP"] = "28";
	op_tab["TIX"] = "2C";
    op_tab["RSUB"] = "10";
    op_tab["JSUB"] = "11";
    op_tab["MOV"] = "FF";
}

class assembler
{
	int ACC, X, L, PC;
	string ip_file;
	int code_start, data_start;
	int data_bytes, code;
	map <string, std::vector<int> > sym_tab ;
	void parse_file();
	int get_data_location(string,string,string);
	unsigned char process_byte(string);
	public:
	assembler(string file):ip_file(file)
	{
		ACC=X=L=PC=0;
		code=0;
		operator_table();
		clear_memory();
	}
	void clear_memory();
	void load_memory();
	void assemble();
};
unsigned char assembler::process_byte(string byte_string)
{
	// byte string should be of the form F'XX' where F is the format (C,X,B) and XX is the value
	// e.g C'Z'; X'A2'; B'00011011'
	char beg_char = byte_string.at(0);
	char byte;
	try
	{
		switch (beg_char)
		{
			case 'C': byte = byte_string.at() // edit here
		}
	}
	catch ( ... )
	{
		cout << "Invalid byte format" << endl;
		return 0;
	}
	return byte;
}
void assembler::parse_file()
{
	fstream in(ip_file,ios::in);
	string line; int lineno=0;
	random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 1024); // define the range
    code_start = distr(eng);
    cout << code_start;
    code = code_start;
	while (!in.eof())
	{
		//cout << "in main loop";
		getline(in,line);
		//cout << line << endl;
		int p=0; string word;
		int token=0;
		istringstream iss(line);
		string tokens[3];
		iss >> tokens[0] >> tokens[1] >> tokens[2];
		cout << tokens[0] << "," << tokens[1] << "," << tokens[2] << endl;
		if (lineno==0 && !(tokens[0].compare("START")))
		{
			code_start = std::stoi (tokens[1],nullptr,16);
			code = code_start;
			//cout << code_start;
		}
		else if (op_tab.find(tokens[0]) != op_tab.end())
		{
			// operator encountered
			memory[code++] = std::stoi(op_tab.at(tokens[0]),nullptr,16);
			printf ("hi%02x\n",memory[code-1]);
			// in SIC no immediate addressing
			sym_tab[tokens[1]].push_back(code++);
			code++;
			//sym_tab[tokens[1]].push_back(code++);
			for (int i=0; i<sym_tab[tokens[1]].size(); i++ ) cout << sym_tab[tokens[1]][i] << "-";
		}
		else if (sym_tab.find(tokens[0]) != sym_tab.end()) // if storage variable
		{

			int loc;
			if (op_tab.find(tokens[0]) == op_tab.end())
			{
				cout << "symbol"  << tokens[1] << endl;
				loc = get_data_location(tokens[0],tokens[1],tokens[2]);
				unsigned char high, low;
				for (int i=0; i<sym_tab[tokens[0]].size(); i++)
				{
					low = (loc & 255);
					high = (loc >> 8);
					memory[sym_tab[tokens[0]][i]] = low;
					memory[sym_tab[tokens[0]][i]+1] = high;
				}
			}
		}
		else if (sym_tab.find(tokens[0]) == sym_tab.end()) // if not an operator and not an existing symbol
		{
			sym_tab[tokens[0]].push_back(code);
			
		}
		lineno++;
	}
	for (int i=code_start; i<code_start+18; i++) cout << (int)memory[i] << " ";
	in.close();
}
int assembler::get_data_location(string name, string st_type="", string val="")
{ // allocate the variable to somewhere in memory
	if (!st_type.compare("WORD")) // allocate constant word
	{
		cout << "word" << val << endl;
		int intval = std::stoi(val,nullptr,16);
		unsigned char byte1 = (intval >> 16);
		unsigned char byte2 = ((intval & 65280) >> 8);
		unsigned char byte3 = (intval & 255);
		cout << "bytes" << (int)byte1 << (int)byte2 << (int)byte3  << endl;
		int loc = code;
		memory[code++] = byte3;
		memory[code++] = byte2;
		memory[code++] = byte1;
		return loc;
	}
	else if (!st_type.compare("RESB") || !st_type.compare("RESW"))
	{
		cout << "res" << endl;
		int bytes = std::stoi(val,nullptr,16);
		if (!st_type.compare("RESW")) bytes*=3;
		int loc = code;
		code+=bytes;
		return loc;
	}
	else if (!st_type.compare("BYTE"))
	{
		cout << "byte" << endl;
		unsigned char byte = byte_format(val);
		int loc = code;
		code++;
		return loc;
	}
}
void assembler::load_memory()
{

}
void assembler::clear_memory()
{
	for (int i=0; i<MEMORY_SIZE; i++) memory[i]=0xFF;
}
void assembler::assemble() 
{
	parse_file();
}

int main(int argc, char const *argv[])
{
	string filename = argv[1];
	assembler asmb(filename);
	asmb.assemble();
	return 0;
}

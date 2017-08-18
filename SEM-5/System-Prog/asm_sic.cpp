#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <random>
#include <iomanip>
#include "asm_sic.h"
#define MEMORY_SIZE 32768
using namespace std;

unsigned char memory[MEMORY_SIZE]; // model for the memory
std::map<std::string,std::string> op_tab;
void execute_code(string);
void operator_table()
{
	op_tab["ADD"] = "18";
	op_tab["SUB"] = "1C";
	op_tab["MUL"] = "20";
	op_tab["DIV"] = "24";
	op_tab["LDA"] = "00";
	op_tab["LDX"] = "04";
	op_tab["STA"] = "0C";
	op_tab["STX"] = "10";
	op_tab["COMP"] = "28";
	op_tab["TIX"] = "2C";
    op_tab["RSUB"] = "4C";
    op_tab["JSUB"] = "48";
	op_tab["JEQ"] = "30";
	op_tab["JGT"] = "34";
	op_tab["JLT"] = "38";
}
bool is_branch_instr(string instr) // check for branch instruction
{
	return (!instr.compare("JSUB") || !instr.compare("RSUB")  || !instr.compare("JEQ") || !instr.compare("JLT") || !instr.compare("JGT"));
}
assembler::assembler(string infile, string outfile):ip_file(infile),op_file(outfile)
{
	code=0;
	code_start=0;
	instr_end=0;
	operator_table();
	clear_memory();
}
unsigned char *assembler::byte_format(string byte_string)
{
	// byte string should be of the form F'XX' where F is the format (C,X,B) and XX is the value
	// e.g C'Z'; X'A2'; B'00011011'
	char beg_char = byte_string.at(0);
	unsigned char *bytearr;
	int len = byte_string.size();
	string buf = byte_string.substr(2,len-1);
	try
	{
		switch (beg_char)
		{
			case 'C': bytearr = new unsigned char[len-3];
					  for (int i = 0; i<len-3; i++)
					  {
						  bytearr[i] = (unsigned char)(buf[i]);
						  memory[code++] = bytearr[i];
					  }
					  break;
			case 'X': bytearr = new unsigned char[(len-3)/2];
					  for (int i=0; i<len-3; i+=2)
					  {
						  bytearr[i] = (unsigned char)(std::stoi(buf.substr(i,i+2)),nullptr,16);
						  memory[code++] = bytearr[i];
					  }
		}
	}
	catch ( ... )
	{
		cout << "Invalid byte format" << endl;
		return NULL;
	}
	return bytearr;
}
void assembler::parse_file()
{
	std::fstream in(ip_file,ios::in);
	std::string line; int lineno=0;
	std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 1024); // define the range
    code_start = distr(eng);
    code = code_start;
	while (!in.eof())
	{
		getline(in,line);
		int p=0; string word;
		int token=0;
		istringstream iss(line);
		std::string tokens[3];
		iss >> tokens[0] >> tokens[1] >> tokens[2];
		//cout << tokens[0] << "," << tokens[1] << "," << tokens[2] << endl;
		//cout << (label_table.find("SWAP") != label_table.end()) << "--oo" << endl;
		if (lineno==0 && !(tokens[0].compare("START")))
		{
			code_start = std::stoi (tokens[1],nullptr,16);
			code = code_start;
		}
		else if (op_tab.find(tokens[0]) != op_tab.end())
		{
			// operator encountered			
		//	cout << "--this is op" << endl;

			memory[code++] = std::stoi(op_tab.at(tokens[0]),nullptr,16);

			//printf ("hi%02x\n",memory[code-1]);
			// in SIC no immediate addressing
			if (!tokens[0].compare("RSUB"))
			{
				memory[code++] = 0; memory[code++] = 0;
			}
			else if (is_branch_instr(tokens[0]))
			{
				//cout << "--this is branch" << endl;
				if (label_table.find(tokens[1]) != label_table.end()) // previously occured
				{
					int jmploc = label_table[tokens[1]];
					memory[code++] = (jmploc & 255);
					memory[code++] = (jmploc >> 8);
				}
				else // not occured before. may be jump addr
				{
					//cout << "where occurs: " << code << endl;
					label_table[tokens[1]] = code++;
					code++;
					cout << label_table[tokens[1]] << "," << tokens[1] << endl;
				}
			}
			else
			{
				if (tokens[1].find(",") != std::string::npos) // index addr
				{
					//cout << "yes" << endl;
					if (tokens[1].substr(tokens[1].find(",")).compare(",X") == 0)
					{
						tokens[1] = tokens[1].substr(0,tokens[1].find(","));
						cout << tokens[1] << endl;
						memory[code+1] = 128;
					}
					else
					{
						cout << "ERROR" << endl;
					}
				}
				sym_tab[tokens[1]].push_back(code++);
				//cout << "pushed back" << endl;
				code++;
			}

			//for (int i=0; i<sym_tab[tokens[1]].size(); i++ ) cout << sym_tab[tokens[1]][i] << "-";
		}
		else if (sym_tab.find(tokens[0]) != sym_tab.end()) // if storage variable
		{
			//cout << "--this is var" << endl;
			//for (auto ele : sym_tab[tokens[0]]) cout << ele << ",";
			//cout << "shown" << endl;
			if (instr_end==0) {
				instr_end=code;
				//cout << "CODE: " << code;
			}
			int loc;
			if (op_tab.find(tokens[0]) == op_tab.end())
			{
				//cout << "symbol"  << tokens[1] << endl;
				loc = get_data_location(tokens[0],tokens[1],tokens[2]);
				unsigned char high, low;
				for (auto memloc : sym_tab[tokens[0]])
				{
					low = (loc & 255);
					high = (loc >> 8);
					memory[memloc] = low;
					memory[memloc+1] |= high;
				}
			}
		}
		else if (sym_tab.find(tokens[0]) == sym_tab.end()) // if not an operator and not an existing symbol
		{   // must be a label
			//cout << "--this is label" << endl;
			if (label_table.find(tokens[0]) != label_table.end())
			{
				//cout << "found here: " << code << "," << tokens[0] << "," << label_table[tokens[0]] << endl;
				memory[label_table[tokens[0]]] = (code & 255);
				memory[label_table[tokens[0]]+1] = ((code >> 8) & 255);
			}
			else
			{
				label_table[tokens[0]] = code;
			}
			if (op_tab.find(tokens[1]) == op_tab.end()) // not an operator
			{
				cout << "Invalid format" << endl;
			}
			else
			{
				if (!tokens[1].compare("RSUB"))
				{
					memory[code++] = 0; memory[code++] = 0;
				}
				else if (is_branch_instr(tokens[1]))
				{
					if (label_table.find(tokens[2]) != label_table.end()) // previously occured
					{
						int jmploc = label_table[tokens[2]];
						memory[code++] = (jmploc & 255);
						memory[code++] = (jmploc >> 8);
					}
					else // not occured before. may be jump addr
					{
						label_table[tokens[2]] = code++;
						code++;
						//code += 2;
					}
				}
				else
				{
					memory[code++] = std::stoi(op_tab.at(tokens[1]),nullptr,16);
					if (tokens[1].find(",") != std::string::npos) // index addr
					{
						if (tokens[1].substr(tokens[1].find(",")).compare("X") == 0)
						{
							tokens[1] = tokens[1].substr(tokens[1].find(","));
							memory[code+1] = 128;
						}
					}
					//else memory[code+1] = 0;
					sym_tab[tokens[2]].push_back(code++);
					code++;
					
				}
			}

		}
		lineno++;
	}
	//cout << "hi" << code_start << "," << code << (int)memory[code_start+1] << endl;
	for (int l=code_start; l<code; l++) cout << (int)memory[l] << " ";
	in.close();

}
int assembler::get_data_location(string name, string st_type="", string val="")
{ // allocate the variable to somewhere in memory
	if (!st_type.compare("WORD")) // allocate constant word
	{
		//cout << "word" << val << endl;
		int intval = std::stoi(val,nullptr,16);
		unsigned char byte1 = (intval >> 16);
		unsigned char byte2 = ((intval & 65280) >> 8);
		unsigned char byte3 = (intval & 255);
		//cout << "bytes" << (int)byte1 << (int)byte2 << (int)byte3  << endl;
		int loc = code;
		memory[code++] = byte3;
		memory[code++] = byte2;
		memory[code++] = byte1;
		return loc;
	}
	else if (!st_type.compare("RESB") || !st_type.compare("RESW"))
	{
		//cout << "res" << endl;
		int bytes = std::stoi(val,nullptr,16);
		if (!st_type.compare("RESW")) bytes*=3;
		int loc = code;
		code+=bytes;
		return loc;
	}
	else if (!st_type.compare("BYTE"))
	{
		//cout << "byte" << endl;
		int loc = code;
		unsigned char *bytes = byte_format(val);


		return loc;
	}
}
void assembler::dump_code()
{
	fstream outf(op_file,ios::out);
	outf << "H" << std::setw(4) << std::setfill('0') << std::hex << code_start << std::setw(4) << std::setfill('0') << std::hex << (instr_end - code_start) << std::setw(4) << std::setfill('0') << std::hex << (code-code_start) << endl;
	for (int i=code_start; i<code; i++)
	{
		outf << std::setw(2) << std::setfill('0') << std::hex << (int)(memory[i]) << endl;
	}
	outf.close();
}
void assembler::clear_memory()
{
	for (int i=0; i<MEMORY_SIZE; i++) memory[i]=0;
}
void assembler::assemble()
{
	parse_file();
	dump_code();
}

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>
#include <random>
#include <iomanip>
#define MEMORY_SIZE 32
using namespace std;

unsigned char memory[MEMORY_SIZE]; // model for the memory
map <string, string> op_tab;
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
bool is_branch_instr(string instr)
{
	return (!instr.compare("JSUB") || !instr.compare("RSUB")  || !instr.compare("JEQ") || !instr.compare("JLT") || !instr.compare("JGT"));
}
class assembler
{
	string ip_file, op_file;
	int code_start, code, instr_end;
	map <string, std::vector<int> > sym_tab ;;
	map <string, int> label_table;
	void parse_file();
	int get_data_location(string,string,string);
	unsigned char *byte_format(string);
	void dump_code();
	public:
	assembler(string infile, string outfile):ip_file(infile),op_file(outfile)
	{
		//ACC=X=L=PC=0;
		code=0;
		code_start=0;
		instr_end=0;
		operator_table();
		clear_memory();
	}
	void clear_memory();
	void load_memory();
	void assemble();
};
unsigned char *assembler::byte_format(string byte_string)
{
	// byte string should be of the form F'XX' where F is the format (C,X,B) and XX is the value
	// e.g C'Z'; X'A2'; B'00011011'
	char beg_char = byte_string.at(0);
	unsigned char *bytearr;
	int len = byte_string.size();
	string buf = byte_string.substr(2,len-1); // extract the value part
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
					  //code+=(len-3);
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
			if (is_branch_instr(tokens[0]))
			{
				int jmploc = label_table[tokens[1]];
				memory[code++] = (jmploc & 255);
				memory[code++] = (jmploc >> 8);
			}
			else
			{
				sym_tab[tokens[1]].push_back(code++);
				code++;
			}

			//sym_tab[tokens[1]].push_back(code++);
			for (int i=0; i<sym_tab[tokens[1]].size(); i++ ) cout << sym_tab[tokens[1]][i] << "-";
		}
		else if (sym_tab.find(tokens[0]) != sym_tab.end()) // if storage variable
		{
			if (instr_end==0) {
				instr_end=code;
				cout << "CODE: " << code;
			}
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
		{   // must be a label
			label_table[tokens[0]] = code;
			if (op_tab.find(tokens[1]) == op_tab.end()) // not an operator
			{
				cout << "Invalid format" << endl;
			}
			else
			{
				if (is_branch_instr(tokens[1]))
				{
					int jmploc = label_table[tokens[2]];
					memory[code++] = (jmploc & 255);
					memory[code++] = (jmploc >> 8);
				}
				else
				{
					memory[code++] = std::stoi(op_tab.at(tokens[1]),nullptr,16);
					sym_tab[tokens[2]].push_back(code++);
					code++;
				}
			}

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
void assembler::load_memory()
{
	
}
void assembler::clear_memory()
{
	cout << "CLEAR" << endl;
	for (int i=0; i<MEMORY_SIZE; i++) memory[i]=255;
}
void assembler::assemble()
{
	parse_file();
	dump_code();
}
void execute_code(string codefile)
{
	int ACC=0, X=0, L=0, PC=0; // SW=0;
	int CC=0; // replace with SW
	fstream cdf(codefile,ios::in);
	string head;
	cdf >> head;
	cout << head << endl;
	cout << head.substr(1,4) << endl;
	int start = std::stoi(head.substr(1,4),nullptr,16);
	int instr_size = std::stoi(head.substr(5,4),nullptr,16);
	int code_size = std::stoi(head.substr(9,4),nullptr,16); 
	cout << start << "," << instr_size << "," << code_size << endl;
	for (int i=start; i<start+code_size+5; i++) cout << (int)memory[i] << " ";
	cout << endl;
	for (PC=start; PC<start+instr_size;)
	{
		// do exec here
		int code = memory[PC];
		cout << "Code: " << code << "	";
		int loc, val;
		switch(code)
		{
			case 0: //LDA
					loc = memory[PC+1] + (int)(memory[PC+2] << 8);
					val = memory[loc] + (int)(memory[loc+1] << 8) + (int)(memory[loc+2] << 16);
					ACC = val;
					cout << "0" << "," << loc << "," << val << endl;
					break;
			case 4: //LDX
					loc = memory[PC+1] + (int)(memory[PC+2] << 8);
					val = memory[loc] + (int)(memory[loc+1] << 8) + (int)(memory[loc+2] << 16);
					X = val;
					break;
			case 12: //STA
					 loc = memory[PC+1] + (int)(memory[PC+2] << 8);
					 memory[loc] = (ACC & 255);
					 memory[loc+1] = ((ACC & 65280) >> 8);
					 memory[loc+2] = (ACC >> 16);
					 break;
			case 16: //STX
					 loc = memory[PC+1] + (int)(memory[PC+2] << 8);
					 memory[loc] = (X & 255);
					 memory[loc+1] = ((X & 65280) >> 8);
					 memory[loc+2] = (X >> 16);
					 break;
			case 24: //ADD
					 loc = memory[PC+1] + (int)(memory[PC+2] << 8);
					 val = memory[loc] + (int)(memory[loc+1] << 8) + (int)(memory[loc+2] << 16);
					 ACC += val;
					 if (ACC>16777215)
					 {
					 	//status word will show carry
					 	ACC = (ACC & 16777215);
					 }
					 break;
			case 28: //SUB
					 loc = memory[PC+1] + (int)(memory[PC+2] << 8);
					 val = memory[loc] + (int)(memory[loc+1] << 8) + (int)(memory[loc+2] << 16);
					 ACC -= val;
					 break;
			case 40: //COMP
					 loc = memory[PC+1] + (int)(memory[PC+2] << 8);
					 val = memory[loc] + (int)(memory[loc+1] << 8) + (int)(memory[loc+2] << 16);
					 if (val == ACC) CC = 0;
					 else if (ACC > val) CC = 1;
					 else CC = 2;
					 break;
			case 48: //JEQ
					 if (CC==0)
					 {
					 	loc = memory[PC+1] + (int)(memory[PC+2] << 8);
					 	PC = loc-3;
					 }
					 break;
			case 52: //JGT
					 if (CC==1)
					 {
					 	loc = memory[PC+1] + (int)(memory[PC+2] << 8);
					 	PC = loc-3;
					 }
					 break;
			case 56: //JLT
					 if (CC==2)
					 {
					 	loc = memory[PC+1] + (int)(memory[PC+2] << 8);
					 	PC = loc-3;
					 }
					 break;
		}
		PC+=3;	
	}
	for (int i=start; i<start+code_size+5; i++) cout << (int)memory[i] << " ";
	cout << endl;
	cdf.close();
	cout << ACC << "-" << X << "-" << L << "-" << PC << endl;
}
int main(int argc, char const *argv[])
{
	string filename = argv[1];
	string dump = argv[2];
	//string filename, dump;
	//cout << "Enter input file: ";
	//cin >> filename;
	//cout << "Enter output file: ";
	//cin >> dump;
	assembler asmb(filename,dump);
	asmb.assemble();
	execute_code(dump);
	return 0;
}

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include "sicxe_exec.h"
#define MEMORY_SIZE 32768
using namespace std;


void execute_code(std::string codefile)
{
	int memory[MEMORY_SIZE];
	int ACC=0, X=0, L=0, PC=0; // SW=0;
	int CC=0; // replace with SW
	std::fstream cdf(codefile,ios::in);
	std::string head;
	cdf >> head;
	//cout << head << endl;
	//cout << head.substr(1,4) << endl;
	int start = std::stoi(head.substr(1,4),nullptr,16);
	int instr_size = std::stoi(head.substr(5,4),nullptr,16);
	int code_size = std::stoi(head.substr(9,4),nullptr,16); 
	int end = std::stoi(head.substr(13,4),nullptr,16); 
	//cout << start << "," << instr_size << "," << code_size << endl;
	//for (int i=start; i<start+code_size+5; i++) cout << (int)memory[i] << " ";
	//cout << endl;
	/* load memory */
	string byte;
	for (int i=start; i<start+code_size; i++)
	{
		cdf >> byte;
		memory[i] = std::stoi(byte,nullptr,16);
	}
	for (PC=start; ;PC+=3)
	{
		// do exec here
		int code = memory[PC];
		//cout << "Code: " << code << "\t";
		int loc, val, high;
		//cout << ACC << "-" << X << "-" << L << "-" << PC << endl;
		switch(code)
		{

			case 0: //LDA
					high = (int)(memory[PC+2]);
					//cout << "high: " << high << endl;
					if ((high & 128)) high = ((high & 127) << 8) + X;
					else high = (high & 127) << 8;
					loc = memory[PC+1] + high;
					//cout << "0" << "," << loc << "," << val << endl;
					val = memory[loc] + (int)(memory[loc+1] << 8) + (int)(memory[loc+2] << 16);
					ACC = val;
					//cout << "0" << "," << loc << "," << val << endl;
					break;
			case 4: //LDX
					high = (int)(memory[PC+2]);
					if ((high & 128)) high = ((high & 127) << 8) + X;
					else high = (high & 127) << 8;
					loc = memory[PC+1] + high;
					val = memory[loc] + (int)(memory[loc+1] << 8) + (int)(memory[loc+2] << 16);
					X = val;
					break;
			case 12: //STA
					 high = (int)(memory[PC+2]);
					 if ((high & 128)) high = ((high & 127) << 8) + X;
					 else high = (high & 127) << 8;
					 loc = memory[PC+1] + high;
					 memory[loc] = (ACC & 255);
					 memory[loc+1] = ((ACC & 65280) >> 8);
					 memory[loc+2] = (ACC >> 16);
					 break;
			case 16: //STX
					 high = (int)(memory[PC+2]);
					 if ((high & 128)) high = ((high & 127) << 8) + X;
					 else high = (high & 127) << 8;
					 loc = memory[PC+1] + high;
					 memory[loc] = (X & 255);
					 memory[loc+1] = ((X & 65280) >> 8);
					 memory[loc+2] = (X >> 16);
					 break;
			case 24: //ADD
					 high = (int)(memory[PC+2]);
					 if ((high & 128)) high = ((high & 127) << 8) + X;
					 else high = (high & 127) << 8;
					 loc = memory[PC+1] + high;
					 val = memory[loc] + (int)(memory[loc+1] << 8) + (int)(memory[loc+2] << 16);
					 ACC += val;
					 ACC &= 16777215;
					 break;
			case 28: //SUB
					 high = (int)(memory[PC+2]);
					 if ((high & 128)) high = ((high & 127) << 8) + X;
					 else high = (high & 127) << 8;
					 loc = memory[PC+1] + high;
					 val = memory[loc] + (int)(memory[loc+1] << 8) + (int)(memory[loc+2] << 16);
					 ACC -= val;
					 ACC &= 16777215;
					 break;
			case 32: //MUL
					 high = (int)(memory[PC+2]);
					 if ((high & 128)) high = ((high & 127) << 8) + X;
					 else high = (high & 127) << 8;
					 loc = memory[PC+1] + high;
					 val = memory[loc] + (int)(memory[loc+1] << 8) + (int)(memory[loc+2] << 16);
					 ACC *= val;
					 ACC &= 16777215;
					 break;
			case 36: high = (int)(memory[PC+2]);
					 if ((high & 128)) high = ((high & 127) << 8) + X;
					 else high = (high & 127) << 8;
					 loc = memory[PC+1] + high;
					 val = memory[loc] + (int)(memory[loc+1] << 8) + (int)(memory[loc+2] << 16);
					 ACC /= val;
					 ACC &= 16777215;
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
			case 72: //JSUB
					 loc = memory[PC+1] + (int)(memory[PC+2] << 8);
					 L = PC;
					 PC = loc - 3;
					 break;
			case 76: //RSUB
					 PC = L;
					 break;

		}
		if (PC+3 == end) break;
		//PC+=3;	
	}
	std::cout << "MEMORY: " << endl << "------------------------------------------------------------------------------------------" << endl;
	for (int i=start; i<start+code_size; i++) 
	{
		cout << std::setw(4) << std::setfill('0') << std::hex << i << " - " << std::setw(4) << std::setfill('0') << std::hex << (int)memory[i] << endl;
	}
	cout << endl;
	cdf.close();
	std::cout << endl << "REGISTER STATUS: " << endl << "---------------------------------------------" << endl;
	std::cout << "ACCUMULATOR: " << std::dec << ACC << endl << "INDEX REGISTER: " << X << endl << "L REGISTER: " << L << endl << "PROGRAM COUNTER:" << PC << endl;
}
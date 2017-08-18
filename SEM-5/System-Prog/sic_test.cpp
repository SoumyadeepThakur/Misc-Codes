#include <iostream>
#include <cstdlib>

#include "asm_sic.h"
#include "sicxe_exec.h"
using namespace std;

/* driver program to test */
int main(int argc, char const *argv[])
{
	string filename = argv[1];
	string dump = argv[2];
	assembler asmb(filename,dump);
	asmb.assemble();
	cout << "ASSEMBLED" << endl;
	execute_code(dump);
	return 0;
}
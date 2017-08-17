/*
AUTHOR: SOUMYADEEP THAKUR
DATE OF CREATION: 17 AUG 2017

*/

/* guard */
#ifndef __ASM_SIC_H_INCLUDED__
#define __ASM_SIC_H_INCLUDED__

#include <vector>
#include <map>

#ifndef __STRING_INCL__
#define __STRING_INCL__

#include <string>

#endif

#endif

/*util function to check for branches */
bool is_branch_instr(std::string);

/*class definition */
class assembler
{
	std::string ip_file, op_file;
	int code_start, code, instr_end;
	std::map <std::string, std::vector<int> > sym_tab ;
	std::map <std::string, int> label_table;

	void parse_file();
	int get_data_location(std::string,std::string,std::string);
	unsigned char *byte_format(std::string);
	void dump_code();

	public:
	assembler(std::string,std::string);
	void clear_memory();
	void load_memory();
	void assemble();

};

#endif

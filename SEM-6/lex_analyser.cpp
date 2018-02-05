#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
using namespace std;

class token_entry;
//enum token_type = {arithop, relop, assignop, identifier, number};
std::unordered_set<std::string> keyword;
std::vector<token_entry> token_table;

class token_entry
{
	public:
	std::string tokentype, lexeme;
	int row, col;
	token_entry(std::string tok_type, std::string lex, int row_no, int col_no):tokentype{tok_type}, lexeme{lex}, row{row_no}, col{col_no} {};

};
bool is_valid_identifier(std::string id)
{
	if (!(id[0] == '_' || (id[0] <= 'Z' && id[0] >= 'A') || (id[0] <= 'z' && id[0] >= 'a'))) return false;
	id.erase(id.begin());
	for (char& c : id)
	{
		if (!(c == '_' || (c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a') || (c <= '9' && c >= '0'))) return false;
	}
	return true;
}
bool is_keyword(std::string token)
{
	if (keyword.find(token) != keyword.end())
		return true;
	return false;
}
bool is_number(std::string token)
{
	for (char& c : token)
	{
		if (c < '0' || c > '9') return false;
	}
	return true;
}
void populate_keyword()
{
	std::ifstream keyfile;
	keyfile.open("key.txt", ios::in);
	std::string keywd;
	keyfile >> keywd;
	keyword.insert(keywd);
	keyfile.close();
}
int get_token_type(std::string token)
{
	
}

void tokenize(std::vector<std::string>& tokens, std::string& line)
{
	std::string delimiter = " +-*/<>=;,(){}";
	int last = 0, len = 0;
	line = line + " ";
	for (int i = 0; i < line.length(); i++)
	{
		char c = line[i];
		if (delimiter.find(c) != std::string::npos) // c is a delimeter
		{
			//tokens.push_back(line.substr(last, len));
			cout << "Delim: " << c << endl;
			tokens.push_back((""+c));
			if (len)
			{
				cout << line.substr(last, len) << endl;
				tokens.push_back(line.substr(last, len));
			}
			last = i+1;
			len=0;
		}
		else
		{
			len++;
		}
	}
}
void process_code(std::string code_file_name)
{
	std::ifstream code_file(code_file_name, std::ifstream::in);
	std::string code_line;
	std::vector<string> tokens;
	while (code_file.eof())
	{
		code_file >> code_line;
		tokenize(tokens, code_line);
	}
}
int main(int argc, char const **argv)
{
	// vector<xyz>().swap(myvector) to clear myvector
	std::vector<std::string> tokens;
	std::string line;
	//cin >> line;
	getline(cin, line);
	cout << line << endl;
	tokenize(tokens, line);
	for (std::string& s : tokens)
		cout << s << endl;
	return 0;
}

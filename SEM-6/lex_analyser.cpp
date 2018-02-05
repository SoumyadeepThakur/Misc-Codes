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
			//cout << "Delim: " << c << endl;
			if (len)
			{
				//cout << "Token: " << line.substr(last, len) << endl;
				tokens.push_back(line.substr(last, len));
			}
			if (c!=' ') 
			{
				//cout << "delim pushed" << endl;
				tokens.push_back(std::string(1,c));
			}
			last = i+1;
			len=0;
		}
		else
		{
			len++;
		}
	}
	for (std::string& s : tokens)
		cout << s << ",";
	cout << endl;
}
void process_code(std::string code_file_name)
{
	std::fstream code_file(code_file_name, ios::in);
	std::string code_line;
	std::vector<string> tokens;
	cout << "Hi" << endl;
	//code_file >> code_line;
	//cout << code_line;
	while (!code_file.eof())
	{
		std::string tokentype;
		getline(code_file, code_line);
		cout << code_line << endl;
		tokenize(tokens, code_line);
		for (std::string& token : tokens)
		{
			tokentype = get_token_type(token);
			// add token to table
			//token_entry t_ent(tokentype, token, )

		}
		std::vector<std::string>().swap(tokens); // free vector memory
	}
}
int main(int argc, char const **argv)
{
	process_code("code.txt");
	// vector<xyz>().swap(myvector) to clear myvector
	//std::vector<std::string> tokens;
	//std::string line;
	//cin >> line;
	//getline(cin, line);
	//cout << line << endl;
	//tokenize(tokens, line);
	//for (std::string& s : tokens)
	//	cout << s << ",";
	//cout << endl;
	return 0;
}

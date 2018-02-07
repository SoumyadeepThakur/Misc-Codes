#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <iomanip>

// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}
using namespace std;

class token_entry;
enum token_type {INVALID, KEYWORD, IDENTIFIER, LITERAL, ARITHOP, RELOP, ASSIGNOP, PUNCTUATION};
std::unordered_set<std::string> keyword;
std::vector<token_entry> token_table;

class token_entry
{
	public:
	std::string lexeme;
	token_type tokentype;
	int row, col;
	token_entry(token_type tok_type, std::string lex, int row_no, int col_no):tokentype{tok_type}, lexeme{lex}, row{row_no}, col{col_no} {};
};
void trim_left_copy(std::string& s, const std::string& delimiters = " \f\n\r\t\v" )
{
	s.erase(s.find_first_not_of( delimiters));
}
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
		if (c != '.' && (c < '0' || c > '9')) return false;
	}
	return true;
}
bool is_string_or_char(std::string token)
{
	if (token[0] == '\'' && token[token.length()-1] == '\'' && token.length() == 3) return true;
	if (token[0] == '"' && token[token.length()-1] == '"') return true;
	return false;

}
bool is_arith_op(std::string token)
{
	if (token.length() == 1)
	{
		char c = token[0];
		if (c=='+' || c=='-' || c=='*' || c=='/')
			return true;
	}
	return false;
}
void populate_keyword()
{
	std::ifstream keyfile;
	keyfile.open("key.txt", ios::in);
	std::string keywd;
	while (!keyfile.eof())
	{
		keyfile >> keywd;
		keyword.insert(keywd);
	}
	//cout << "Keywords: " << endl;
	//for (std::string keyw: keyword) cout << keyw << " ";
	//cout << endl;
	keyfile.close();
}
token_type get_token_type(std::string token)
{
	int len = token.length();
	
	if (is_keyword(token))
		return KEYWORD;
	if (is_number(token) || is_string_or_char(token))
		return LITERAL;
	if (is_valid_identifier(token))
		return IDENTIFIER;
	if (token.length() == 1)
	{
		char c = token[0];
		if (c=='=') return ASSIGNOP;
		else if (c=='+' || c=='-' || c=='*' || c=='/') return ARITHOP;
		else if (c=='>' || c=='<') return RELOP;
		else if (c==';' || c== ',' || c=='(' || c== ')' || c=='{' || c== '}') return PUNCTUATION;
	}
	return INVALID;
		
}
std::string to_token_type_str(token_type tokentype)
{
	switch(tokentype)
	{
		case KEYWORD: return "KEYWORD";
		case IDENTIFIER: return  "IDENTIFIER";
		case LITERAL: return "LITERAL";
		case ARITHOP: return  "ARITHOP";
		case RELOP: return "RELOP";
		case ASSIGNOP: return "ASSIGNOP";
		case PUNCTUATION: return "PUNCTUATION";
		default: return "INVALID";
	}
}

bool display_table()
{
	int tokid=1; bool error=false;
	cout << "Token Table: " << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "TOKEN ID" << std::setw(20) <<  "TOKEN TYPE" << std::setw(20) <<  "LEXEME" << std::setw(20) << "POSITION" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	for (token_entry& t : token_table)
	{
		//std::string toktype = get_token_type(t.tokentype);
		if (t.tokentype == -1) error = true;
		cout   << tokid << " " <<  std::setw(20) << to_token_type_str(t.tokentype) << std::setw(20) << t.lexeme << std::setw(20) << "(" << t.row << "," << t.col << ")" << endl;
		tokid++;
	}
	return error;
}
void tokenize(std::string& line, std::vector<std::string>& tokens, std::vector<int>& col_no)
{
	std::string delimiter = " +-*/<>=;,(){}";
	int last = 0, len = 0;
	//trim_left_copy(line); // handle left tabs here pls
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
				col_no.push_back(last);
			}
			if (c!=' ') 
			{
				//cout << "delim pushed" << endl;
				tokens.push_back(std::string(1,c));
				col_no.push_back(i);
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
	std::vector<int> cols;
	int line_no = 1;
	cout << "Hi" << endl;
	//code_file >> code_line;
	//cout << code_line;
	populate_keyword();
	while (!code_file.eof())
	{
		token_type tokentype;
		getline(code_file, code_line);
		code_line = ltrim(code_line);
		cout << code_line << endl;
		tokenize(code_line, tokens, cols);
		for (std::string& token : tokens)
		{
			tokentype = get_token_type(token);
			// add token to table
			cout << "Tokentype: " << tokentype;
			token_entry t_ent(tokentype, token, line_no, cols.front()+1);
			cols.erase(cols.begin());
			token_table.push_back(t_ent);
		}

		std::vector<std::string>().swap(tokens); // free vector memory
		line_no++;
	}
	if(display_table())
		cout << "Error in lex analysis" << endl;
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
	//cout << "Token Table: " << endl;
	//for (token_entry& t : token_table)
	//{
	//	cout << t.tokentype << " - " << t.lexeme << " - " << t.row << " - " << t.col << endl;
	//}
	return 0;
}

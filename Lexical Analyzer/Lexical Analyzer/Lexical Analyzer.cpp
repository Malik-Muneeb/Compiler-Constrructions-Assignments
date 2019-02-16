#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<iterator>
using namespace std;

//cs= current state, f= forward pointer, ls= lexeme start,
//iw =index white last final state visited, lf= last final state visited
//line=line number
int cs = 0, f = 0, ls = 0, iw = -1, lf = -1, line = 0;

const int totalKey = 61;
string keywords[totalKey] = { "Asm", "auto", "bool", "break", "case" ,"catch", "char", "class",
"const", "cast", "continue", "default",	"delete",	"do",	"double",
"else", "enum", "dynamic_cast", "extern", "false",	"float",  "for",
"union", "unsigned", "using", "friend", "goto",	"if", "inline",	"int",
"long",	"mutable",	"virtual",	"namespace", "new",	"operator",  "private",
"protected", "public",	"register",	"void", "reinterpret_cast",	"return",
"short", "signed",	"sizeof", "static",	"static_cast",	"volatile",	"struct",
"switch", "template",	"this",	"throw", "true", "try", "typedef",	"typeid",
"unsigned",	"wchar_t",	"while" };

//true means we can traverse that state
bool states[7][7] = { { true, true, true, true, false, false, true },
{ false, false, false, false, false, false, false },
{ false, false, true, false, false, false, false },
{ false, false, false, true, true, false, false },
{ false, false, false, false, false, true, false },
{ false, false, false, false, false, true, false },
{ false, false, false, false, false, false, false, } };

//use to check path from cs to particular state
int start = 0, eq = 1, id = 2, integer = 3, point = 4, real = 5, semicolon = 6;
string token[7] = { "", "=", "ID", "INT", "", "REAL", ";" };	//Token names
string error = "";
map <string, string> symbol;									//used for Symbol Table
void readFile();
void identifyLexeme(string buffer);
void ungetch(string buffer);
void insertInTable(string lexeme);
void printTable();		
void printError();

int main()
{
	readFile();
	cout << "\nSymbol Table: \n";
	printTable();
	printError();
	return 0;
}

void readFile()				//read data from file
{
	ifstream read;
	read.open("input.txt");
	if (!read)
		cout << "Error opening file...\n";
	string buffer;
	while (getline(read, buffer))
	{
		cout << "Line no: " << line + 1 << "\t" << buffer << endl;
		//reset pointers after processing each line
		f = 0, cs = 0, ls = 0, iw = -1, lf = -1, line = line + 1;
		identifyLexeme(buffer);
	}

}

void identifyLexeme(string buffer)			//identify lexemes from input
{
	while (buffer[f] != NULL)
	{
		if (isspace(buffer[f]))
		{
			if (states[cs][start])
			{
				cs = 0;
				ls = ls + 1;
			}
			else
				ungetch(buffer);
		}
		else if (buffer[f] == '=')
		{
			if (states[cs][eq])
			{
				cs = eq;
				lf = cs;
			}
			else
				ungetch(buffer);
		}
		else if (buffer[f] == ';')
		{
			if (states[cs][semicolon])
			{
				cs = semicolon;
				lf = cs;
			}
			else
				ungetch(buffer);
		}
		else if (buffer[f] == '\\' && buffer[f + 1] == 'n')
		{
			if (states[cs][start])
			{
				line = line + 1;
				f = f + 1;
				iw = f - 1;
				ls = ls + 2;
			}
			else
				ungetch(buffer);
		}
		else if (buffer[f] == '.')
		{
			if (states[cs][point])
				cs = point;
			else if (lf == -1)
			{
				ls = ls + 1;
				cs = 0;
				error = error + " " + char(line) + " " + buffer[f];
			}
			else
			{
				cs = integer;
				iw = iw - 1;
				ungetch(buffer);
				f = f - 1;
			}
		}
		else if (isalpha(buffer[f]))
		{
			if (states[cs][id])
			{
				cs = id;
				lf = cs;
			}
			else
				ungetch(buffer);
		}
		else if (isdigit(buffer[f]))
		{
			if (states[cs][integer])
			{
				cs = integer;
				lf = cs;
			}
			else if (states[cs][real])
			{
				cs = real;
				lf = cs;
			}
		}
		else
		{
			bool isUngetch = false;
			if (lf != -1)
			{
				ungetch(buffer);
				isUngetch = true;
			}
			if (!isUngetch)
			{
				ls = ls + 1;
				error = error + " " + char(line) + " " + buffer[f];
			}
		}

		f = f + 1;
		iw = f - 1;
	}

	if (lf != -1)			//for last lexeme of each line
		ungetch(buffer);

}

void ungetch(string buffer)
{
	f = f - 1;
	if (lf != -1)
	{
		char* ch = new char[iw - ls];
		int j = 0;
		for (int i = ls; i <= iw; i++)
		{
			ch[j] = buffer[i];
			j++;
		}
		ch[j] = '\0';

		string lexeme(ch);
		insertInTable(lexeme);
	}
}

void insertInTable(string lexeme)
{
	bool isLexeme = true;
	for (int i = 0; i < totalKey && isLexeme; i++)
	{
		if (keywords[i] == lexeme)
			isLexeme = false;
	}

	if (isLexeme)
		symbol.insert(pair<string, string>(lexeme, token[cs]));
	else
		symbol.insert(pair<string, string>(lexeme, "KEYWORD"));
	lf = -1;
	ls = iw + 1;
	iw = -1;
	cs = 0;
}

void printTable()				//print Symbol Table
{
	map <string, string> ::iterator itr;
	cout << "\tLexeme\tToken\n";
	for (itr = symbol.begin(); itr != symbol.end(); ++itr)
	{
		cout << '\t' << itr->first
			<< '\t' << itr->second << '\n';
	}
	cout << endl;
}

void printError()		//Print errors and their line numbers
{
	if (error != "")
	{
		cout << "\nError Table:\n";
		bool isLine = true;
		cout << "\tLine#\tCharacter\n";
		for (int i = 1; i < error.length(); i = i + 2)
		{
			if (isLine)
			{
				cout << "\t" << int(error[i]) << " ";
				isLine = false;
			}
			else
			{
				cout << "\t" << char(error[i]) << "\n";
				isLine = true;
			}
		}

	}
}
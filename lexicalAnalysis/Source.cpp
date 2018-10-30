#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <algorithm>

#define MAX_LEN 1000
using namespace std;
int current_position = 0; // record current reading position
const string backspace = " ";
const string enter = "\n";
const string keyword[] = {
	"auto", "double", "int", "struct", "break", "else", "long", "switch",
	"case", "enum", "register", "typedef", "char", "extern", "return", "union",
	"const", "float", "short", "unsigned", "continue", "for", "signed", "void",
	"default", "goto", "sizeof", "volatile", "do", "if", "while", "static"
};
const string symbol[] = {
	"<", ">", "!=", ">=", "<=", "==", ",", ";", "(", ")", "{", "}", "+", "-", "*", "/", "=", "++", "--"
};
//存放文件取出的字符
string letter[MAX_LEN];
//将字符转换为单词
string words[MAX_LEN];
int length; //保存程序中字符的数目
int num;

void printFile(FILE* file)
{
	if (file == nullptr)
		printf("file not exist");

	char ch = (char)fgetc(file);
	while (ch != EOF)
	{
		putchar(ch);
		ch = (char)fgetc(file);
	}
	fclose(file);
}

bool isLetter(char str)
{
	return (str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'z');
}

bool isDigit(char s)
{
	return (s >= '0' && s <= '9');
}

bool isId(string s)
{
	if (isLetter(s[0]))
	{
		for (auto i = 1; i < s.length(); ++i)
		{
			if (!isLetter(s[i]) && !isDigit(s[i]) && s[i] != '_')
			{
				return false;
			}
		}
	}
	return true;
}

bool isKeyword(string s)
{
	auto keyword_num = sizeof(keyword) / sizeof(keyword[0]);
	for (int i = 0; i < keyword_num; ++i)
	{
		if (!keyword[i].compare(s))
		{
			return true;
		}
	}
	return false;
}

bool isOperator(string str)
{
	return false;
}

void isInt(const string& str, int& i)
{
	for (; i < str.length(); ++i)
	{
		if (isDigit(str[i]))
			continue;
		else
			return;
	}
}


int typeofWord(string str)
{
	if ((str >= "a" && str <= "z") || (str >= "A" && str <= "z"))
		return 1; //letter
	if (str >= "0" && str <= "9")
		return 2; //num
	if (str == ">" || str == "=" || str == "<" || str == "!" || str == "," || str == ";" || str == "(" || str == ")" ||
		str == "{" || str == "}"
		|| str == "+" || str == "-" || str == "*" || str == "/")
		return 3; // form
	// if (!str.compare(backspace))
	// 	return 0;
}

bool isConstant(string str)
{
	auto i = 0;
	isInt(str, i);
	if (i != 0)
	{
		if (str[i] == '.')
		{
			i++;
			isInt(str, i);
			if (str[i] == 'E')
			{
				i++;
				if (str[i] == '+' || str[i] == '-')
				{
					i++;
					isInt(str, i);
					return true;
				}
			}
		}
		if (str[i] == 'E')
		{
			i++;
			if (str[i] == '+' || str[i] == '-')
			{
				i++;
				isInt(str, i);
				return true;
			}
		}
		if (typeofWord(letter[i]) == 3)
		{
			i++;
			return true;
		}
	}


	return false;
}

bool isSymbol(string str)
{
	auto symbol_num = sizeof(symbol) / sizeof(symbol[0]);
	for (auto i = 0; i < symbol_num; ++i)
	{
		if (!symbol[i].compare(str))
		{
			return true;
		}
	}
	return false;
}

string identifyWord(string str, int& pos)
{
	pos += 1;
	while (letter[pos].compare(backspace) && typeofWord(letter[pos]) != 3)
	{
		str.append(letter[pos]);
		pos++;
	}
	if (!letter[pos].compare(backspace))
	{
		pos++;
	}
	return str;
}

string identifyNum(string str, int& pos)
{
	pos += 1;
	while (typeofWord(letter[pos]) == 2 || letter[pos] == "." || letter[pos] == "E" || letter[pos] == "+" || letter[pos]
		== "-")
	{
		str.append(letter[pos]);
		pos++;
	}
	return str;
}

string identifySym(string str, int& pos)
{
	pos += 1;
	if (!letter[pos].compare(backspace) && typeofWord(letter[pos]) == 3)
	{
		// pos++;
		auto first = letter[pos - 1];
		auto second = letter[pos];
		if ((second == "=" && ((first == "<" || first == ">" || first == "=" || first == "!")) || (second == first && (
			first == "+" || first == "-"))));
		str.append(letter[pos]);
	}
	return str;
}

void printRes(string str, string res)
{
	cout << "<" << str << ":" << res << ">" << endl;
}

void getWord()
{
	string word;
	for (current_position = 0; current_position < sizeof(letter) / sizeof(letter[0]);)
	{
		if (backspace.compare(letter[current_position]) && enter.compare(letter[current_position]))
		{
			auto type = typeofWord(letter[current_position]);
			switch (type)
			{
			case 1:
				{
					word = identifyWord(letter[current_position], current_position);
					if (isKeyword(word))
					{
						printRes(word, "keyword");
						break;
					}
					else if (isId(word))
					{
						printRes(word, "id");
					}
					break;
				}
			case 2:
				{
					word = identifyNum(letter[current_position], current_position);
					if (isConstant(word))
						printRes(word, "constant");
					break;
				}
			case 3:
				{
					word = identifySym(letter[current_position], current_position);
					if (isSymbol(word))
						printRes(word, "symbol");
					break;
				}
			default:
				{
				}
			}
		}
		else
			current_position++;
	}
}

void read_file(ifstream& example_file)
{
	assert(example_file.is_open());
	char c;
	auto length = 0;
	example_file >> noskipws;

	while (!example_file.eof())
	{
		example_file >> c;
		// if (c != ' ')
		// {
		letter[length] = c;
		length++;
		// }
	}
	getWord();
}

int main()
{
	FILE* file = nullptr;
	char buff[255];

	ifstream example_file("prog.txt");
	read_file(example_file);

	// cout << isLetter('s');

	// for (auto i = 0; i < length; ++i)
	// {
	// 	cout << letter[i];
	// }
	// cout << isConstant("46E-8");
	// cout << isKeyword("int");
	// cout << isSymbol("2+");
	system("pause");
	return 0;
}

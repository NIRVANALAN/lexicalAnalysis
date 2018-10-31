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
const string preprocess = "#";
const string keyword[] = {
	"auto", "double", "int", "struct", "break", "else", "long", "switch",
	"case", "enum", "register", "typedef", "char", "extern", "return", "union",
	"const", "float", "short", "unsigned", "continue", "for", "signed", "void",
	"default", "goto", "sizeof", "volatile", "do", "if", "while", "static"
};
const string symbol[] = {
	"<", ">", "!=", ">=", "<=", "==", ",", ";", "(", ")", "{", "}", "+", "-", "*", "/", "=", "++", "--", "\"","[","]","'"
};
auto line_num = 0;
auto keyword_num = 0;
auto symbol_num = 0;
auto id_num = 0;
auto string_num = 0;
auto err_flag = 0;
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
	return (str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z');
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
		{
			// i++;
			continue;
		}
		else
			return;
	}
}

int typeofWord(string str)
{
	if ((str >= "a" && str <= "z") || (str >= "A" && str <= "Z"))
		return 1; //letter
	if (str >= "0" && str <= "9")
		return 2; //num
	if (str == ">" || str == "=" || str == "<" || str == "!" || str == "," || str == ";" || str == "(" || str == ")" ||
		str == "{" || str == "}"
		|| str == "+" || str == "-" || str == "*" || str == "/" || str == "[" || str == "]"||str=="'")
		return 3; // form
	if (str == "\"")
		return 4;
	if (str == "#")
		return 5;
	// if (!str.compare(backspace))
	// 	return 0;
}

bool isConstant(string str)
{
	auto i = 0;
	isInt(str, i);
	if (i == str.length())
		return true;
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
	while (letter[pos].compare(backspace) && typeofWord(letter[pos]) != 3 && letter[pos].compare(enter))
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

bool endLine(int pos)
{
	return false;
}

string identifySym(string str, int& pos)
{
	pos += 1;
	auto first = letter[pos - 1];
	auto second = letter[pos];
	if (second.compare(backspace) && typeofWord(second) == 3)
	{
		// for annotation
		if (first == "/")
		{
			if (second == "/")
			{
				pos++;
				while (letter[pos] != "\n")
				{
					pos++;
				}
				pos++;
				return "annotation";
			}
			if (second == "*")
			{
				pos++;
				while (!(letter[pos] == "*" && letter[pos + 1] == "/"))
				{
					pos++;
				}
				pos += 2;
				return "annotation";
			}
		}
		// for operator like == >= <= !=
		if ((second == "=" && ((first == "<" || first == ">" || first == "=" || first == "!")) || (second == first && (
			first == "+" || first == "-"))))
			str.append(letter[pos]);
	}
		// for error process
	// char c = '';
	// char c = 'cc';
	if (first=="'"&&err_flag!=1)
	{
		if(letter[pos+1]!="'")
		{
			err_flag = 1;
			cerr << " multiple char include in ' error in line " << __LINE__ << endl;
			//deal err
			while (letter[pos]!="'")
			{
				pos++;
			}
			pos ++;
		}

	}
	return str;
}

void printRes(string str, string res)
{
	cout << "< " << str << " : " << res << " >" << endl;
}

string identifyString(string str, int& pos)
{
	// pos += 1;
	while (letter[pos] != "\\" && letter[pos + 1] != ";")
	{
		str.append(letter[pos]);
		pos++;
	}
	str.append(letter[pos]);
	pos++;
	return str;
};

void identifyMacro(int& pos)
{
	pos += 1;
	while (letter[pos] != "\n")
	{
		pos++;
	}
	pos++;
}

void getWord()
{
	string word;
	for (current_position = 0; current_position < length;)
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
						keyword_num++;
						break;
					}
					else if (isId(word))
					{
						id_num++;
						printRes(word, "id");
					}
					break;
				}
			case 2:
				{
					word = identifyNum(letter[current_position], current_position);
					if (isConstant(word))
					{
						id_num++;
						printRes(word, "constant");
					}
					break;
				}
			case 3:
				{
					word = identifySym(letter[current_position], current_position);
					if (word != "annotation")
						if (isSymbol(word))
						{
							symbol_num++;
							printRes(word, "symbol");
						}
					break;
				}
			case 4:
				{
					word = identifyString(letter[current_position], current_position);
					{
						string_num++;
						printRes(word, "string");
					}
					break;
				}
			case 5:
				{
					identifyMacro(current_position);
					// printRes(word, "Macro");
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
	example_file >> noskipws;
	if (example_file.peek() == EOF)
	{
		cout << "file is empty" << endl;
	}
	while (example_file.peek() != EOF)
	{
		example_file >> c;
		letter[length] = c;
		length++;
	}
}

int main()
{
	FILE* file = nullptr;
	char buff[MAX_LEN];
	// ifstream example_file("prog.txt");
	ifstream example_file("tmp.txt");
	read_file(example_file);
	getWord();
	cout << endl;
	cout<<"id num"<<" : "<<id_num<<endl;
	cout<<"string num"<<" : "<<string_num<<endl;
	cout<<"keyword num"<<" : "<<keyword_num<<endl;
	cout<<"symbol num"<<" : "<<symbol_num<<endl;
	cout << "char num" << " : " << length << endl;
	// cout << isLetter('s');
	// for (auto i = 0; i < length; ++i)
	// {
	// 	cout << letter[i];
	// }

	// cout << typeofWord("[");
	// cout << isConstant("46E-8");
	// cout << isKeyword("int");
	// cout << isSymbol("2+");
	// cout << identifyString("string");
	system("pause");
	return 0;
}

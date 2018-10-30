#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <algorithm>

#define MAX_LEN 100
using namespace std;
int current_position = 0; // record current reading position
const string backspace = " ";
const string keyword[] = {
	"auto", "double", "int", "struct", "break", "else", "long", "switch",
	"case", "enum", "register", "typedef", "char", "extern", "return", "union",
	"const", "float", "short", "unsigned", "continue", "for", "signed", "void",
	"default", "goto", "sizeof", "volatile", "do", "if", "while", "static"
};
const string symbol[] = {"<", ">", "!=", ">=", "<=", "==", ",", ";", "(", ")", "{", "}", "+", "-", "*", "/", "="};
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

int typeofWord(string str)
{
	if (!str.compare(backspace))
		return 0;
	if ((str >= "a" && str <= "z") || (str >= "A" && str <= "z"))
		return 1; //letter
	if (str >= "0" && str <= "9")
		return 2; //num
	if (str == ">" || str == "=" || str == "<" || str == "!" || str == "," || str == ";" || str == "(" || str == ")" ||
		str == "{" || str == "}"
		|| str == "+" || str == "-" || str == "*" || str == "/")
		return 3; // form
}

string identify(string str, int& pos)
{
	pos += 1;
	while (letter[pos].compare(backspace) || typeofWord(letter[pos]) != 3)
	{
		str.append(letter[pos]);
		pos++;
	}
	return str;
}

void getWord()
{
	string word;
	for (current_position = 0; current_position < letter->length();)
	{
		auto type = typeofWord(letter[current_position]);
		switch (type)
		{
		case 1:
			{
				word = identify(letter[current_position], current_position);
				cout << word << endl;
			}
		case 2:
			{
			}
		case 3:
			{
			}
		default:
			{
			}
		}
	}
}

void read_file(ifstream &example_file)
{
	assert(example_file.is_open());
	char c;
	auto length = 0;
	example_file >> noskipws;

	while (!example_file.eof())
	{
		example_file >> c;
		// cout << c;
		// if (c != ' ')
		// {
		letter[length] = c;
		length++;
		// }
	}
}

int main()
{
	FILE* file = nullptr;
	char buff[255];

	ifstream example_file("prog.txt");
	// read_file(example_file);
	// getWord
	cout << isLetter('s');

	// for (auto i = 0; i < length; ++i)
	// {
	// 	cout << letter[i];
	// }
	system("pause");
	return 0;
}

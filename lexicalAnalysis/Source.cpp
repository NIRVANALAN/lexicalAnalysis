#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cassert>

#define MAX_LEN 100
using namespace std;
int current_position = 0; // record current reading position
const string backspace = " ";
const string keyword[] = { "auto", "double", "int", "struct", "break", "else", "long", "switch",
						  "case", "enum", "register", "typedef", "char", "extern", "return", "union",
						  "const", "float", "short", "unsigned", "continue", "for", "signed", "void",
						  "default", "goto", "sizeof", "volatile", "do", "if", "while", "static" };
const string symbol[] = { "<", ">", "!=", ">=", "<=", "==", ",", ";", "(", ")", "{", "}", "+", "-", "*", "/", "=" };
//存放文件取出的字符
string letter[MAX_LEN];
//将字符转换为单词
string words[MAX_LEN];
int length;  //保存程序中字符的数目
int num;

void printFile(FILE *file) {
	if (file == nullptr)
		printf("file not exist");

	char ch = (char)fgetc(file);
	while (ch != EOF) {
		putchar(ch);
		ch = (char)fgetc(file);
	}
	fclose(file);
}

bool isId() {
	return true;
}

bool isKeyword(string s) {
	return true;
}

int typeofWord(string str) {
	if (!str.compare(backspace))
	{
		return 0;
	}
	if ((str >= "a" && str <= "z") || (str >= "A" && str <= "z"))
		return 1; //letter
	if (str >= "0" && str <= "9")
		return 2; //num
	if (str == ">" || str == "=" || str == "<" || str == "!" || str == "," || str == ";" || str == "(" || str == ")" ||
		str == "{" || str == "}"
		|| str == "+" || str == "-" || str == "*" || str == "/")
		return 3; // form
}

string identify(string str, int &pos) {
	pos += 1;
	while (letter[pos].compare(backspace) || typeofWord(letter[pos]) != 3) {
		str.append(letter[pos]);
		pos++;
	}
	return str;
}

void getWord() {
	string word;
	for (current_position = 0; current_position < letter->length(); ) {
		auto type = typeofWord(letter[current_position]);
		switch (type) {
		case 1: {
			word = identify(letter[current_position], current_position);
			cout << word << endl;
		}
		case 2: {

		}
		case 3: {

		}
		default:
			current_position++;
		}
	}
}

int main() {
	FILE *file = nullptr;
	char buff[255];
	//    file = fopen("../input/id", "r");
	//    printFile(file);

	ifstream example_file("prog.txt");
	assert(example_file.is_open());
	char c;
	auto length = 0;
	example_file >> noskipws;
	while (!example_file.eof()) {
		example_file >> c;
		//        cout << c;
		if (true) {
			letter[length] = c;
			length++;
		}
	}
	getWord();
	for (auto i = 0; i < length; ++i) {
		cout << letter[i];
	}
	return 0;
}

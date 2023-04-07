/*==============================================
Programmer: Mya Nnanthavongdouangsy
Class: CPSC 323-03 (Compiliers and languages)
Instructor: Miss Susmitha Padda 
------------------------------------------------
File: Project-1
------------------------------------------------
Environment: Win 10 Visual Studio 2022
Project: This program will take a txt file and 
		 find tokens for each lexeme and write 
		 each to an output file. 
==============================================*/
#include <iostream>
#include<fstream> 
#include <iomanip>
using namespace std;

void lexer(fstream& file, string& name, size_t size);
bool isOperator(char op);
bool isSeperator(char sep);
bool isCharacter(char strCh);
bool isKeyword(string& keyw);

//---------------------------------------------------------------
//main()
int main() {

	string lexeme = " ";
	size_t length;

	fstream readFile("input_scode.txt", ios::in);

	if (!readFile) {														//checking if input file can open
		cout << "Error opening read file\n\n";
	}
	else cout << "Success opening read file.\n\n";

	fstream writeFile("output.txt", ios::out);

	if (!writeFile) {														//checking if output file can open
		cout << "Error with opening write file.\n\n";
	}
	else cout << "Success opening write file.\n\n";

	system("pause");														//pause and clear screen
	system("cls");			

	writeFile << "Token" << setw(19) << "Lexeme" << endl;
	writeFile << "_____________________________" << endl;

	while (!readFile.eof()) {

		readFile >> lexeme;

		length = lexeme.length();

		lexer(writeFile, lexeme, length);
	}

	cout << "Success writing to output file. Check file to see tokens and lexemes of input_scode.\n\n";

	readFile.close();
	writeFile.close();

	return 0;
} //end of main()
//---------------------------------------------------------------
//lexer()
void lexer(fstream& file, string& name, size_t length) {
	int place = 0;
	string token = " ";

	for (int i = 0; i < length; i++) {
		if (isKeyword(name)) {												//checking if keyword 
			token = "keyword";
			file << token << setw(16) << name << endl;
			i += 4;
		}
		else if (isdigit(name[i])) {									   //checking if real number
			place = i;
			while (place < length) {
				if (name[place] == '.') {
					++place;
					while (place < length) {
						if (isSeperator(name[place])) {
							token = "real";
							file << token << setw(15);
							for (int j = i; j < place; j++) {
								file << name[j];
							}
							file << endl;
							i = place - 1;
							break;
						}
						place++;
					}
					break;
				}
				place++;
			}
		}
		else if (isCharacter(name[i]) || name[i] == '_') {					//checking if identifier
			token = "identifier";
			place = i;
			++place;
			if (isCharacter(name[place]) || isdigit(name[place]) || name[place] == '_') {
				while (place < length) {
					if (isOperator(name[place]) || isSeperator(name[place])) {

						file << token << setw(9);
						for (int j = i; j < place; j++) {
							file << name[j];
						}
						file << endl;
						i = place - 1;
						break;
					}
					place++;
				}
			}
			else if (isCharacter(name[i])) {
				file << token << setw(9) << name[i] << endl;
			}
		}
		else if (isSeperator(name[i])) {									//checking if seperator
			token = "seperator";
			file << token << setw(10) << name[i] << endl;
		}
		else if (isOperator(name[i])) {										//checking if operator
			token = "operator";
			place = i;
			++place;
			file << token << setw(11);
			if (isOperator(name[place])) {
				for (int j = i; j <= place; j++) {
					file << name[j];
				}
				file << endl;
				i = place;
			}
			else {
				file << name[i] << endl;
			}
		}
	}
} //end of lexer()
//---------------------------------------------------------------			//seperate functions to check values
//isOperator()
bool isOperator(char op) {													
	if (op == '+' || op == '-' || op == '/' || op == '=' || op == '*' || op == '%' || op == '?' || op == '>' || op == '<' || op == '&' || op == '!') {
		return true;
	}
	else
		return false;
} //end of isOperator()
//--------------------------------------------------------------
//isSeperator()
bool isSeperator(char sep) {
	if (sep == '(' || sep == ')' || sep == ';') {
		return true;
	}
	else
		return false;
}
//end of isSeperator()
//--------------------------------------------------------------
//isCharacter()
bool isCharacter(char strCh) {
	if (strCh >= 'A' && strCh <= 'Z' || strCh >= 'a' && strCh <= 'z') {
		return true;
	}
	else
		return false;
}
//end of isCharacter()
//--------------------------------------------------------------
//isKeyword()
bool isKeyword(string& keyw) {

	if (keyw == "while") {
		return true;
	}
	else
		return false;
}
//end of isKeyword()
//--------------------------------------------------------------
/*======== OUTPUT ==============================================
Success opening read file.

Success opening write file.

Press any key to continue . . .
-------- clear screen ---------------------------------
Success writing to output file. Check file to see tokens and lexemes of input_scode.


C:\Users\user\Desktop\cs\CS\Languages\C++\cpsc323_project-1_done\x64\Debug\cpsc323_project-1_done.exe (process 55256) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .
==============================================================*/
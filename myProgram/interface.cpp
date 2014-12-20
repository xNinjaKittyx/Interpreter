
#include <iostream>     //including I/O support
#include <fstream>      //including file I/O support
#include <vector>		//including support of vector container
#include <string>		//including the new C++ string class support
#include <cstring>		//including old C character array support
#include <conio.h>		//including support to use getch()
						//	to read one char at a time from user input

#include "interface.h"	//
#include "lexScanner.h"
#include "expEvaluator.h"
#include "interpreter.h"
using namespace std;


// 1. Read in a program (lines of statements) from a file
void Interface::loadProgramFromFile()
{
	char fileName[MaxLengthFileName];	
	// this char array stores the name of the file the program reads from.

	cout<<"Name of file to upload program from (ex. file.txt): ";
	cin >> fileName;
	while( strlen(fileName) == 0 )
	{
		cin >> fileName;
	}

	ifstream inFile;
	inFile.open( fileName );
	if ( inFile.fail() )
	{ cout << endl << "Cannot open this file!" << endl;
	return;
	}

	lines.clear();  //Delete all the lines of statements
	string inputBuffer;
	while( !inFile.eof() )
	{
		getline(inFile, inputBuffer);
		while( !inFile.eof() && inputBuffer.size() == 0 )
		{
			getline(inFile, inputBuffer);
		}

		if (!inFile.eof())
		{
  			cout<< "Line["
				<< lines.size()
				<< "] read:"
				<< inputBuffer << endl;
			lines.push_back(inputBuffer);
		}

	}

	inFile.close();
}



// 2. Display the lines of statements
void Interface::displayProgram()
{
	for (int i = 0; i < (int)lines.size();i++) {
		cout << "Line[" << i << "]:" << lines[i] << endl;
	}
}



// 3. Enter new lines of code to the end of the program
void Interface::appendLines()
{
	string s = " ";
	string t = ".";
	int count = lines.size();
	bool hi = true;
	cout << "Keep typing lines of statements. To stop appending, type a single period." << endl;
	while (hi == true) {
		cout << "[" << count << "]: ";
		getline(cin, s);
		if (s == ".") {
			hi = false;
		}
		else {
			lines.push_back(s);
			count++;
		}
	}
}


// 4. Insert new lines after an existing line
void Interface::insertLines()
{	
	int n;
	string s;
	if (lines.empty()) {
		cout << "There's no code!" << endl;
		return;
	}
	cout << "Before what line # would you like to inserts lines into?" << endl;
	cin >> n;
	while (n < 0 || n >= lines.size()) {
		cout << "You didn't type a valid integer. Please input again." << endl;
		cin >> n;
	}
	cin.ignore();
	bool hi = true;
	cout << "Keep typing lines to insert. To exit, use a single period for a line." << endl;
	while (hi) {
		cout << "[" << n << "]: ";
		getline(cin, s);
		if (s == ".") {
			hi = false;
		}
		else {
			lines.insert(lines.begin()+n, s);
			n++;
		}
	}
}


// 5. Delete a range of existing line
void Interface::deleteLines()
{
	int n;
	int m;
	if (lines.empty()) {
		cout << "There's no code!" << endl;
		return;
	}
	cout << "What lines do you wish to delete?" << endl;
	cout << "From line #:" << endl;
	cin >> n;
	while (n < 0 || n >= lines.size()) {
		cout << "You didn't type a valid integer. Please input again." << endl;
		cin >> n;
	}
	cout << "To line #:" << endl;
	cin >> m;

	for (int i = n; i <= m; i++) {
		lines.erase(lines.begin() + n);
	}
}


// 6. Replace the contents of an existing line
void Interface::replaceOneLine()
{
	int n;
	string s;
	if (lines.empty()) {
		cout << "There's no code!" << endl;
		return;
	}
	cout << "What line would you like to replace?" << endl;
	cin >> n;
	while (n < 0 || n >= lines.size()) {
		cout << "You didn't type a valid integer. Please input again." << endl;
		cin >> n;
	}
	cin.ignore();
	cout << "Type in the new line for line " << n << endl;
	getline(cin, s);
	lines.erase(lines.begin() + n);
	lines.insert(lines.begin() + n, s);

}


// 7. Save program to a file
void Interface::saveProgramIntoFile()
{
	if (lines.empty()) {
		cout << "There's no code!" << endl;
		return;
	}
	char fileName[MaxLengthFileName];

	cout << "Name the file of the current program (ex. file.txt): ";
	cin >> fileName;
	while (strlen(fileName) == 0)
	{
		cin >> fileName;
	}

	ofstream outFile;
	outFile.open(fileName);
	if (outFile.fail())
	{
		cout << endl << "Cannot output!" << endl;
		return;
	}
	
	for (auto i = lines.begin(); i < lines.end(); i++) {
		outFile << *i << endl;
	}

	outFile.close();

}

//An auxilliary message displaying function
void Interface::endOfService(const string service)
{
	cout<<endl << service << " done." << endl << "Press any key to continue.";
	getch();
	cout << endl;
	cout << "****************************************************" <<endl<< endl;

}

// This menu() function is the interface
void Interface::startInterface() {

	// "Then I suppose now is the time for me to say something profound....
	// Nothing comes to mind. Let's do it."

	bool inMenu = true;	// while the user is using the program this var is set to true and the menu keeps looping.
						// when the user wants to quit, it is set to false and the loop ends.
	char keyPressed;	// This var stores which menu selection the user picks.

	floatVarValueTable varTable;

	string rawExpressionString;
	expVector infixExp, postfixExp;
	float expValue;

	while ( inMenu )
	{
		cout<< endl << endl << endl;
		cout << "****************************************************" << endl;
		cout  <<"**  MENU:(press a character to select an option)  **" << endl;
 		cout << "****************************************************" << endl;
		cout<<"Q. [QUIT]\tQuit."<<endl;
		cout<<"L. [LOAD]\tRead in a program (lines of statements) from a file"<<endl;
  		cout<<"S. [SAVE]\tSave lines of statement as a program into a file"<<endl;
		cout << endl;

		cout<<"C. [CODE DISPLAY]\tDisplay the source code as lines of statements"<<endl;
		cout << endl;

		cout<<"A. [APPEND]\tAppend new lines to the end of the program"<<endl;
		cout<<"I. [INSERT]\tInsert new lines before an existent line"<<endl;
		cout<<"D. [DELETE]\tDelete a range of existent lines"<<endl;
		cout<<"R. [REPLACE]\tReplace the contents of an existent line"<<endl;
		cout << endl;
		
		cout << "G. [LEXICAL]\tGet Lexical Info of the code." << endl;
		cout << "H. [CALC]\tEvaluate a line of arithmic or logic expression" << endl;
		cout<<"P. [PARSE]\tParse and ident the code" << endl;
		cout<<"E. [EXECUTE]\tExecute (run) the program"<<endl;
		cout<<"T. [TOGGLE]\tToggle the execution debug mode"<<endl;

		cout << "****************************************************" <<endl<< endl;

		cout<<"Your choice is: ";
		keyPressed = getch();
		cout<<keyPressed << endl;

		switch(keyPressed) {
		case 'Q': case 'q'://Quit
			cout << "[QUIT]:" << endl;
			inMenu = false;
			break;

		case 'L': case 'l':// 1. Read in a program (lines of statements) from a file
 			cout << "[LOAD PROGRAM]:" << endl;
			loadProgramFromFile();
			endOfService("[LOAD PROGRAM]");
			break;

		case 'C': case 'c':// 2. Display the lines of statements
			cout << "[CODE DISPLAY]:" << endl;
			displayProgram();
			endOfService("[CODE DISPLAY]");
			break;

		case 'A': case 'a':// 3. Append new lines of code to the end
			cout << "[APPEND]:" << endl;
			appendLines();
			endOfService("[APPEND LINES]");
			break;

		case 'I': case 'i':// 4. Insert a new line after an existing line
			cout << "[INSERT LINES]:" << endl;
			insertLines();
			endOfService("[INSERT LINES]");
			break;

		case 'D': case 'd':// 5. Delete an existing line
			cout << "[DELETE LINES]:" << endl;
			deleteLines();
			endOfService("[DELETE LINES]");
			break;

		case 'R': case 'r':// 6. Replace the contents of an existing line
			cout << "[REPLACE]:" << endl;
			replaceOneLine();
			endOfService("[REPLACE ONE LINE]");
			break;

		case 'S': case 's':// 7. Save program to a file
			cout << "[SAVE]:" << endl;
			saveProgramIntoFile();
			endOfService("[SAVE CODE INTO A FILE]");
			break;

		case 'G': case 'g' : //Get Lexical Info
			cout << "[GET LEXICAL INFO]:" << endl;
			LexicalScanner::getLexicalInfo(
				lines,
				myVectOfTokenVects,
				myVectOfCategoryVects);

			LexicalScanner::displayLexicalInfo(
				myVectOfTokenVects,
				myVectOfCategoryVects);

			endOfService("[GET LEXICAL INFO]");
			break;

		case 'H': case 'h': //Calculate Lines
			infixExp.clear();
			postfixExp.clear();
			cout << "[CALCULATE LINE]:" << endl;
			cout << "Type in an infix expression with Numerical constants or any of the variables listed above." << endl;
			getline(cin, rawExpressionString);
			LexicalScanner::getPerLineTokenVectFromOneStringObject
				(rawExpressionString,
				infixExp
				);

			ExpressionEvaluator::infixToPostfixConversion(infixExp, postfixExp);

			if (ExpressionEvaluator::postfixEvaluator(postfixExp, varTable, expValue))
				cout << "The value of this expression is " << expValue << endl;
			else
				cout << "This expression is not a valid expression" << endl;

			endOfService("[CALCULATE]");
			break;
			

		case 'P': case 'p':// 8. Parse and Indent the program
			cout << "[PARSE AND INDENT SOURCE CODE]:" << endl;
			endOfService("[PARSE AND INDENT SOURCE CODE]");
			break;

		case 'E': case 'e':// 9. Run program
			cout << "[EXECUTE TO RUN PROGRAM]:" << endl;

			Interpreter::executeProgram(lines);
			endOfService("[EXECUTE TO RUN PROGRAM]");
			break;

		case 'T': case 't':// Toggle the debug mode
			cout << "[TOGGLE the debug mode]:" << endl;
			break;


		default:
			cout << "[?? UNKNOWN COMMAND]:" << endl;
			// Unrecognized key, do nothing
			break;
		}

	} // End of while loop.
}

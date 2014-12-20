#ifndef INTERFACE_H   
//The compiler checks whether INTERFACE_H is defined alread to see
//whether this header file is already included.

#define INTERFACE_H
//If INTERFACE_H not defined yet, define it and include
//what should be included in order to utilize the implementation
//in the interface.cpp


#include <vector>		//including support of vector container
#include <string>		//including the new C++ string class support
#include "lexScanner.h"
using namespace std;



	class Interface
	{
	 private:
		//Store a program as vector of strings, with each statement stored as a string.
		//Initially it is an empty vector.
		 vector<string> lines;
		 vectOfTokenVects myVectOfTokenVects;
		 vectOfCategoryVects myVectOfCategoryVects;

		

	 public:

		//This constant static data member is used to s
		//		set the maximal length of file names to 100 characters
		static const unsigned int MaxLengthFileName = 100;

		// 1. Read in a program (lines of statements) from a file
		void loadProgramFromFile();

		// 2. Display the lines of statements
		void displayProgram();

		// 3. Enter new lines of code to the end of the program
		void appendLines();

		// 4. Insert new lines after an existing line
		void insertLines();

		// 5. Delete existing lines
		void deleteLines();

		// 6. Replace the contents of an existing line
		void replaceOneLine();

		// 7. Save program to a file
		void saveProgramIntoFile();


		// This startInterface() function serves as the central place
		//	to access all the services provided by the interpreter
		//	including the functions listed above
		void startInterface();

		//This is a function to facilitate the display of messages to the user
		void endOfService(const string service);
	};


#endif


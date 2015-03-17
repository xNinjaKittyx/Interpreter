#include "interpreter.h"
#include "lexScanner.h"
#include "expEvaluator.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

void Interpreter::executeProgram(vector<string> source) {

	static floatVarValueTable stringFloatMap;
	static int isCurlyBrace = 0;
	vectOfCategoryVects vectCategory;
	vectOfTokenVects vectToken;
	LexicalScanner::getLexicalInfo(source, vectToken, vectCategory);
	vector<int> stackLineNum;
	vector<string> stackBlockTypes;
	vector<string> source2;
	bool execute;
	bool debug = false;

	for (size_t i = 0; i < vectToken.size(); i++) {
		perLineTokenVector tokenStringVector = vectToken[i];
		//each line
		
		 
		// cout << i << endl;cout << stackBlockTypes.size() << " " << stackLineNum.size() << endl; //DEBUGGING

		


		size_t j = 0;
			//now evaluate each individual token
			//Check if the token is a keyword.

			if (LexicalScanner::isKEYWORD(tokenStringVector[j])) {
				//If it is a keyword, then try read.




				if (tokenStringVector[j] == "read") {
					if (readExecute(tokenStringVector, stringFloatMap, i, j) == false)
						return;
					
				}



				//DISPLAY
				else if (tokenStringVector[j] == "display") {
					if (displayExecute(tokenStringVector, stringFloatMap, i, j) == false)
						return;
				}



				else if (tokenStringVector[j] == "if") {
					bool boolvar;
					j++;
					string rawExpressionString;
					vector<int> myNumStack;
					if (LexicalScanner::isLEFT_PARENTHESIS(tokenStringVector[j]) == false) {
						cout << "ERROR 401: Syntak Error for display on line " << i << "." << endl;
						return;
					}
					myNumStack.push_back(1);
					++j;
					while (!(LexicalScanner::isRIGHT_PARENTHESIS(tokenStringVector[j]) && (myNumStack.size() == 1))) {
						if (LexicalScanner::isLEFT_PARENTHESIS(tokenStringVector[j])) {
							myNumStack.push_back(1);
						}
						else if (LexicalScanner::isRIGHT_PARENTHESIS(tokenStringVector[j])) {
							myNumStack.pop_back();
						}
						rawExpressionString.append(tokenStringVector[j]);
						j++;
					}
					myNumStack.clear();

					expVector infixExp, postfixExp;
					float expValue;

					LexicalScanner::getPerLineTokenVectFromOneStringObject
						(rawExpressionString,
						infixExp
						);
					ExpressionEvaluator::infixToPostfixConversion(infixExp, postfixExp);

					if (ExpressionEvaluator::postfixEvaluator(postfixExp, stringFloatMap, expValue))
						boolvar = expValue;
					else {
						cout << "ERROR 402: Invalid Expression on line " << i << "." << endl;
						return;
					}

					try {
						i++;
					}
					catch (size_t param) {
						cout << "ERROR 403: Exception with Line Numbers." << endl;
						return;
					}


					tokenStringVector = vectToken[i];
					j = 0;
					if (LexicalScanner::isLEFT_CURLYBRACE(tokenStringVector[j]) == false) {
						if (boolvar == true) {
							isCurlyBrace = 2;
							stackLineNum.push_back(i - 1);
							stackBlockTypes.push_back("if");
							i--;
							continue;
						}
						else if (boolvar == false){
							try {
								i++;
							}
							catch (size_t param) {
								cout << "ERROR 405: Exception with Line Numbers" << endl;
								return;
							}

							tokenStringVector = vectToken[i];
							j = 0;

							if (tokenStringVector[j] == "else") {

								try {
									i++;
								}
								catch (size_t param) {
									cout << "ERROR 407: Exception with Line Numbers" << endl;
									return;
								}


								tokenStringVector = vectToken[i];
								j = 0;

								if (LexicalScanner::isLEFT_CURLYBRACE(tokenStringVector[j]) == false) {
									isCurlyBrace = 2;
									stackLineNum.push_back(i - 1);
									stackBlockTypes.push_back("else");
									i--;
									continue;
								}
								else {
									stackLineNum.push_back(i - 1);
									stackBlockTypes.push_back("else");
									continue;
								}
							}
							i--;
							continue;

						}
					}

					stackBlockTypes.push_back("if");
					stackLineNum.push_back(i - 1);
					int watever = i - 1;

					if (boolvar == true) {
						continue;
					}
					else if (boolvar == false) {
						while (true) {
							bool foundit = false;
							for (int i = 0; i < stackLineNum.size(); i++) {
								if (stackLineNum[i] == watever) {
									foundit = true;
									break;
								}
							}
							if (foundit == false) {
								//This means that the original line number was not found.
								break;
							}
							try {
								i++;
							}
							catch (size_t param) {
								cout << "ERROR 405: Exception with Line Numbers" << endl;
								return;
							}


							tokenStringVector = vectToken[i];
							j = 0;

							if (LexicalScanner::isLEFT_CURLYBRACE(tokenStringVector[j])) {
								stackLineNum.push_back(i - 1);
							}
							else if (LexicalScanner::isRIGHT_CURLYBRACE(tokenStringVector[j])) {
								stackLineNum.pop_back();
							}
						}
						stackBlockTypes.pop_back();

						try {
							i++;
						}
						catch (size_t param) {
							cout << "ERROR 406: Exception with Line Numbers" << endl;
							return;
						}


						tokenStringVector = vectToken[i];
						j = 0;
						
						if (tokenStringVector[j] == "else") {

							try {
								i++;
							}
							catch (size_t param) {
								cout << "ERROR 407: Exception with Line Numbers" << endl;
								return;
							}


							tokenStringVector = vectToken[i];
							j = 0;

							if (LexicalScanner::isLEFT_CURLYBRACE(tokenStringVector[j]) == false) {
								isCurlyBrace = 2;
								stackLineNum.push_back(i - 1);
								stackBlockTypes.push_back("else");
								i--;
								continue;
							}
							else {
								stackLineNum.push_back(i - 1);
								stackBlockTypes.push_back("else");
								continue;
							}
						}
						i--;

					}

				}



				else if (tokenStringVector[j] == "else") {
					//Else statements are either going to the invalid ones or in the case that if is true.
					//So all of them will be ignored (assuming they have the right syntax).

					try {
						i++;
					}
					catch (size_t param) {
						cout << "ERROR 501: Exception with Line Numbers" << endl;
						return;
					}


					tokenStringVector = vectToken[i];
					j = 0;

					if (LexicalScanner::isLEFT_CURLYBRACE(tokenStringVector[j]) == false) {
						continue;
					}
					stackBlockTypes.push_back("else");
					stackLineNum.push_back(i - 1);
					int watever = i - 1;
					while (true) {


						bool foundit = false;
						for (int i = 0; i < stackLineNum.size(); i++) {
							if (stackLineNum[i] == watever) {
								foundit = true;
								break;
							}
						}
						if (foundit == false) {
							//This means that the original line number was not found.
							break;
						}

						try {
							i++;
						}
						catch (size_t param) {
							cout << "ERROR 503: Exception with Line Numbers" << endl;
							return;
						}

						tokenStringVector = vectToken[i];
						j = 0;

						if (LexicalScanner::isLEFT_CURLYBRACE(tokenStringVector[j])) {
							stackLineNum.push_back(i - 1);
						}
						else if (LexicalScanner::isRIGHT_CURLYBRACE(tokenStringVector[j])) {
							stackLineNum.pop_back();
						}
					}
						
					continue;
				}







				else if (tokenStringVector[j] == "while") {

					bool boolvar;

					j++;
					string rawExpressionString;
					vector<int> myNumStack;
					if (LexicalScanner::isLEFT_PARENTHESIS(tokenStringVector[j]) == false) {
						cout << "ERROR 601: Syntak Error for display on line " << i << "." << endl;
						return;
					}
					myNumStack.push_back(1);
					++j;
					while (!(LexicalScanner::isRIGHT_PARENTHESIS(tokenStringVector[j]) && (myNumStack.size() == 1))) {
						if (LexicalScanner::isLEFT_PARENTHESIS(tokenStringVector[j])) {
							myNumStack.push_back(1);
						}
						else if (LexicalScanner::isRIGHT_PARENTHESIS(tokenStringVector[j])) {
							myNumStack.pop_back();
						}
						rawExpressionString.append(tokenStringVector[j]);
						j++;
					}
					myNumStack.clear();

					expVector infixExp, postfixExp;
					float expValue;

					LexicalScanner::getPerLineTokenVectFromOneStringObject
						(rawExpressionString,
						infixExp
						);
					ExpressionEvaluator::infixToPostfixConversion(infixExp, postfixExp);

					if (ExpressionEvaluator::postfixEvaluator(postfixExp, stringFloatMap, expValue))
						boolvar = expValue;
					else {
						cout << "ERROR 602: Invalid Expression on line " << i << "." << endl;
						return;
					}

					try {
						i++;
					}
					catch (size_t param) {
						cout << "ERROR 603: Exception with Line Numbers" << endl;
						return;
					}
					tokenStringVector = vectToken[i];
					j = 0;

					if (LexicalScanner::isLEFT_CURLYBRACE(tokenStringVector[j]) == false) {
						if (boolvar == false) {
							continue;
						}
						else if (boolvar == true) {
							isCurlyBrace = 2;
							stackLineNum.push_back(i - 1);
							stackBlockTypes.push_back("while");
							i--;
							continue;
						}
					}
					stackLineNum.push_back(i - 1);
					stackBlockTypes.push_back("while");
					int watever = i - 1;

					if (boolvar == false) {
						while (true) {

							bool foundit = false;
							for (int i = 0; i < stackLineNum.size(); i++) {
								if (stackLineNum[i] == watever) {
									foundit = true;
									break;
								}
							}
							if (foundit == false) {
								//This means that the original line number was not found.
								break;
							}

							try {
								i++;
							}
							catch (size_t param) {
								cout << "ERROR 605: Exception with Line Numbers" << endl;
								return;
							}
							tokenStringVector = vectToken[i];
							j = 0;

							if (LexicalScanner::isLEFT_CURLYBRACE(tokenStringVector[j])) {
								stackLineNum.push_back(i - 1);
							}
							else if (LexicalScanner::isRIGHT_CURLYBRACE(tokenStringVector[j])) {
								stackLineNum.pop_back();
							}
						}
						stackBlockTypes.pop_back();
					}
					else
						continue;
				}
				else {
					cout << "ERROR 999: This has not been implemented yet" << endl;
					return;
				}
			}




			//Now for declaration of variables
			else if (LexicalScanner::isID_NAME(tokenStringVector[j])) {
				if (idNameExecute(tokenStringVector, stringFloatMap, i, j) == false)
					break;
			}



			else if (LexicalScanner::isLEFT_CURLYBRACE(tokenStringVector[j])) {
				if (stackBlockTypes.empty() || (stackBlockTypes.size() == stackLineNum.size())) {
					cout << "isLEFT_CURLYBRACE ERROR: Left Curly Braces on line " << i << "." << endl;
					return;
				}
				else
					stackLineNum.push_back(i - 1);
			}

			else if (LexicalScanner::isRIGHT_CURLYBRACE(tokenStringVector[j])) {
				if (stackBlockTypes.empty() || stackLineNum.empty()) {
					cout << "isRIGHT_CURLYBRACE ERROR: Right Curly Braces on line " << i << "." << endl;
					return;
				}
				else {
					if (stackBlockTypes.back() == "while") {
						i = stackLineNum.back() - 1;
						stackLineNum.pop_back();
						stackBlockTypes.pop_back();
					}
					else {
						stackLineNum.pop_back();
						stackBlockTypes.pop_back();
					}
				}

			}


			else {
				cout << "Error on line " << i << "." << endl;
				return;
			}

			if (isCurlyBrace == 2) {
				if (stackBlockTypes.back() == "if") {
					stackBlockTypes.pop_back();
					stackLineNum.pop_back();
					isCurlyBrace = 0;
				}
				else if (stackBlockTypes.back() == "else") {
					stackBlockTypes.pop_back();
					stackLineNum.pop_back();
					isCurlyBrace = 0;
				}
				else if (stackBlockTypes.back() == "while") {

					i = stackLineNum.back() - 1;
					stackLineNum.pop_back();
					stackBlockTypes.pop_back();
					isCurlyBrace = 0;
				}

			}

			if (stackLineNum.size() == stackBlockTypes.size() && debug == true) {
				cout << "THE STACKS EQUAL" << endl;
			}
		
	}
}
//IF IT IS READ
bool Interpreter::readExecute(perLineTokenVector &tokenStringVector, floatVarValueTable &stringFloatMap, size_t &i, size_t &j) {


	//If there's another token afterwards, then try the next token
	if (j < tokenStringVector.size() + 1) {
		++j;

		//Now  check if its an ID_NAME
		if (LexicalScanner::isID_NAME(tokenStringVector[j])) {

			//Create they KEY-VALUE into the map stringFloatMap using map as an Associative Array.
			//We are assuming that READ only reads numerical values.
			float i;
			cin >> i;
			stringFloatMap[tokenStringVector[j]] = i;

		}

		//ID_NAME CHECK
		else {
			cout << "ERROR 100: The var on line " << i << " is not a valid ID_NAME." << endl;
			return false;
		}
	}
	//tokenStringVector CHECK
	else {
		cout << "ERROR 101: There is no var written after READ on line " << i << "." << endl;
		return false;
	}

	//Increase J again
	if (j < tokenStringVector.size() + 1) {
		++j;
		if (LexicalScanner::isSEMICOLON(tokenStringVector[j]))
			return true;
		else {
			cout << "ERROR 102: You forgot a semicolon. The program will continue to run." << endl;
		}
	}
	else {
		cout << "ERROR 103: You forgot a semicolon. The program will continue to run." << endl;
	}
	return true;
}

//IF IT IS DISPLAY
bool Interpreter::displayExecute(perLineTokenVector &tokenStringVector, floatVarValueTable &stringFloatMap, size_t &i, size_t &j) {
	string rawExpressionString;
	if (j < tokenStringVector.size() + 1) {
		++j;
		for (auto k = j; k < tokenStringVector.size() - 1; k++) {
			//String Literals or IDNAMES?
			if (LexicalScanner::isSTRING_LITERAL(tokenStringVector[k])) {
				string ohaidere = tokenStringVector[k];

				ohaidere.erase(ohaidere.begin());
				ohaidere.erase(ohaidere.end() - 1);
				cout << ohaidere;
				if (k < tokenStringVector.size())
					k++;

			}
			else if (LexicalScanner::isID_NAME(tokenStringVector[k]) || LexicalScanner::isNUMERICAL_LITERAL(tokenStringVector[k])) {
				while ((LexicalScanner::isCOMMA(tokenStringVector[k]) == false && LexicalScanner::isSEMICOLON(tokenStringVector[k]) == false)) {
					if (k == tokenStringVector.size())
						break;
					if (LexicalScanner::isID_NAME(tokenStringVector[k])) {
						if (stringFloatMap.find(tokenStringVector[k]) == stringFloatMap.end()) {
							cout << "ERROR 201: CANNOT FIND VARIABLE" << endl;
							return false;
						}
					}
					rawExpressionString.append(tokenStringVector[k]);
					k++;
				}

				expVector infixExp, postfixExp;
				float expValue;

				LexicalScanner::getPerLineTokenVectFromOneStringObject
					(rawExpressionString,
					infixExp
					);
				ExpressionEvaluator::infixToPostfixConversion(infixExp, postfixExp);

				if (ExpressionEvaluator::postfixEvaluator(postfixExp, stringFloatMap, expValue))
					cout << expValue;
				else {
					cout << "ERROR 202: Invalid Expression on line " << i << "." << endl;
					return false;
				}
			}
			else { //Syntax Error
				cout << "ERROR 203: Syntax Error for display on line " << i << "." << endl;
				return false;
			}


			if (LexicalScanner::isCOMMA(tokenStringVector[k])) {
				//continue the programc
				continue;
			}
			else if (LexicalScanner::isSEMICOLON(tokenStringVector[k])) {
				cout << endl;
				return true; //Basically this for loop will ignore everything past the semicolon on the same line.
			}
			else { //Syntax Error
				cout << "ERROR 204: Syntax Error for display on line " << i << "." << endl;
				return false;
			}
		}

	}
	return true;
}

//IF IT IS ID_NAME
bool Interpreter::idNameExecute(perLineTokenVector &tokenStringVector, floatVarValueTable &stringFloatMap, size_t &i, size_t &j ) {

	string nameOfId = tokenStringVector[j];
	string rawExpressionString;
	j++;
	if (LexicalScanner::isASSIGNMENT_OP(tokenStringVector[j])) {
		j++;
		while ((LexicalScanner::isCOMMA(tokenStringVector[j]) == false && LexicalScanner::isSEMICOLON(tokenStringVector[j]) == false)) {
			if (j == tokenStringVector.size())
				break;
			if (LexicalScanner::isID_NAME(tokenStringVector[j])) {
				if (stringFloatMap.find(tokenStringVector[j]) == stringFloatMap.end()) {
					cout << "ERROR 301: CANNOT FIND VARIABLE" << endl;
					return false;
				}
			}
			rawExpressionString.append(tokenStringVector[j]);
			j++;
		}


		expVector infixExp, postfixExp;
		float expValue;

		LexicalScanner::getPerLineTokenVectFromOneStringObject
			(rawExpressionString,
			infixExp
			);
		ExpressionEvaluator::infixToPostfixConversion(infixExp, postfixExp);

		if (ExpressionEvaluator::postfixEvaluator(postfixExp, stringFloatMap, expValue))
			stringFloatMap[nameOfId] = expValue;
		else {
			cout << "ERROR 302: Invalid Expression on line " << i << "." << endl;
			return false;
		}

		if (LexicalScanner::isSEMICOLON(tokenStringVector[j])) {
			return true;
		}
		else {
			cout << "ERROR 303: Syntax Error for display on line " << i << "." << endl;
			return false;
		}
	}
	else {
		cout << "ERROR 304: ASSIGNMENT OPERATOR NOT USED CORRECTLY." << endl;
		return false;
	}
	return true;
}
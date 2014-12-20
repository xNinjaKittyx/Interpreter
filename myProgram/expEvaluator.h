#ifndef EXP_EVALUATOR_H    
#define EXP_EVALUATOR_H 
//**************************************************************************************
#include <map>
#include <string>
using namespace std;

typedef map<string,float> floatVarValueTable;
//A variable table recording the names (strings) of variables
//and the current floating point values of these variables

typedef vector<string> expVector;
//An expression vector is a vector of token strings 

class ExpressionEvaluator
{
 public:
	static int precedenceLevel(const string & opToken);
	//return the precedence level of an operator toekn


	static bool postfixEvaluator( const expVector & postfixExp, 
						floatVarValueTable & varTable, 
						float & expValue );
	//Evaluate the value of the postfix expression in postfixExp
	//with respect to the variables and their current values in varTable.
	//finally store the value of the expresson in expValue.
	//If postfixExp is not a valid postfix expression, return false; otherwsie return true.


	static bool infixToPostfixConversion( const expVector & infixExp, expVector & postfixExp );
	//Convert the infix expression in infixExp into a corresponding postfix expression.
	//Store the corresponding postfix expression in postfixExp.
	//If infixExp is not a valid infix expression, return false; otherwsie return true.



	static bool infixEvaluator	(	const expVector & infixExp, 
							floatVarValueTable & varTable, 
							float& expValue
						);
	//Evaluate the value of the infix expression in postfixExp
	//with respect to the variables and their current values in varTable.
	//finally store the value of the expresson in expValue.
	//If postfixExp is not a valid postfix expression, return false; otherwsie return true.



	static bool infixEvaluator(	expVector::iterator begin, 
							expVector::iterator end, 
							floatVarValueTable & varTable, 
							float &expValue
						);
	//Evaluate the value of an infix expression 
	//that is embedded within an expression vector 
	//The two expVector::iterator iterators: begin and end specify 
	//where the infix expression is embedded.
	//
	//Evaluate the value of an infix expression 
	//with respect to the variables and their current values in varTable.
	//finally store the value of the expresson in expValue.
	//If postfixExp is not a valid postfix expression, return false; otherwsie return true.

};

//**************************************************************************************
#endif // Matching the starting #ifndef EXP_EVALUATOR_H  
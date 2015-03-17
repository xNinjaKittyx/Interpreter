#ifndef INTERPRETER_H

#define INTERPRETER_H

#include <vector>
#include <string>
#include "lexScanner.h"
#include "expEvaluator.h"
using namespace std;

	class Interpreter{
		private:
			//Store the Map<string,float>
			static bool readExecute(perLineTokenVector &tokenStringVector, floatVarValueTable &stringFloatMap, size_t &i, size_t &j);
			static bool displayExecute(perLineTokenVector &tokenStringVector, floatVarValueTable &stringFloatMap, size_t &i, size_t &j);
			static bool idNameExecute(perLineTokenVector &tokenStringVector, floatVarValueTable &stringFloatMap, size_t &i, size_t &j);

		public:
			//executeProgram
			static void executeProgram(vector<string> source);
	};

#endif
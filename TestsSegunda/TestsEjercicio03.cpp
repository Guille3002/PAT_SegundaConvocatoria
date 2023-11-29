#include "pch.h"

#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "../PAT_SegundaConvocatoria/Ejercicio03.h"
#include "../PAT_SegundaConvocatoria/Ejercicio03.cpp"

using ::testing::TestWithParam;
using ::testing::ValuesIn;
using ::std::tuple;
using ::std::vector;
using ::std::string;
using ::std::unordered_map;

namespace SegundaTests {

	static const char VOID_FUNC = 'V';
	static const char INT_FUNC = 'F';

	struct StackOperations {
		string funcName;
		int param;
		int expected;
		char type; // V: void, F: function with return value
	};

	int push(MinStack* minStack, int value) {
		minStack->push(value);
		return INT_MIN;
	}

	int pop(MinStack* minStack, int value) {
		minStack->pop();
		return INT_MIN;
	}

	int top(MinStack* minStack, int value) {
		return minStack->top();
	}

	int getMin(MinStack* minStack, int value) {
		return minStack->getMin();
	}

	static const unordered_map<string, int (*)(MinStack*, int)> stackOps = {
		{"push", push},
		{"pop", pop},
		{"top", top},
		{"getMin", getMin}
	};

	class E03Tests : public TestWithParam<vector<StackOperations>> {
	protected:
		MinStack* minStack;
		vector<StackOperations> operations;

		void SetUp() override {
			minStack = new MinStack();
			operations = GetParam();
		}

		void TearDown() override {
			delete minStack;
			minStack = nullptr;
		}

	public:
		static vector<vector<StackOperations>> ReadParams() {
			vector<vector<StackOperations>> params;
			std::ifstream paramsFile("e03.csv");
			string line;

			vector<StackOperations> ops;

			while (std::getline(paramsFile, line)) {
				if (line.length() == 0) {
					params.push_back(ops);
					ops = {};
					continue;
				}

				std::stringstream strStream(line);

				string op;
				std::getline(strStream, op, ',');

				string paramString;
				std::getline(strStream, paramString, ',');

				int param, result;
				char type;

				if (op == "pop" || op == "push") {
					result = INT_MIN;
					param = paramString.length() != 0 ? std::stoi(paramString) : INT_MIN;
					type = VOID_FUNC;
				}
				else {
					result = std::stoi(paramString);
					param = INT_MIN;
					type = INT_FUNC;
				}

				ops.push_back(StackOperations{ op, param, result, type });
			}

			if (ops.size() > 0)
				params.push_back(ops);

			return params;
		}
	};

	TEST_P(E03Tests, MinStackTests) {
		for (int i = 0; i < operations.size(); ++i) {
			StackOperations op = operations[i];
			GTEST_COUT << " - Instruccion [" << i << "]: " << op.funcName << "(" << (op.type == VOID_FUNC && op.funcName != "pop" ? std::to_string(op.param) : "") << ")" << std::endl;

			int poppedValue = INT_MIN;
			ASSERT_DURATION_LE(100, poppedValue = stackOps.at(op.funcName)(minStack, op.param);)

				if (op.type == INT_FUNC) {
					ASSERT_EQ(poppedValue, op.expected) << "Error en la instruccion [" << i << "] -> " << op.funcName << "()"
						<< ".\nSe esperaba [" << op.expected << "], pero se encontro [" << poppedValue << "]";
				}
		}
	}

	INSTANTIATE_TEST_CASE_P(E03Min, E03Tests, ValuesIn(E03Tests::ReadParams()));
}
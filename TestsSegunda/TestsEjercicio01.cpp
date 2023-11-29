#include "pch.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "../PAT_SegundaConvocatoria/Ejercicio01.h"
#include "../PAT_SegundaConvocatoria/Ejercicio01.cpp"

using ::testing::TestWithParam;
using ::testing::ValuesIn;
using std::vector;
using std::tuple;

namespace SegundaTests {

	class E01Test : public TestWithParam<tuple<int, vector<string>>> {
	protected:
		Ejercicio01* e01;

		int n;
		vector<string> expectedResult;

		void SetUp() override {
			e01 = new Ejercicio01();
			std::tie(n, expectedResult) = GetParam();
		}

		void TearDown() override {
			delete e01;
			e01 = nullptr;
		}

	public:
		static vector<tuple<int, vector<string>>> GetTestParams() {
			vector<tuple<int, vector<string>>> params;

			params.push_back(tuple<int, vector<string>>(3, vector<string>{"((()))", "(()())", "(())()", "()(())", "()()()"}));
			params.push_back(tuple<int, vector<string>>(1, vector<string>{"()"}));

			std::ifstream paramsFile("parenthesis.csv");
			string line;

			while (std::getline(paramsFile, line)) {
				std::stringstream strStream(line);

				string sn;
				std::getline(strStream, sn, ',');

				int n = std::stoi(sn);

				vector<string> results;
				while (std::getline(strStream, sn, ',')) {
					results.push_back(sn);
				}

				params.push_back(tuple<int, vector<string>>(n, results));
			}

			return params;
		}

	};

	TEST_P(E01Test, E01Parenthesis) {
		vector<string> result = e01->generateParenthesis(n);

		EXPECT_EQ(expectedResult.size(), result.size()) << "La cantidad de combinaciones de parentesis (" << result.size() << ") no coincide con la esperada (" << expectedResult.size() << ").";

		std::sort(result.begin(), result.end());
		std::sort(expectedResult.begin(), expectedResult.end());

		for (int i = 0; i < expectedResult.size() && i < result.size(); i++) {
			EXPECT_EQ(expectedResult[i], result[i]) << "Una de las combinaciones no coincide con las esperadas.";
		}
	}

	INSTANTIATE_TEST_CASE_P(E01Parenthesis,
		E01Test,
		ValuesIn(E01Test::GetTestParams()));

}
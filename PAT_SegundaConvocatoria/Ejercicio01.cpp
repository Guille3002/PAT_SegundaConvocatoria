#include "Ejercicio01.h"

vector<string> Ejercicio01::generateParenthesis(int n) {
    vector<string> result;
    generateParenthesisHelper("", 0, 0, n, result);
    return result;
}

void Ejercicio01::generateParenthesisHelper(string current, int open, int close, int n, vector<string>& result) {
    if (current.size() == 2 * n) {
        result.push_back(current);
        return;
    }

    if (open < n) {
        generateParenthesisHelper(current + '(', open + 1, close, n, result);
    }

    if (close < open) {
        generateParenthesisHelper(current + ')', open, close + 1, n, result);
    }
}


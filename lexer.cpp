#include <iostream>
#include <fstream>
#include <unordered_set>
#include <cctype>

using namespace std;

// Keywords
unordered_set<string> keywords = {
    "int", "float", "return", "if", "else", "while", "for", "char", "bool", "void", "double"
};

// Operators
unordered_set<string> operators = {
    "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">="
};

// Symbols
unordered_set<char> symbols = {
    '(', ')', '{', '}', ';', ','
};

// Check keyword
bool isKeyword(const string& word) {
    return keywords.count(word);
}

// Check operator
bool isOperator(const string& op) {
    return operators.count(op);
}

// Check symbol
bool isSymbol(char ch) {
    return symbols.count(ch);
}

int main() {
    ifstream codeFile("Code.txt");
    ofstream tokenFile("tokens.txt");

    char ch;
    string buffer = "";

    while (codeFile.get(ch)) {

        // Ignore spaces
        if (isspace(ch)) continue;

        // IDENTIFIER / KEYWORD
        if (isalpha(ch) || ch == '_') {
            buffer = ch;
            while (isalnum(codeFile.peek()) || codeFile.peek() == '_') {
                buffer += codeFile.get();
            }

            if (isKeyword(buffer))
                tokenFile << "[KEYWORD] " << buffer << endl;
            else
                tokenFile << "[IDENTIFIER] " << buffer << endl;
        }

        // NUMBER (INTEGER + FLOAT)
        else if (isdigit(ch)) {
            buffer = ch;
            bool isFloat = false;

            while (isdigit(codeFile.peek()) || codeFile.peek() == '.') {
                if (codeFile.peek() == '.') isFloat = true;
                buffer += codeFile.get();
            }

            if (isFloat)
                tokenFile << "[FLOAT] " << buffer << endl;
            else
                tokenFile << "[NUMBER] " << buffer << endl;
        }

        // STRING LITERAL
        else if (ch == '"') {
            buffer = "";
            while (codeFile.get(ch) && ch != '"') {
                buffer += ch;
            }
            tokenFile << "[STRING] " << buffer << endl;
        }

        // COMMENTS (single line)
        else if (ch == '/' && codeFile.peek() == '/') {
            while (codeFile.get(ch) && ch != '\n');
            tokenFile << "[COMMENT] single-line ignored\n";
        }

        // COMMENTS (multi-line)
        else if (ch == '/' && codeFile.peek() == '*') {
            codeFile.get(); // skip *
            while (codeFile.get(ch)) {
                if (ch == '*' && codeFile.peek() == '/') {
                    codeFile.get();
                    break;
                }
            }
            tokenFile << "[COMMENT] multi-line ignored\n";
        }

        // OPERATORS (including double)
        else if (string("+-*/%=<>!").find(ch) != string::npos) {
            buffer = ch;

            if (codeFile.peek() == '=') {
                buffer += codeFile.get();
            }

            if (isOperator(buffer)) {
                if (buffer == "=")
                    tokenFile << "[ASSIGN] " << buffer << endl;
                else if (buffer == "+" || buffer == "-" || buffer == "*" || buffer == "/")
                    tokenFile << "[ARITH_OP] " << buffer << endl;
                else
                    tokenFile << "[REL_OP] " << buffer << endl;
            }
        }

        // SYMBOLS
        else if (isSymbol(ch)) {
            tokenFile << "[SYMBOL] " << ch << endl;
        }

        // ERROR / UNKNOWN
        else {
            tokenFile << "[INVALID] " << ch << endl;
        }
    }

    codeFile.close();
    tokenFile.close();

    return 0;
}
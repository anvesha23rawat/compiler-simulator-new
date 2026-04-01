#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <regex>

using namespace std;

unordered_set<string> keywords = {
    "int", "float", "return", "if", "else", "while", "for", "char", "bool", "void", "double", "include"
};

bool isKeyword(const string& word) {
    return keywords.count(word);
}

int main() {
    ifstream codeFile("Code.txt");
    ofstream tokenFile("tokens.txt");

    string line;
    while (getline(codeFile, line)) {
        istringstream iss(line);
        string word;
        while (iss >> word) {
            if (isKeyword(word)) {
                tokenFile << "[KEYWORD] " << word << "\n";
            } else if (regex_match(word, regex("[a-zA-Z_][a-zA-Z0-9_]*"))) {
                tokenFile << "[IDENTIFIER] " << word << "\n";
            } else if (regex_match(word, regex("[0-9]+"))) {
                tokenFile << "[NUMBER] " << word << "\n";
            } else {
                tokenFile << "[SYMBOL] " << word << "\n";
            }
        }
    }

    codeFile.close();
    tokenFile.close();

    return 0;
}

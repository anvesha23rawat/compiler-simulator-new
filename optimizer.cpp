#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool isNumber(const string &s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return !s.empty();
}

int main() {
    ifstream in("tac.txt");
    ofstream out("optimized.txt");

    string line;
    out << "--- Optimized Code (Constant Folding) ---\n";

    while (getline(in, line)) {

        // Skip header lines
        if (line.find("---") != string::npos) {
            continue;
        }

        stringstream ss(line);
        string lhs, eq, op1, oper, op2;

        ss >> lhs >> eq >> op1 >> oper >> op2;

        // Check valid TAC pattern
        if (eq == "=" && !lhs.empty()) {

            if (isNumber(op1) && isNumber(op2)) {
                int a = stoi(op1);
                int b = stoi(op2);
                int result = 0;

                if (oper == "+") result = a + b;
                else if (oper == "-") result = a - b;
                else if (oper == "*") result = a * b;
                else if (oper == "/") result = (b != 0 ? a / b : 0);

                out << lhs << " = " << result << endl;
            } else {
                out << line << endl;
            }

        } else {
            out << line << endl;
        }
    }

    return 0;
}
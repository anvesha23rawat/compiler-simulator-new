#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "parser.h"

using namespace std;

int tempCount = 1;
int labelCount = 1;

string newTemp() {
    return "t" + to_string(tempCount++);
}

string newLabel() {
    return "L" + to_string(labelCount++);
}

// Generate TAC from AST
string generateTAC(shared_ptr<ASTNode> node, ofstream &out) {
    if (!node) return "";

    // ---------------- LITERAL / IDENTIFIER ----------------
    if (node->type == "Literal" || node->type == "Identifier") {
        return node->value;
    }

    // ---------------- ASSIGNMENT ----------------
    if (node->type == "Assignment") {
        string lhs = node->value;

        if (node->children.size() == 1) {
            string rhs = generateTAC(node->children[0], out);
            out << lhs << " = " << rhs << endl;
            return lhs;
        }

        string left = generateTAC(node->children[0], out);

        for (size_t i = 1; i < node->children.size(); i += 2) {
            string op = node->children[i]->value;
            string right = generateTAC(node->children[i+1], out);

            string temp = newTemp();
            out << temp << " = " << left << " " << op << " " << right << endl;

            left = temp;
        }

        out << lhs << " = " << left << endl;
        return lhs;
    }

    // ---------------- IF STATEMENT ----------------
    if (node->type == "If") {
        string labelTrue = newLabel();
        string labelEnd = newLabel();

        auto cond = node->children[0];

        string left = cond->children[0]->value;
        string op = cond->children[1]->value;
        string right = cond->children[2]->value;

        // IF condition
        out << "if " << left << " " << op << " " << right << " goto " << labelTrue << endl;
        out << "goto " << labelEnd << endl;

        // TRUE block
        out << labelTrue << ":" << endl;

        // (Currently no body, but structure ready)

        // END label
        out << labelEnd << ":" << endl;

        return "";
    }

    // ---------------- DEFAULT TRAVERSAL ----------------
    for (auto &child : node->children) {
        generateTAC(child, out);
    }

    return "";
}

int main() {
    auto root = parseCode("Code.txt");

    ofstream out("tac.txt");

    if (!root) {
        out << "Error generating TAC\n";
        return 1;
    }

    out << "--- Three Address Code ---\n";
    generateTAC(root, out);

    out.close();

    return 0;
}
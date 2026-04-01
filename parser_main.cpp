#include <iostream>
#include <fstream>
#include <memory>
#include "parser.h"

void printAST(const std::shared_ptr<ASTNode>& node, std::ostream& out, int depth = 0) {
    if (!node) return;
    out << std::string(depth * 2, ' ') << node->type;
    if (!node->value.empty())
        out << ": " << node->value;
    out << "\n";
    for (const auto& child : node->children) {
        printAST(child, out, depth + 1);
    }
}

int main() {
    std::shared_ptr<ASTNode> root = parseCode("Code.txt");  // Read from frontend input file
    std::ofstream out("parse.txt");

    if (!root) {
        out << "Parse Error: Failed to parse code.\n";
        return 1;
    }

    out << "--- Parsed AST ---\n";
    printAST(root, out);
    return 0;
}

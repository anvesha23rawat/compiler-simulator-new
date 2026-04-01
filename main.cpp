#include <iostream>
#include <memory>
#include <fstream>
#include "parser.h"
#include "semantic.h"

int main() {
    std::shared_ptr<ASTNode> root = parseCode("Code.txt");

    // Open file to write semantic errors and symbol table
    std::ofstream outfile("semantic.txt");
    if (!outfile) {
        std::cerr << "Error: Could not open semantic.txt for writing\n";
        return 1;
    }

    // Redirect std::cerr to semantic.txt for semantic errors
    std::streambuf* original_cerr = std::cerr.rdbuf();
    std::cerr.rdbuf(outfile.rdbuf());

    SemanticAnalyzer analyzer;
    analyzer.analyze(root);

    // Restore cerr
    std::cerr.rdbuf(original_cerr);

    // Write symbol table to semantic.txt after errors
    outfile << "--- Symbol Table ---\n";
    const auto& table = analyzer.getSymbolTable();
    for (const auto& entry : table) {
        outfile << entry.first << " : " << entry.second << "\n";
    }

    outfile.close();

    return 0;
}

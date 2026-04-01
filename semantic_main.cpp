#include <fstream>
#include <iostream>
#include <memory>
#include "parser.h"
#include "semantic.h"

int main() {
    auto root = parseCode("Code.txt");
    SemanticAnalyzer analyzer;

    std::ofstream outfile("semantic.txt");
    if (!outfile) {
        std::cerr << "Error: Could not open semantic.txt for writing\n";
        return 1;
    }

    // Redirect cout and cerr to the file stream
    std::streambuf* coutbuf = std::cout.rdbuf();
    std::streambuf* cerrbuf = std::cerr.rdbuf();

    std::cout.rdbuf(outfile.rdbuf());
    std::cerr.rdbuf(outfile.rdbuf());

    std::cout << "--- Semantic Analysis ---\n";
    analyzer.analyze(root);
    analyzer.print();

    // Restore cout and cerr
    std::cout.rdbuf(coutbuf);
    std::cerr.rdbuf(cerrbuf);

    outfile.close();

    return 0;
}

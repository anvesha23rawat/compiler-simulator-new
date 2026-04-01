#include "ast.h"
#include "semantic.h"
#include <memory>

int main() {
    // Simulated program: int x = 5; int y = 10; int z = x + y;

    // Build AST
    auto root = std::make_shared<ASTNode>("Program", "");

    auto decl1 = std::make_shared<ASTNode>("Declaration", "x");
    decl1->children.push_back(std::make_shared<ASTNode>("Type", "int"));
    decl1->children.push_back(std::make_shared<ASTNode>("Value", "5"));

    auto decl2 = std::make_shared<ASTNode>("Declaration", "y");
    decl2->children.push_back(std::make_shared<ASTNode>("Type", "int"));
    decl2->children.push_back(std::make_shared<ASTNode>("Value", "10"));

    auto decl3 = std::make_shared<ASTNode>("Declaration", "z");
    decl3->children.push_back(std::make_shared<ASTNode>("Type", "int"));

    auto expr = std::make_shared<ASTNode>("Expression", "+");
    expr->children.push_back(std::make_shared<ASTNode>("Variable", "x"));
    expr->children.push_back(std::make_shared<ASTNode>("Variable", "y"));
    decl3->children.push_back(expr);

    root->children.push_back(decl1);
    root->children.push_back(decl2);
    root->children.push_back(decl3);

    // Print AST
    std::cout << "\n--- Abstract Syntax Tree ---\n";
    printAST(root);

    // Semantic Analysis
    std::cout << "\n--- Semantic Analysis ---\n";
    analyzer.insert("x", "int");
    analyzer.insert("y", "int");
    analyzer.insert("z", "int");
    analyzer.print();

    return 0;
}

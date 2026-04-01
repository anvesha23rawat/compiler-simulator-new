#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <string>
#include <unordered_map>
#include <memory>
#include "ast.h"  // Your ASTNode definition
class SemanticAnalyzer {
private:
    std::unordered_map<std::string, std::string> symbolTable;
    // Recursively check used variables in expression subtree
    void checkUsedVariables(const std::shared_ptr<ASTNode>& exprNode) const;

public:
    // Insert declaration (warn on redeclaration)
    void insert(const std::string& name, const std::string& type);

    // Analyze the AST node recursively for semantic errors
    void analyze(const std::shared_ptr<ASTNode>& node);

    // Print the symbol table
    void print() const;
};

#endif // SEMANTIC_H

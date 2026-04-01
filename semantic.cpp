#include <iostream>
#include <memory>        // For std::shared_ptr
#include "parser.h"      // For parseCode and ASTNode
#include "semantic.h"    // For SemanticAnalyzer
using namespace std;


void SemanticAnalyzer::insert(const std::string& name, const std::string& type) {
    if (symbolTable.find(name) != symbolTable.end()) {
        std::cerr << "Warning: Redeclaration of variable '" << name << "'\n";
    }
    symbolTable[name] = type;
}

void SemanticAnalyzer::checkUsedVariables(const std::shared_ptr<ASTNode>& exprNode) const {
    if (!exprNode) return;

    // Check if node is variable usage
    if (exprNode->type == "Identifier" || exprNode->type == "Name") {
        const std::string& varName = exprNode->value;
        if (symbolTable.find(varName) == symbolTable.end()) {
            std::cerr << "Semantic Error: Undeclared variable '" << varName << "' used in expression\n";
        }
    }

    // Recursively check children
    for (const auto& child : exprNode->children) {
        checkUsedVariables(child);
    }
}

void SemanticAnalyzer::analyze(const std::shared_ptr<ASTNode>& node) {
    if (!node) return;

    for (const auto& child : node->children) {
        if (child->type == "Declaration") {
            // Extract variable type and name from children
            std::string varType, varName;
            for (const auto& gc : child->children) {
                if (gc->type == "Type")
                    varType = gc->value;
                else if (gc->type == "Name")
                    varName = gc->value;
            }
            if (!varName.empty() && !varType.empty())
                insert(varName, varType);
            else
                std::cerr << "Semantic Error: Invalid declaration node\n";
        }
        else if (child->type == "Assignment") {
            // LHS variable name stored in child->value
            std::string lhsVar = child->value;

            if (symbolTable.find(lhsVar) == symbolTable.end()) {
                std::cerr << "Semantic Error: Undeclared variable '" << lhsVar << "' on left side of assignment\n";
            }

            // Check RHS expression subtree for used variables
            for (const auto& exprChild : child->children) {
            checkUsedVariables(exprChild);
            }

        }

        // Recursively analyze nested children (e.g. nested blocks)
        analyze(child);
    }
}

void SemanticAnalyzer::print() const {
    std::cout << "--- Symbol Table ---\n";
    for (const auto& entry : symbolTable) {
        std::cout << entry.first << " : " << entry.second << "\n";
    }
}

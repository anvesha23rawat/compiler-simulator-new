#include <memory>
#include <string>
#include "ast.h"

std::shared_ptr<ASTNode> parseCode(const std::string& filename);

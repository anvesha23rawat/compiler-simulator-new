// token.h
#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    NUMBER,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN,
    END
};

struct Token {
    TokenType type;
    std::string value;
};

#endif

#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include "tokens.hpp"

class Lexer {
private:
    std::string input;
    size_t position;
    char currentChar;
    int line;
    int column;

    void advance();
    char peek();
    void skipWhitespace();
    Token matchNumber();
    Token matchIdentifierOrKeyword();
    Token matchOperator();


public:
    Lexer(const std::string& input);
    char getCurrentChar() const { return currentChar; }
    int getLine() const { return line; }
    int getColumn() const { return column; }
    
    Token getNextToken();
    Token getFirstToken();
};

#endif 
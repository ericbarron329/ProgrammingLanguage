#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include "ast.hpp"

class Parser {
private:
    Lexer lexer;
    Token currentToken;

    void advance();
    void expect(TokenType type);

    ASTNode* parseStatement();
    ASTNode* parseLetStatement();
    ASTNode* parsePrintStatement();
    ASTNode* parseExpression();
    ASTNode* parseTerm();
    ASTNode* parseFactor();

public:
    Parser(Lexer lexer);
    ASTNode* parseProgram();
};

#endif
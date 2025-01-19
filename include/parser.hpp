#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include "ast.hpp"

class Parser {
private:
    Lexer lexer;
    Token currentToken;

    void advance();

    ASTNode* parseStatement();
    ASTNode* parseLetStatement();
    ASTNode* parsePrintStatement();
    ASTNode* parseExpression();
    ASTNode* parseTerm();
    ASTNode* parseFactor();
    void expect(TokenType type);

public:
    Parser(Lexer lexer);
    ASTNode* parseProgram();
};

#endif
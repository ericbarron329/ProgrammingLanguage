#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include "ast.hpp"

class Parser {
public:
    Lexer& lexer;
    Token currentToken;

    void advance();
    void expect(TokenType type);

public:
    ASTNode* parseStatement();
    ASTNode* parseLetStatement();
    ASTNode* parsePrintStatement();
    ASTNode* parseExpression();
    ASTNode* parseTerm();
    ASTNode* parseFactor();

    Parser(Lexer &lexer);
    ASTNode* parseProgram();
};

#endif
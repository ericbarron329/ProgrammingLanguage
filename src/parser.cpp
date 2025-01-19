#include "../include/parser.hpp"
#include <iostream>

Parser::Parser(Lexer lexer) : lexer(lexer), currentToken(lexer.getNextToken()) {
}

void Parser::advance() {
    currentToken = lexer.getNextToken();
}

void Parser::expect(TokenType type) {
    if (currentToken.type == type) {
        advance();
    } else {
        std::cout << "Error: Expected " << type
        << " but found " << currentToken.type 
        << " at line " << lexer.getLine() 
        << ", column " << lexer.getColumn() << std::endl;
    }
}

ASTNode* Parser::parseLetStatement() {
    std::string identifier;
    ASTNode* value;

    expect(TokenType::LET);
    expect(TokenType::IDENTIFIER);
    identifier = currentToken.value;
    expect(TokenType::EQUAL);
    value = parseExpression();
    expect(TokenType::SEMICOLON);

    LetStatement* letStatement = new LetStatement(identifier, value);
    return letStatement;
}

ASTNode* Parser::parseExpression() {
    
}
#include "../include/parser.hpp"
#include <iostream>

Parser::Parser(Lexer lexer) : lexer(lexer) {
    currentToken = lexer.getNextToken();
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
        exit(1);
    }
}

// let number === 98234;
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

    std::cout   << "LetStatement: identifier = " << identifier
                << ", value = " << static_cast<NumberLiteral*>(value)->value << std::endl;
    return letStatement;
}

ASTNode* Parser::parseExpression() {
    if (currentToken.type == TokenType::NUMBER) {
        int tokenNumber = std::stoi(currentToken.value);
        NumberLiteral* numberLiteral = new NumberLiteral(tokenNumber);
        advance();
        return numberLiteral;
    } else if (currentToken.type == TokenType::IDENTIFIER) {
        std::string identifierValue = currentToken.value;
        Identifier* identifier = new Identifier(identifierValue);
        advance();
        return identifier;
    } else if (currentToken.type == TokenType::LEFT_PAREN) {
        advance();
        ASTNode* expression = parseExpression();
        expect(TokenType::RIGHT_PAREN);
        return expression;
    } else {
        std::cerr   << "Error: Unexpected token " << currentToken.value
                    << " at line " << lexer.getLine()
                    << ", column " << lexer.getColumn() << std::endl;
        exit(1); 
    }
}
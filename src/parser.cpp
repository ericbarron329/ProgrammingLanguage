#include "../include/parser.hpp"
#include <iostream>

Parser::Parser(Lexer &lexer) : lexer(lexer) {
    currentToken = lexer.getNextToken();
}

void Parser::advance() {
    currentToken = lexer.getNextToken();
}

void Parser::expect(TokenType expectedToken) {
    if (currentToken.type == expectedToken) {
        std::cout << "token matches: " << expectedToken << "!" << std::endl;
        advance();
        std::cout << "Moving to this new token: " << currentToken.type << " " << currentToken.value << std::endl;
        // advance();
        // std::cout << "Moving to this new token 2: " << currentToken.type << " " << currentToken.value << std::endl;
        
    } else {
        std::cout << "Error: Expected " << expectedToken
        << " but found " << currentToken.type 
        << " at line " << lexer.getLine() 
        << ", column " << lexer.getColumn() << std::endl;
        exit(1);
    }
}

ASTNode* Parser::parseLetStatement() {
    std::string identifier;
    ASTNode* value;
    expect(TokenType::LET);
    // std::cout << currentToken.type << " " << currentToken.value << std::endl;
    // advance();
    // identifier = currentToken.value;
    // expect(TokenType::IDENTIFIER);
    // expect(TokenType::EQUAL);
    // value = parseExpression();
    // expect(TokenType::SEMICOLON);

    LetStatement* letStatement = new LetStatement(identifier, value);

    // std::cout   << "LetStatement: identifier = " << identifier
    //             << ", value = " << static_cast<NumberLiteral*>(value)->value << std::endl;
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
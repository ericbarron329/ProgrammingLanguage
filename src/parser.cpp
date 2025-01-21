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
        // std::cout << "token matches: " << expectedToken << "!" << std::endl;
        advance();
    } else {
        std::cout << "Error: Expected " << expectedToken
        << " but found " << currentToken.type 
        << " at line " << lexer.getLine() 
        << ", column " << lexer.getColumn() << std::endl;
        exit(1);
    }
}

ASTNode* Parser::parseStatement() {
    if (currentToken.type == TokenType::LET) {
        return parseLetStatement();
    } else if (currentToken.type == TokenType::PRINT) {
        return parsePrintStatement();
    } else {
        std::cerr << "Error: Invalid token statement" << std::endl;
        exit(1);
    }
}

ASTNode* Parser::parseLetStatement() {
    std::string identifier;
    ASTNode* value;
    expect(TokenType::LET);
    identifier = currentToken.value;
    expect(TokenType::IDENTIFIER);
    expect(TokenType::EQUAL);
    value = parseExpression();
    expect(TokenType::SEMICOLON);

    LetStatement* letStatement = new LetStatement(identifier, value);
    return letStatement;
}

ASTNode* Parser::parsePrintStatement() {
    ASTNode* printValue;
    
    expect(TokenType::PRINT); 
    printValue = parseExpression();
    expect(TokenType::SEMICOLON);

    PrintStatement* printStatement = new PrintStatement(printValue);
    return printStatement;
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

ASTNode* Parser::parseProgram() {
    std::vector<ASTNode*> statements;

    while (currentToken.type != TokenType::END_OF_FILE) {
        ASTNode* statement = parseStatement();
        if (statement != nullptr) {
            statements.push_back(statement);
        }
    }

    Program* program = new Program(statements);
    return program;
}
#include "../include/lexer.hpp"
#include <string>
#include <iostream>

Lexer::Lexer(const std::string& input) {
    this->input = input;
    position = 0;
    currentChar = input.empty() ? '\0' : input[0];
    line = 1;
    column = 1;
}

void Lexer::advance() {
    // Check if were at end of string
    if (input.size() > position) {
        if (currentChar == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        position++;
        currentChar = input[position];
    } else {
        currentChar = '\0';
    }
}

Token Lexer::getNextToken() {
    skipWhitespace();

    if (isalpha(currentChar)) {
        // Alphanumeric Token
        return matchIdentifierOrKeyword();
    } else if (isdigit(currentChar)) {
        // Digit Token
        return matchNumber();
    } else if (currentChar == '+' || currentChar == '-' || currentChar == '/' || currentChar == '*' || currentChar == ';' || currentChar == '<' || currentChar == '>' || currentChar == '=' || currentChar == '(' || currentChar == ')' || currentChar == '"') {
        // Operator Token
        return matchOperator();
    } else if (currentChar == '\0') {
        // EOF Token
        return Token(TokenType::END_OF_FILE, "", line, column);
    } else {
        // Unknown Token
        Token unknown(TokenType::UNKNOWN, std::string(1, currentChar), line, column);
        advance();
        return unknown;
    }
}

char Lexer::peek() {
    if (input.size() > position + 1) {
        return input[position + 1];
    } else {
        return '\0';
    }
}

void Lexer::skipWhitespace() {
    while (isspace(currentChar)) {
        advance();
    }
}

Token Lexer::matchNumber() {

    std::string value = "";
    int startLine = line;
    int startColumn = column;

    // Retrieves the entire number
    while (isdigit(currentChar)) {
        value += currentChar;
        advance();
    }

    // Generates token
    Token token(TokenType::NUMBER, value, startLine, startColumn);
    return token;
}

Token Lexer::matchIdentifierOrKeyword() {

    TokenType currentType;
    std::string value = "";
    int startLine = line;
    int startColumn = column;

    // Retrieves the entire number
    while (isalpha(currentChar)) {
        value += currentChar;
        advance();
    }

    // Generates token
    if (value == "let") {
        currentType = TokenType::LET;
    } else if (value == "print") {
        currentType = TokenType::PRINT;
    } else {
        currentType = TokenType::IDENTIFIER;
    }

    Token token(currentType, value, startLine, startColumn);
    return token;

}

Token Lexer::matchOperator() {

    TokenType currentType;
    int startLine = line;
    int startColumn = column;
    std::string value(1, currentChar);

    switch(currentChar) {

        case '+': currentType = TokenType::PLUS; advance(); break;
        case '-': currentType = TokenType::MINUS; advance(); break;
        case '*': currentType = TokenType::MULTIPLY; advance(); break;
        case '/': currentType = TokenType::DIVIDE; advance(); break;
        case '=':
            if (peek() == '=') {
                currentChar += '=';
                advance();
                currentType = TokenType::COMPARE; break;
            } else {
                advance();
                currentType = TokenType::EQUAL; break;
            }
            break;
        case '<': currentType = TokenType::LESS_THAN; advance(); break;
        case '>': currentType = TokenType::GREATER_THAN; advance(); break;
        case ';': currentType = TokenType::SEMICOLON; advance(); break;
        case '(': currentType = TokenType::LEFT_PAREN; advance();break;
        case ')': currentType = TokenType::RIGHT_PAREN; advance(); break;
        case '"': {
            currentType = TokenType::STRING; 
            advance();

            while (currentChar != '"' && currentChar != '\0') {
                value += currentChar;
                advance();
            }
            if (currentChar == '"') {
                advance();
            } else {
                std::cerr << "Error: string must end with \" " << std::endl;
                currentType = TokenType::UNKNOWN;
            }
            value.erase(0,1);
            break;
        }
        default:
            currentType = TokenType::UNKNOWN; break;
    }

    return Token(currentType, value, startLine, startColumn);
}
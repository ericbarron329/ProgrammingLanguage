#include <string>
enum TokenType {
    LET,
    PRINT,
    IDENTIFIER,
    NUMBER,
    PLUS,
    MINUS,
    DIVIDE,
    MULTIPLY,
    EQUAL,
    LESS_THAN,
    GREATER_THAN,
    SEMICOLON,
    LEFT_PAREN,
    RIGHT_PAREN,
    END_OF_FILE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;

    Token() : type(TokenType::UNKNOWN), value(""), line(0), column(0) {}

    Token(TokenType t, const std::string& v, int l = 0, int c = 0) 
    : type(t), value(v), line(l), column(c) {

    }
};
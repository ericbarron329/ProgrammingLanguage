#include <iostream>
#include "../include/lexer.hpp"
using namespace std;

int main() {

    std::string code = "let x = 10;\nprint x;\nif x > 5 then print x;";
    Lexer lexer(code);

    // while (lexer.getCurrentChar() != '\0') {
    //     std::cout   << "Current Char: " << lexer.getCurrentChar()
    //                 << ", Line: " << lexer.getLine()
    //                 << ", Column: " << lexer.getColumn() << std::endl;
    //     lexer.advance();
    // }


    // This is to test is the lexer works correctly
    while (lexer.getCurrentChar() != '\0') {
        Token t = lexer.getNextToken();
        std::cout << t.value << endl;
    }

    return 0;
}
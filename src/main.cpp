#include <iostream>
#include "../include/lexer.hpp"
#include "../include/parser.hpp"

int main() {

    std::string code = "let x = 10;";

    Lexer lexer(code);
    Parser parser(lexer);

    // // Used to test Lexer
    // while (lexer.getCurrentChar() != '\0') {
    //     Token t = lexer.getNextToken();
    //     std::cout << t.value << t.type << std::endl;
    // }

    // Parser testing
    std::cout << parser.currentToken.type << " " << parser.currentToken.value << std::endl;
    parser.parseLetStatement();
    std::cout << "Worked!" << std::endl;


    return 0;
}
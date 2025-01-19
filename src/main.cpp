#include <iostream>
#include "../include/lexer.hpp"
#include "parser.hpp"

int main() {

    std::string code = "let x = 10;";

    Lexer lexer(code);
    // Parser parser(lexer);

    while (lexer.getCurrentChar() != '\0') {
        std::cout << lexer.getNextToken().value << std::endl;
    }

    return 0;
}
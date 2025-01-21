#include <iostream>
#include <fstream>
#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include <sstream>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Filed to open file: " + filename);
    }

    std::string line;
    std::string content;

    while (std::getline(file, line)) {
        content += line + '\n';
    }

    return content;
}

int main() {
    // File management
    std::string code = readFile("code.bucket");
    std::cout << code << std::endl;
    // Programming logic
    Lexer lexer(code);
    Parser parser(lexer);

    // // Used to test Lexer
    // while (lexer.getCurrentChar() != '\0') {
    //     Token t = lexer.getNextToken();
    //     std::cout << t.value << "\t" << t.type << std::endl;
    // }

    // Parser testing
    ASTNode* parsedProgram = parser.parseProgram();

    return 0;
}
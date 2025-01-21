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

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {

    // File management
    std::string code = readFile("code.bucket");

    // Programming logic
    Lexer lexer(code);
    Parser parser(lexer);

    // Used to test Lexer
    // while (lexer.getCurrentChar() != '\0') {
    //     Token t = lexer.getNextToken();
    //     std::cout << t.value << "\t" << t.type << std::endl;
    // }

    // Parser testing
    ASTNode* program = parser.parseProgram();
    std::cout << program->toString() << std::endl;
    delete program;

    
    return 0;
}
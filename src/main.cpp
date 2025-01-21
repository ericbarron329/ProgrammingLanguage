#include <iostream>
#include "ast.hpp"
#include "interpreter.hpp"

int main() {
    // program equivalent to:
    // let x = 10
    // print (x + 20)
    // print "Hello"

    // 1) Construct AST by hand:
    // let x = 10
    auto* letX = new LetStatement("x", new NumberLiteral(10));

    // print (x + 20)
    auto* print1 = new PrintStatement(
        new BinaryExpression("+", new Identifier("x"), new NumberLiteral(20))
    );

    // print "Hello"
    auto* print2 = new PrintStatement(
        new StringLiteral("Hello")
    );

    // Make a vector of statements
    std::vector<ASTNode*> stmts = { letX, print1, print2 };

    // Build the Program node
    auto* program = new Program(stmts);

    // 2) Interpret
    Interpreter interpreter;
    interpreter.interpret(program);

    // 3) Cleanup
    delete program; // This will recursively delete all contained AST nodes
    return 0;
}

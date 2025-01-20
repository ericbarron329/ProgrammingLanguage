#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>

class ASTNode {
public:
    virtual ~ASTNode() = default;
};

class LetStatement : public ASTNode {
public:
    std::string identifier;
    ASTNode* value;
    LetStatement(const std::string& id, ASTNode* val) : identifier(id), value(val) {}
};

class PrintStatement : public ASTNode {
public:
    ASTNode* value;
    PrintStatement(ASTNode* val) : value(val) {}
};

class BinaryExpression : public ASTNode {
public:
    std::string op;
    ASTNode* left;
    ASTNode* right;
    BinaryExpression(const std::string& oper, ASTNode* lhs, ASTNode* rhs) 
    : op(oper), left(lhs), right(rhs) {}
};

class NumberLiteral : public ASTNode {
public:
    int value;
    NumberLiteral(int val) : value(val) {}
};

class Identifier : public ASTNode {
public:
    std::string name;
    Identifier(const std::string& id) : name(id) {}

};

class Program : public ASTNode {
public:
    std::vector<ASTNode*> statements;
    Program(const std::vector<ASTNode*>& stmts) : statements(stmts) {}
};

#endif
#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual std::string toString() const = 0;
};

class LetStatement : public ASTNode {
public:
    std::string identifier;
    ASTNode* value;
    LetStatement(const std::string& id, ASTNode* val) : identifier(id), value(val) {}

    std::string toString() const override {
        return "Let Statement: " + identifier + "\tvalue: " + value->toString();
    }
};

class PrintStatement : public ASTNode {
public:
    ASTNode* value;
    PrintStatement(ASTNode* val) : value(val) {}

    std::string toString() const override {
        return "Print statement: " + value->toString();
    }
};

class BinaryExpression : public ASTNode {
public:
    std::string op;
    ASTNode* left;
    ASTNode* right;
    BinaryExpression(const std::string& oper, ASTNode* lhs, ASTNode* rhs) 
    : op(oper), left(lhs), right(rhs) {}

    std::string toString() const override {
        return "Binary Expression: " + op + " " + left->toString() + " " + right->toString();
    }
};

class NumberLiteral : public ASTNode {
public:
    int value;
    NumberLiteral(int val) : value(val) {}

    std::string toString() const override {
        return "Number Literal: " + std::to_string(value);
    }
};

class Identifier : public ASTNode {
public:
    std::string name;
    Identifier(const std::string& id) : name(id) {}

    std::string toString() const override {
        return "Identifier: " + name;
    }
};

class Program : public ASTNode {
public:
    std::vector<ASTNode*> statements;
    Program(const std::vector<ASTNode*>& stmts) : statements(stmts) {}

    std::string toString() const override {
        std::string res = "Program:\n";
        for (ASTNode* statement : statements) {
            res += " " + statement->toString() + "\n";
        }
        return res;
    }
};

#endif
#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include <variant>
#include "ast.hpp"

// A simple type to represent runtime values (int, string, or none)
enum class ValueType { INT, STRING, NONE };

class Value {
public:
    ValueType type;
    int intValue;
    std::string stringValue;

    Value() : type(ValueType::NONE), intValue(0), stringValue("") {}
    
    // Integer constructor
    Value(int i) : type(ValueType::INT), intValue(i), stringValue("") {}

    // String constructor
    Value(const std::string &s) : type(ValueType::STRING), intValue(0), stringValue(s) {}
};

// A lightweight Interpreter
class Interpreter {
private:
    // Environment: identifier -> Value
    std::unordered_map<std::string, Value> environment;

public:
    Value interpret(ASTNode* node);

private:
    Value interpretProgram(class Program* node);
    Value interpretLetStatement(class LetStatement* node);
    Value interpretPrintStatement(class PrintStatement* node);
    Value interpretBinaryExpression(class BinaryExpression* node);
    Value interpretNumberLiteral(class NumberLiteral* node);
    Value interpretIdentifier(class Identifier* node);
    Value interpretStringLiteral(class StringLiteral* node);

    // Utility for applying a binary operator
    Value applyBinaryOp(const std::string& op, const Value& leftVal, const Value& rightVal);
};

#endif

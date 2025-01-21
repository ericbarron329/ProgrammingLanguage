#include "interpreter.hpp"
#include <typeinfo>  // for typeid, dynamic_cast checks

Value Interpreter::interpret(ASTNode* node) {
    if (!node) {
        // No node => return none
        return Value();
    }

    // We'll attempt dynamic_cast on each known AST type
    if (auto* p = dynamic_cast<Program*>(node))          return interpretProgram(p);
    if (auto* ls = dynamic_cast<LetStatement*>(node))    return interpretLetStatement(ls);
    if (auto* ps = dynamic_cast<PrintStatement*>(node))  return interpretPrintStatement(ps);
    if (auto* be = dynamic_cast<BinaryExpression*>(node))return interpretBinaryExpression(be);
    if (auto* nl = dynamic_cast<NumberLiteral*>(node))   return interpretNumberLiteral(nl);
    if (auto* id = dynamic_cast<Identifier*>(node))      return interpretIdentifier(id);
    if (auto* sl = dynamic_cast<StringLiteral*>(node))   return interpretStringLiteral(sl);

    // If it's something else or unknown
    throw std::runtime_error("Unknown AST node type in interpret()");
}

// -------------------------------------------------------
// Individual node handlers

Value Interpreter::interpretProgram(Program* node) {
    // Interpret each statement in order
    // The value of a program is the value of the last statement (if any)
    Value lastValue;
    for (auto* stmt : node->statements) {
        lastValue = interpret(stmt);
    }
    return lastValue;
}

Value Interpreter::interpretLetStatement(LetStatement* node) {
    // Evaluate the value expression
    Value val = interpret(node->value);

    // Store it in the environment
    environment[node->identifier] = val;

    // Typically a statement has no resulting value => return none
    return Value();
}

Value Interpreter::interpretPrintStatement(PrintStatement* node) {
    // Evaluate the expression
    Value val = interpret(node->value);

    // Print the result
    switch (val.type) {
        case ValueType::INT:
            std::cout << val.intValue << std::endl;
            break;
        case ValueType::STRING:
            std::cout << val.stringValue << std::endl;
            break;
        default:
            std::cout << "None" << std::endl;
            break;
    }

    // "print" statement yields no value
    return Value();
}

Value Interpreter::interpretBinaryExpression(BinaryExpression* node) {
    // Evaluate left and right
    Value leftVal = interpret(node->left);
    Value rightVal = interpret(node->right);

    // Apply the operator (like +, -, etc.)
    return applyBinaryOp(node->op, leftVal, rightVal);
}

Value Interpreter::interpretNumberLiteral(NumberLiteral* node) {
    // Return as an integer value
    return Value(node->value);
}

Value Interpreter::interpretIdentifier(Identifier* node) {
    // Look up in environment
    auto it = environment.find(node->name);
    if (it == environment.end()) {
        throw std::runtime_error("Undefined variable: " + node->name);
    }
    return it->second;
}

Value Interpreter::interpretStringLiteral(StringLiteral* node) {
    // Return as a string value
    return Value(node->stringLiteral);
}

// -------------------------------------------------------
// Utility: apply a binary operator to two Value objects

Value Interpreter::applyBinaryOp(const std::string& op, const Value& leftVal, const Value& rightVal) {
    // If we wanted to support string concatenation with '+', etc.:
    if (op == "+") {
        // if both ints => add
        if (leftVal.type == ValueType::INT && rightVal.type == ValueType::INT) {
            return Value(leftVal.intValue + rightVal.intValue);
        }
        // if either is string => concatenate
        if (leftVal.type == ValueType::STRING || rightVal.type == ValueType::STRING) {
            std::string leftStr  = (leftVal.type == ValueType::STRING) 
                                     ? leftVal.stringValue 
                                     : std::to_string(leftVal.intValue);
            std::string rightStr = (rightVal.type == ValueType::STRING) 
                                     ? rightVal.stringValue 
                                     : std::to_string(rightVal.intValue);
            return Value(leftStr + rightStr);
        }
        // otherwise => error or "none"
        throw std::runtime_error("Invalid operands to '+'");
    }
    else if (op == "-") {
        if (leftVal.type == ValueType::INT && rightVal.type == ValueType::INT) {
            return Value(leftVal.intValue - rightVal.intValue);
        }
        throw std::runtime_error("Invalid operands to '-'");
    }
    else if (op == "*") {
        if (leftVal.type == ValueType::INT && rightVal.type == ValueType::INT) {
            return Value(leftVal.intValue * rightVal.intValue);
        }
        throw std::runtime_error("Invalid operands to '*'");
    }
    else if (op == "/") {
        if (leftVal.type == ValueType::INT && rightVal.type == ValueType::INT) {
            if (rightVal.intValue == 0) {
                throw std::runtime_error("Division by zero");
            }
            return Value(leftVal.intValue / rightVal.intValue);
        }
        throw std::runtime_error("Invalid operands to '/'");
    }

    // If we have more operators (==, <, >, etc.), implement them here
    throw std::runtime_error("Unknown operator: " + op);
}

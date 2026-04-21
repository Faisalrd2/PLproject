#include "Parser.h"
#include <stdexcept>
#include <string>

Parser::Parser(Scanner& scanner_ref) : scanner(scanner_ref) {
    // Load the very first token to start the parsing process
    currentToken = scanner.getNextToken();
}

void Parser::match(TokenType expectedType) {
    if (currentToken.type == expectedType) {
        currentToken = scanner.getNextToken();
    } else {
        throw std::runtime_error("Syntax Error: Unexpected token encountered.");
    }
}

// Parses the lowest level of precedence: numbers, imaginary units, and parentheses
Complex Parser::factor() {
    // Handle unary minus (e.g., the negative sign in "-2 + 3i")
    if (currentToken.type == TokenType::MINUS) {
        match(TokenType::MINUS);
        Complex value = factor();
        return Complex{-value.real, -value.imag};
    }

    // Handle numbers and implicit imaginary multiplication (e.g., "5" or "2i")
    if (currentToken.type == TokenType::NUMBER) {
        double val = currentToken.value;
        match(TokenType::NUMBER);
        
        // If an 'i' immediately follows a number, treat it as an imaginary value
        if (currentToken.type == TokenType::IMAGINARY_UNIT) {
            match(TokenType::IMAGINARY_UNIT);
            return Complex{0, val};
        }
        
        // Otherwise, it is just a standard real number
        return Complex{val, 0};
    }

    // Handle a standalone 'i'
    if (currentToken.type == TokenType::IMAGINARY_UNIT) {
        match(TokenType::IMAGINARY_UNIT);
        return Complex{0, 1};
    }

    // Handle parenthesized expressions
    if (currentToken.type == TokenType::LPAREN) {
        match(TokenType::LPAREN);
        Complex result = expr();
        match(TokenType::RPAREN);
        return result;
    }

    throw std::runtime_error("Syntax Error: Expected a number, 'i', or '('");
}

// Parses multiplication and division
Complex Parser::term() {
    Complex left = factor();

    while (currentToken.type == TokenType::MULTIPLY || currentToken.type == TokenType::DIVIDE) {
        if (currentToken.type == TokenType::MULTIPLY) {
            match(TokenType::MULTIPLY);
            Complex right = factor();
            
            // Complex multiplication formula: (a+bi)(c+di) = (ac-bd) + (ad+bc)i
            double newReal = (left.real * right.real) - (left.imag * right.imag);
            double newImag = (left.real * right.imag) + (left.imag * right.real);
            left = Complex{newReal, newImag};
            
        } else if (currentToken.type == TokenType::DIVIDE) {
            match(TokenType::DIVIDE);
            Complex right = factor();
            
            // Complex division requires multiplying by the conjugate
            double denominator = (right.real * right.real) + (right.imag * right.imag);
            if (denominator == 0) {
                throw std::runtime_error("Math Error: Division by zero.");
            }

            double newReal = ((left.real * right.real) + (left.imag * right.imag)) / denominator;
            double newImag = ((left.imag * right.real) - (left.real * right.imag)) / denominator;
            left = Complex{newReal, newImag};
        }
    }
    return left;
}

// Parses addition and subtraction (Highest level rule)
Complex Parser::expr() {
    Complex left = term();

    while (currentToken.type == TokenType::PLUS || currentToken.type == TokenType::MINUS) {
        if (currentToken.type == TokenType::PLUS) {
            match(TokenType::PLUS);
            Complex right = term();
            left = Complex{left.real + right.real, left.imag + right.imag};
            
        } else if (currentToken.type == TokenType::MINUS) {
            match(TokenType::MINUS);
            Complex right = term();
            left = Complex{left.real - right.real, left.imag - right.imag};
        }
    }
    return left;
}
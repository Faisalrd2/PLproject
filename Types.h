#ifndef TYPES_H
#define TYPES_H

// The mathematical heart of the interpreter
struct Complex {
    double real;
    double imag;
};

// Every possible symbol the language understands
enum class TokenType {
    NUMBER,
    IMAGINARY_UNIT, // For the 'i'
    PLUS,           // For '+'
    MINUS,          // For '-'
    MULTIPLY,       // For '*'
    DIVIDE,         // For '/'
    LPAREN,         // For '('
    RPAREN,         // For ')'
    END_OF_FILE     // To tell the parser to stop looking
};

// The package that the Scanner hands over to the Parser
struct Token {
    TokenType type;
    double value; // Only meaningful when type is NUMBER. Zero otherwise.
};

#endif
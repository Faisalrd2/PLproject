#include "Scanner.h"
#include <cctype>
#include <stdexcept>

Scanner::Scanner(const std::string& input_string) : input(input_string), position(0) {}

char Scanner::currentChar() const {
    if (position >= input.length()) {
        return '\0'; // Return null character if at the end of the input
    }
    return input[position];
}

void Scanner::advance() {
    position++;
}

Token Scanner::getNextToken() {
    while (currentChar() != '\0') {
        char c = currentChar();

        // Skip any initial white space (spaces, tabs, and newlines)
        if (std::isspace(c)) {
            advance();
            continue;
        }

        // Process single-character tokens for arithmetic and parentheses
        if (c == '+') {
            advance();
            return Token{TokenType::PLUS, 0.0};
        }
        if (c == '-') {
            advance();
            return Token{TokenType::MINUS, 0.0};
        }
        if (c == '*') {
            advance();
            return Token{TokenType::MULTIPLY, 0.0};
        }
        if (c == '/') {
            advance();
            return Token{TokenType::DIVIDE, 0.0};
        }
        if (c == '(') {
            advance();
            return Token{TokenType::LPAREN, 0.0};
        }
        if (c == ')') {
            advance();
            return Token{TokenType::RPAREN, 0.0};
        }

        // Process the imaginary unit
        if (c == 'i') {
            advance();
            return Token{TokenType::IMAGINARY_UNIT, 0.0};
        }

        // Process multi-digit integers
        if (std::isdigit(c)) {
            double value = 0;
            while (std::isdigit(currentChar())) {
                value = value * 10 + (currentChar() - '0');
                advance();
            }
            return Token{TokenType::NUMBER, value};
        }

        // If the character does not match any valid rules, announce an error
        throw std::runtime_error(std::string("Lexical Error: Unrecognized character '") + c + "'");
    }

    // Return an end-of-file token when the input is fully consumed
    return Token{TokenType::END_OF_FILE, 0.0};
}
#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <cstddef>
#include "Types.h"

// Lexical analyzer for the complex number expression language
class Scanner {
private:
    std::string input;
    size_t position;

    // Helper method to peek at the current character without consuming it
    char currentChar() const;

    // Helper method to move the scanner forward by one character
    void advance();

public:
    // Initializes the scanner with the string to be evaluated
    explicit Scanner(const std::string& input_string);

    // Reads the next valid sequence of characters and returns the corresponding token
    Token getNextToken();
};

#endif
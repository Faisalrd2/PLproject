#ifndef PARSER_H
#define PARSER_H

#include "Scanner.h"
#include "Types.h"

// Syntax analyzer and evaluator for the expression language
class Parser {
private:
    Scanner& scanner;
    Token currentToken;

    // Consumes the current token if it matches the expected type, otherwise throws a syntax error
    void match(TokenType expectedType);

    // Core recursive descent functions mapped to grammar rules
    Complex factor();
    Complex term();

public:
    // Initializes the parser with an active scanner and loads the first token
    explicit Parser(Scanner& scanner_ref);

    // The entry point for evaluating an expression
    Complex expr();

    // Returns the type of the token the parser is currently sitting on
    TokenType currentTokenType() const { return currentToken.type; }
};

#endif
#include <iostream>
#include <string>
#include <stdexcept>
#include "Scanner.h"
#include "Parser.h"

int main() {
    std::string inputLine;
    
    std::cout << "Complex Number Expression Interpreter" << std::endl;
    std::cout << "Type 'exit' or 'quit' to stop.\n" << std::endl;

    // The Read-Eval-Print Loop (REPL)
    while (true) {
        std::cout << ">> "; 
        
        // Capture the entire line, including spaces
        if (!std::getline(std::cin, inputLine)) {
            break; // Exit on EOF signal
        }

        // Process termination commands
        if (inputLine == "exit" || inputLine == "quit") {
            break;
        }
        
        // Ignore empty submissions
        if (inputLine.empty()) {
            continue;
        }

        try {
            // 1. Initialize lexical analysis with the input string
            Scanner scanner(inputLine);
            
            // 2. Initialize syntax analysis and pass the scanner dependency
            Parser parser(scanner);
            
            // 3. Trigger the evaluation at the highest precedence level
            Complex result = parser.expr();

            // 4. Ensure no unconsumed input remains
            if (parser.currentTokenType() != TokenType::END_OF_FILE) {
                throw std::runtime_error("Syntax Error: Unexpected token after expression.");
            }

            // 5. Format and display the output mathematically
            bool hasReal = (result.real != 0);
            bool hasImag = (result.imag != 0);

            if (!hasReal && !hasImag) {
                std::cout << "0\n";
            } else {
                if (hasReal) std::cout << result.real;
                if (hasImag) {
                    if (hasReal) std::cout << (result.imag > 0 ? " + " : " - ");
                    else if (result.imag < 0) std::cout << "-";
                    std::cout << (result.imag < 0 ? -result.imag : result.imag) << "i\n";
                } else {
                    std::cout << "\n";
                }
            }

        } catch (const std::exception& e) {
            // Catch and display syntax or math errors without crashing the loop
            std::cerr << e.what() << "\n";
        }
    }

    std::cout << "Execution terminated." << std::endl;
    return 0;
}
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "Lexer.h"


int main() {
    std::string input = "if";
    std::vector<Token> tokens = tokenizeCode(input);
    printTokenStream(tokens);
    return 0;
}

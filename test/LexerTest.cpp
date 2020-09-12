//
// Created by saikatc on 9/11/20.
//

#include "gtest/gtest.h"
#include <string>
#include <vector>
#include "../src/Lexer.h"
#include <iostream>

TEST(LexerTest, TestIf){
    std::string input = "if";
    for(Token& token : tokenizeCode(input)){
        std::cout << token.get_repr();
    }
}

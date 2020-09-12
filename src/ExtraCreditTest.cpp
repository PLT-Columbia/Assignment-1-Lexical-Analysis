//
// Created by Saikat Chakraborty on 9/12/20.
//

#include "gtest/gtest.h"
#include <string>
#include <vector>
#include "Lexer.h"

void checkVectorEquality(std::vector<Token> generated_tokens, std::vector<Token> expected_tokens){
    int gen_size = generated_tokens.size();
    int expected_size = expected_tokens.size();
    EXPECT_EQ(gen_size, expected_size);
    for(int i = 0; i < gen_size; i++){
        EXPECT_EQ(generated_tokens[i] , expected_tokens[i]);
    }
}

TEST(LexerTestExtraCredit, TestNumberError){
    std::string input = "n = 3.;";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_identifier, "n"), Token(type_assign_op, "="),
                                        Token(type_error, "Invalid Number")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(LexerTestExtraCredit, TestStringError){
    std::string input = "STR = \"Inv String;";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_identifier, "n"), Token(type_assign_op, "="),
                                        Token(type_error, "Invalid String")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}


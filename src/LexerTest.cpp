//
// Created by Saikat Chakraborty on 9/11/20.
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

TEST(LexerTest, TestOneToken){
    std::string input = "if";
    std::vector<Token> tokens = tokenizeCode(input);
    EXPECT_EQ(1, tokens.size());
}


TEST(LexerTest, TestAllKeywordsInASent){
    std::string input = "if else for while extern asm";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_keyword, "if"), Token(type_keyword, "else"),
                                        Token(type_keyword, "for"), Token(type_keyword, "while"),
                                        Token(type_keyword, "extern"), Token(type_keyword, "asm")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(LexerTest, TestString){
    std::string input = "STR = \"this is string\";";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_identifier, "STR"), Token(type_assign_op, "="),
                                        Token(type_string, "\"this is string\""), Token(type_semicolon, ";")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(LexerTest, TestNumber){
    std::string input = "n = 3.14;";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_identifier, "n"), Token(type_assign_op, "="),
                                        Token(type_number, "3.14"), Token(type_semicolon, ";")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(LexerTest, TesComment){
    std::string input = "//This is a comment line\nn = 0;";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_comment, "//This is a comment line"),
                                        Token(type_identifier, "n"), Token(type_assign_op, "="),
                                        Token(type_number, "0"), Token(type_semicolon, ";")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(LexerTest, TestFullCode){
    std::string input = "int main(){\n"
                        "   int n = 0;\n"
                        "   //This is a comment line\n"
                        "   string STR = \"this is string\";\n"
                        "   if (n >= 0){\n"
                        "       for(n = 0; n <= 10; n++){\n"
                        "           print(n);\n"
                        "       }\n"
                        "   }\n"
                        "}";
    // Expected Output
    std::vector<Token> expectedTokens(
            {Token(type_identifier, "int"), Token(type_identifier, "main"),
             Token(type_lpar, "("), Token(type_rpar, ")"),
             Token(type_lcurly_brace, "{"), Token(type_identifier, "int"),
             Token(type_identifier, "n"), Token(type_assign_op, "="),
             Token(type_number, "0"), Token(type_semicolon, ";"),
             Token(type_comment, "//This is a comment line"),
             Token(type_identifier, "string"), Token(type_identifier, "STR"),
             Token(type_assign_op, "="), Token(type_string, "\"this is string\""),
             Token(type_semicolon, ";"), Token(type_keyword, "if"),
             Token(type_lpar, "("), Token(type_identifier, "n"),
             Token(type_binop, ">="), Token(type_number, "0"), Token(type_rpar, ")"),
             Token(type_lcurly_brace, "{"), Token(type_keyword, "for"),
             Token(type_lpar, "("), Token(type_identifier, "n"),
             Token(type_assign_op, "="), Token(type_number, "0"),
             Token(type_semicolon, ";"), Token(type_identifier, "n"),
             Token(type_binop, "<="), Token(type_number, "10"),
             Token(type_semicolon, ";"), Token(type_identifier, "n"),
             Token(type_unaryop, "++"), Token(type_rpar, ")"),
             Token(type_lcurly_brace, "{"), Token(type_identifier, "print"),
             Token(type_lpar, "("), Token(type_identifier, "n"),
             Token(type_rpar, ")"), Token(type_semicolon, ";"),
             Token(type_rcurly_brace, "}"), Token(type_rcurly_brace, "}"),
             Token(type_rcurly_brace, "}")
            }
    );
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expectedTokens);
}

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


TEST(KeyWords, EmptyString){
    std::string input = "";
    std::vector<Token> tokens = tokenizeCode(input);
    EXPECT_EQ(0, tokens.size());
}

TEST(KeyWords, WhiteSpaces){
    std::string input = "\n\t \n";
    std::vector<Token> tokens = tokenizeCode(input);
    EXPECT_EQ(0, tokens.size());
}

TEST(KeyWords, OneKeyWord){
    std::string input = "if";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_keyword, input)});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(KeyWords, MultipleKeyWords1){
    std::string input = "if else for while extern asm";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_keyword, "if"), Token(type_keyword, "else"),
                                        Token(type_keyword, "for"), Token(type_keyword, "while"),
                                        Token(type_keyword, "extern"), Token(type_keyword, "asm")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(KeyWords, MultipleKeyWords2){
    std::string input = "if; else++ for( while) extern<= asm>= extern= while{ for} ";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_keyword, "if"), Token(type_semicolon, ";"),
                                        Token(type_keyword, "else"), Token(type_unaryop, "++"),
                                        Token(type_keyword, "for"), Token(type_lpar, "("),
                                        Token(type_keyword, "while"), Token(type_rpar, ")"),
                                        Token(type_keyword, "extern"), Token(type_binop, "<="),
                                        Token(type_keyword, "asm"), Token(type_binop, ">="),
                                        Token(type_keyword, "extern"), Token(type_assign_op, "="),
                                        Token(type_keyword, "while"), Token(type_lcurly_brace, "{"),
                                        Token(type_keyword, "for"), Token(type_rcurly_brace, "}")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}



TEST(Identifiers, OneIdentifier1){
    std::string input = "abc_";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_identifier, input)});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(Identifiers, OneIdentifier2){
    std::string input = "__1_a2Bc_3d_45";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_identifier, input)});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(Identifiers, OneIdentifier3){
    for (std::string input: {"if_else", "else_if", "for123", "whileextern", "extern_", "asmasm"}) {
        // Expected Output
        std::vector<Token> expected_tokens({Token(type_identifier, input)});
        std::vector<Token> generated_tokens = tokenizeCode(input);
        checkVectorEquality(generated_tokens, expected_tokens);
    }
}

TEST(Identifiers, MultipleIdentifiers1){
    std::string input = "  abc=\n\tdef++def \t ghi++;   ";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_identifier, "abc"),
                                        Token(type_assign_op, "="),
                                        Token(type_identifier, "def"),
                                        Token(type_unaryop, "++"),
                                        Token(type_identifier, "def"),
                                        Token(type_identifier, "ghi"),
                                        Token(type_unaryop, "++"),
                                        Token(type_semicolon, ";")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(Identifiers, MultipleIdentifiers2){
    std::string input = "abc; abc++ abc( abc) abc<= abc>= abc= abc{ abc} ";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_identifier, "abc"), Token(type_semicolon, ";"),
                                        Token(type_identifier, "abc"), Token(type_unaryop, "++"),
                                        Token(type_identifier, "abc"), Token(type_lpar, "("),
                                        Token(type_identifier, "abc"), Token(type_rpar, ")"),
                                        Token(type_identifier, "abc"), Token(type_binop, "<="),
                                        Token(type_identifier, "abc"), Token(type_binop, ">="),
                                        Token(type_identifier, "abc"), Token(type_assign_op, "="),
                                        Token(type_identifier, "abc"), Token(type_lcurly_brace, "{"),
                                        Token(type_identifier, "abc"), Token(type_rcurly_brace, "}")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}



TEST(Numbers, OneNumber1){
    std::string input = "1";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_number, input)});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(Numbers, OneNumber2){
    std::string input = "01.030";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_number, input)});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(Numbers, OneNumber3){
    std::string input = ".0";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_number, input)});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(Numbers, MultipleNumbers1){
    std::string input = "0\n 123 .456\t789";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_number, "0"),
                                        Token(type_number, "123"),
                                        Token(type_number, ".456"),
                                        Token(type_number, "789")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(Numbers, MultipleNumbers2){
    std::string input = "123; 123++ 123( 123) 123<= 123>= 123= 123{ 123} "
                        "1.3; 1.3++ 1.3( 1.3) 1.3<= 1.3>= 1.3= 1.3{ 1.3} ";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_number, "123"), Token(type_semicolon, ";"),
                                        Token(type_number, "123"), Token(type_unaryop, "++"),
                                        Token(type_number, "123"), Token(type_lpar, "("),
                                        Token(type_number, "123"), Token(type_rpar, ")"),
                                        Token(type_number, "123"), Token(type_binop, "<="),
                                        Token(type_number, "123"), Token(type_binop, ">="),
                                        Token(type_number, "123"), Token(type_assign_op, "="),
                                        Token(type_number, "123"), Token(type_lcurly_brace, "{"),
                                        Token(type_number, "123"), Token(type_rcurly_brace, "}"),

                                        Token(type_number, "1.3"), Token(type_semicolon, ";"),
                                        Token(type_number, "1.3"), Token(type_unaryop, "++"),
                                        Token(type_number, "1.3"), Token(type_lpar, "("),
                                        Token(type_number, "1.3"), Token(type_rpar, ")"),
                                        Token(type_number, "1.3"), Token(type_binop, "<="),
                                        Token(type_number, "1.3"), Token(type_binop, ">="),
                                        Token(type_number, "1.3"), Token(type_assign_op, "="),
                                        Token(type_number, "1.3"), Token(type_lcurly_brace, "{"),
                                        Token(type_number, "1.3"), Token(type_rcurly_brace, "}")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}


TEST(Strings, EmptyString){
    std::string input = "\"\"";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_string, input)});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(Strings, OneString1){
    std::string input = "\"abc\"";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_string, input)});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(Strings, OneString3){
    std::string input = "\"if else for while extern asm {()} // <= >= ++\"";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_string, input)});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(Strings, MultipleStrings1){
    std::string input = R"_("a" "b c")_" "\t\"d\"\n\"e\"";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_string, "\"a\""),
                                        Token(type_string, "\"b c\""),
                                        Token(type_string, "\"d\""),
                                        Token(type_string, "\"e\"")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(Strings, MultipleStrings2){
    std::string input = R"_("a"; "a"++ "a"( "a") "a"<= "a">= "a"= "a"{ "a"} )_";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_string, "\"a\""), Token(type_semicolon, ";"),
                                        Token(type_string, "\"a\""), Token(type_unaryop, "++"),
                                        Token(type_string, "\"a\""), Token(type_lpar, "("),
                                        Token(type_string, "\"a\""), Token(type_rpar, ")"),
                                        Token(type_string, "\"a\""), Token(type_binop, "<="),
                                        Token(type_string, "\"a\""), Token(type_binop, ">="),
                                        Token(type_string, "\"a\""), Token(type_assign_op, "="),
                                        Token(type_string, "\"a\""), Token(type_lcurly_brace, "{"),
                                        Token(type_string, "\"a\""), Token(type_rcurly_brace, "}")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}



TEST(Comments, OneComment1){
    std::string input = "// abcd \n";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_comment, "// abcd ")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(Comments, OneComment2){
    std::string input = "//\n";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_comment, "//")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(Comments, OneComment3){
    std::string input = "///if else for while extern asm () // <= >= ++   \n";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_comment, "///if else for while extern asm () // <= >= ++   ")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(Comments, MultipleComments1){
    std::string input = R"_(
    // comment1
    ; // comment2
    // abc
    " str " // abc
    )_";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_comment, "// comment1"),
                                        Token(type_semicolon, ";"),
                                        Token(type_comment, "// comment2"),
                                        Token(type_comment, "// abc"),
                                        Token(type_string, "\" str \""),
                                        Token(type_comment, "// abc")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(Comments, MultipleComments2){
    std::string input = R"_(
    while// comment
    abc// comment
    123// comment
    123.456// comment
    "str"// comment
    ++// comment
    )_";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_keyword, "while"),
                                        Token(type_comment, "// comment"),
                                        Token(type_identifier, "abc"),
                                        Token(type_comment, "// comment"),
                                        Token(type_number, "123"),
                                        Token(type_comment, "// comment"),
                                        Token(type_number, "123.456"),
                                        Token(type_comment, "// comment"),
                                        Token(type_string, "\"str\""),
                                        Token(type_comment, "// comment"),
                                        Token(type_unaryop, "++"),
                                        Token(type_comment, "// comment")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}


/*
TEST(GivenTests, TestAllKeywordsInASent){
    std::string input = "if else for while extern asm";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_keyword, "if"), Token(type_keyword, "else"),
                                        Token(type_keyword, "for"), Token(type_keyword, "while"),
                                        Token(type_keyword, "extern"), Token(type_keyword, "asm")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(GivenTests, TestString){
    std::string input = "STR = \"this is string\";";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_identifier, "STR"), Token(type_assign_op, "="),
                                        Token(type_string, "\"this is string\""), Token(type_semicolon, ";")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(GivenTests, TestNumber){
    std::string input = "n = 3.14;";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_identifier, "n"), Token(type_assign_op, "="),
                                        Token(type_number, "3.14"), Token(type_semicolon, ";")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(GivenTests, TesComment){
    std::string input = "//This is a comment line\nn = 0;";
    // Expected Output
    std::vector<Token> expected_tokens({Token(type_comment, "//This is a comment line"),
                                        Token(type_identifier, "n"), Token(type_assign_op, "="),
                                        Token(type_number, "0"), Token(type_semicolon, ";")});
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(GivenTests, TestFullCode){
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
*/


TEST(FullCodeTest, Test1){
    std::string input = "int foo(string p){\n"
                        "   extern int n=0;\n"
                        "   //This is a comment line\n"
                        "   string STR=\"this is string\";\n"
                        "   while(n>=0){\n"
                        "       for(n=0;n<=10;n++){\n"
                        "           print(p);\n"
                        "           asm{\n"
                        "               move a 10; //This is asm instruction\n"
                        "           }"
                        "       }\n"
                        "   }\n"
                        "}";
    // Expected Output
    std::vector<Token> expectedTokens(
            {Token(type_identifier, "int"), Token(type_identifier, "foo"),
             Token(type_lpar, "("),
             Token(type_identifier, "string"), Token(type_identifier, "p"),
             Token(type_rpar, ")"),
             Token(type_lcurly_brace, "{"), Token(type_keyword, "extern"),
             Token(type_identifier, "int"),
             Token(type_identifier, "n"), Token(type_assign_op, "="),
             Token(type_number, "0"), Token(type_semicolon, ";"),
             Token(type_comment, "//This is a comment line"),
             Token(type_identifier, "string"), Token(type_identifier, "STR"),
             Token(type_assign_op, "="), Token(type_string, "\"this is string\""),
             Token(type_semicolon, ";"), Token(type_keyword, "while"),
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
             Token(type_lpar, "("), Token(type_identifier, "p"),
             Token(type_rpar, ")"), Token(type_semicolon, ";"),
             Token(type_keyword, "asm"), Token(type_lcurly_brace, "{"),
             Token(type_identifier, "move"), Token(type_identifier, "a"),
             Token(type_number, "10"), Token(type_semicolon, ";"),
             Token(type_comment, "//This is asm instruction"), Token(type_rcurly_brace, "}"),
             Token(type_rcurly_brace, "}"), Token(type_rcurly_brace, "}"),
             Token(type_rcurly_brace, "}")
            }
    );
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expectedTokens);
}


TEST(FullCodeTest, Test2){
    std::string input = "void ifabc(a e){\n"
                        "   if(f>=0){\n"
                        "           print(e);\n"
                        "   }\n"
                        "   else{\n"
                        "      asm{\n"
                        "         store ifreg 10"
                        "      }"
                        "   }"
                        "}";
    // Expected Output
    std::vector<Token> expectedTokens(
            {
                    Token(type_identifier, "void"), Token(type_identifier, "ifabc"),
                    Token(type_lpar, "("), Token(type_identifier, "a"), Token(type_identifier, "e"),
                    Token(type_rpar, ")"), Token(type_lcurly_brace, "{"), Token(type_keyword, "if"),
                    Token(type_lpar, "("), Token(type_identifier, "f"), Token(type_binop, ">="),
                    Token(type_number, "0"), Token(type_rpar, ")"), Token(type_lcurly_brace, "{"),
                    Token(type_identifier, "print"), Token(type_lpar, "("), Token(type_identifier, "e"),
                    Token(type_rpar, ")"), Token(type_semicolon, ";"), Token(type_rcurly_brace, "}"),
                    Token(type_keyword, "else"), Token(type_lcurly_brace, "{"), Token(type_keyword, "asm"),
                    Token(type_lcurly_brace, "{"), Token(type_identifier, "store"), Token(type_identifier, "ifreg"),
                    Token(type_number, "10"), Token(type_rcurly_brace, "}"), Token(type_rcurly_brace, "}"),
                    Token(type_rcurly_brace, "}")
            }
    );
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expectedTokens);
}

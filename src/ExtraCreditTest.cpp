//
// Created by Saikat Chakraborty on 9/12/20.
//

#include "gtest/gtest.h"
#include <string>
#include <vector>
#include "Lexer.h"

void checkVectorEquality(std::vector<Token> generated_tokens, 
                         std::vector<Token> expected_tokens,
                         std::vector<Token> optional_tokens = {}){
    int gen_size = generated_tokens.size();
    int expected_size = expected_tokens.size();
    int optional_size = optional_tokens.size();

    EXPECT_GE(gen_size, expected_size);
    EXPECT_LE(gen_size, expected_size + optional_size);

    for (int i = 0; i < expected_size; i++){
        EXPECT_EQ(generated_tokens[i] , expected_tokens[i]);
    }
    for (int i = expected_size, j = 0; i < gen_size; i++, j++) {
        EXPECT_EQ(generated_tokens[i].getType() , optional_tokens[j].getType());
    }
}


TEST(ErrorDetection, InvalidNumber1){
    std::string input = "n = 3.;";
    // Expected Output
    std::vector<Token> expected_tokens{Token(type_identifier, "n"), Token(type_assign_op, "=")};
    std::vector<Token> optional_tokens{Token(type_error, "Invalid Number")};
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens, optional_tokens);
}

TEST(ErrorDetection, InvalidNumber2){
    std::string input = "n = 3.1.1";
    // Expected Output
    std::vector<Token> expected_tokens{Token(type_identifier, "n"), Token(type_assign_op, "=")};
    std::vector<Token> optional_tokens{Token(type_error, "Invalid Number")};
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens, optional_tokens);
}

TEST(ErrorDetection, InvalidNumber3){
    std::string input = "n = .r";
    // Expected Output
    std::vector<Token> expected_tokens{Token(type_identifier, "n"), Token(type_assign_op, "=")};
    std::vector<Token> optional_tokens{Token(type_error, "Invalid Number")};
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens, optional_tokens);
}

TEST(ErrorDetection, InvalidNumber4){
    std::string input = "n = 3..";
    // Expected Output
    std::vector<Token> expected_tokens{Token(type_identifier, "n"), Token(type_assign_op, "=")};
    std::vector<Token> optional_tokens{Token(type_error, "Invalid Number")};
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens, optional_tokens);
}


/*TEST(ErrorDetection, InvalidNumber5){
    std::string input = "n = 3_";
    // Expected Output
    std::vector<Token> expected_tokens{Token(type_identifier, "n"), Token(type_assign_op, "=")};
    std::vector<Token> optional_tokens{Token(type_error, "Invalid Number")};
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens, optional_tokens);
}*/


TEST(ErrorDetection, InvalidString1){
    std::string input = R"_(n = "abc)_";
    // Expected Output
    std::vector<Token> expected_tokens{Token(type_identifier, "n"), Token(type_assign_op, "=")};
    std::vector<Token> optional_tokens{Token(type_error, "Invalid String")};
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens, optional_tokens);
}

/*TEST(ErrorDetection, InvalidString5){
    std::string input = R"_(n = ")_";
    // Expected Output
    std::vector<Token> expected_tokens{Token(type_identifier, "n"), Token(type_assign_op, "=")};
    std::vector<Token> optional_tokens{Token(type_error, "Invalid String")};
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens, optional_tokens);
}*/

TEST(ErrorLocalization, InvalidNumber1){
    std::string input = "n = 3.;";
    // Expected Output
    std::vector<Token> expected_tokens{Token(type_identifier, "n"), Token(type_assign_op, "="), Token(type_error, "Invalid Number")};
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(ErrorLocalization, InvalidNumber2){
    std::string input = "n = 3.1.1";
    // Expected Output
    std::vector<Token> expected_tokens{Token(type_identifier, "n"), Token(type_assign_op, "="), Token(type_error, "Invalid Number")};
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(ErrorLocalization, InvalidNumber3){
    std::string input = "n = .r";
    // Expected Output
    std::vector<Token> expected_tokens{Token(type_identifier, "n"), Token(type_assign_op, "="), Token(type_error, "Invalid Number")};
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

TEST(ErrorLocalization, InvalidNumber4){
    std::string input = "n = 3..";
    // Expected Output
    std::vector<Token> expected_tokens{Token(type_identifier, "n"), Token(type_assign_op, "="), Token(type_error, "Invalid Number")};
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

/*TEST(ErrorLocalization, InvalidNumber5){
    std::string input = "n = 3_";
    // Expected Output
    std::vector<Token> expected_tokens{Token(type_identifier, "n"), Token(type_assign_op, "="), Token(type_error, "Invalid Number")};
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}*/

TEST(ErrorLocalization, InvalidString1){
    std::string input = R"_(n = "abc)_";
    // Expected Output
    std::vector<Token> expected_tokens{Token(type_identifier, "n"), Token(type_assign_op, "="), Token(type_error, "Invalid String")};
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}

/*TEST(ErrorLocalization, InvalidString5){
    std::string input = R"_(n = ")_";
    // Expected Output
    std::vector<Token> expected_tokens{Token(type_identifier, "n"), Token(type_assign_op, "="), Token(type_error, "Invalid String")};
    std::vector<Token> generated_tokens = tokenizeCode(input);
    checkVectorEquality(generated_tokens, expected_tokens);
}*/

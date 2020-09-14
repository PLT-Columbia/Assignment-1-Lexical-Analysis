//
// Created by Saikat Chakraborty on 9/11/20.
//

#ifndef ASSIGNMENT_1_LEXER_H
#define ASSIGNMENT_1_LEXER_H

#endif //ASSIGNMENT_1_LEXER_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

/**
 * Available token classes.
 */
enum TokenType {
    type_lpar = 0,
    type_rpar = 1,
    type_lcurly_brace = 2,
    type_rcurly_brace = 3,
    type_keyword = 4,
    type_identifier = 5,
    type_number = 6,
    type_string = 7,
    type_comment = 8,
    type_error = 9,
    type_unaryop = 10,
    type_binop = 11,
    type_semicolon = 12,
    type_assign_op = 13
};

/**
 * Data structure for tokens.
 * Whenever a token is found, an object (with appropriate token type/class and lexeme)
 * from this class has to be created.
 */
class Token {

private:
    TokenType type;
    std::string lexeme;

public:
    Token(TokenType _type, std::string _lexeme);

    std::string get_repr();

    TokenType getType();

    std::string getLexeme();

    bool operator==(const Token& other) const;

    bool operator!=(const Token& other) const;
};

std::string get_token_type_string(TokenType _type);

/*
 * We simulate the state transitions with a DFA here.
 * The next state should be constructed based on the current state and the input character.
 * Gotcha note!
 *      1. Be careful about whitespaces.
 *         Whitespaces usually finish a token, except for strings and comments.
 *         For example, `hello world ` contains 2 identifier tokens, each terminated with a whitespace.
 *         However, `"Hello world "` contains 1 string token, and both spaces are included in the token lexeme.
 *      2. Whitespaces (i.e. ' ', '\t', '\n') usually end sequences of characters in a token. However,
 *         other characters can also end a token stream. For example,
 *         a. print ( ) -> the tokens here are <ID, "print">, <LPAR, "(">, and <RPAR, ")">
 *         b. print() -> the tokens here are also <ID, "print">, <LPAR, "(">, and <RPAR, ")">
 *         Note that, in the former case, the space, ' ', after the token print ended the "print" token.
 *         However, in the latter case, "print" is followed by a left parenthesis, '(', which ends the "print" token.
 *         Your code should be able to handle both these scenarios.
 *      3. For comments, you should discard the newline character ('\n') that ends the comments.
 *         See LexerTest.cpp for the relevant test case.
 */
std::string stateTransition(std::string current_state, char ch);

/***
 * The main function for lexical analysis/tokenization.
 *
 * @param   _character_stream of type std::string
 * @return  std::vector of type Token (declared above)
 *
 */
std::vector<Token> tokenizeCode(std::string _character_stream);


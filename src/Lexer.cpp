//
// Created by Saikat Chakraborty on 9/11/20.
//
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "Lexer.h"

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
 *        See LexerTest.cpp for the relevant test case.
 */
std::string stateTransition(std::string current_state, char ch) {
    if (current_state.empty()) {
        // When the state is empty, the input character will represent the current state.
        current_state.push_back(ch);
        return current_state;
    }
    else if (current_state == "i" && ch == 'f') {
        return "if";
    }
    // TODO: implement the rest of the state transitions.
    else {
        return "Not implemented error!";
    }
}

/***
 * The main function for lexical analysis/tokenization.
 *
 * @param   _character_stream of type std::string
 * @return  std::vector of type Token (declared above)
 *
 */
std::vector<Token> tokenizeCode(std::string _character_stream) {
    std::vector<Token> tokens;
    /*
     * Note to the students:
     *     You should not make any changes to the function prototype (i.e., function name, parameter, and return type).
     *     Any such changes cause the test suite to fail.
     *     You may define auxiliary/helper functions, which can then be call edfrom this function.
     */
    std::string current_state = ""; // Initially, we start with a null or empty state.
    std::string next_state = "";
    bool token_accepted = false;
    // We scan character by character.
    for (std::string::iterator string_iter = _character_stream.begin();
         string_iter != _character_stream.end();
         string_iter++) {
        char current_character = *string_iter;
        next_state = stateTransition(current_state, current_character);
        if (next_state == "(") {
            tokens.emplace_back(TokenType::type_lpar, "(");
            token_accepted = true;
        }
        else if (next_state == ")") {
            tokens.emplace_back(TokenType::type_rpar, ")");
            token_accepted = true;
        }
        else if (next_state == "{") {
            tokens.emplace_back(TokenType::type_lcurly_brace, "{");
            token_accepted = true;
        }
        else if (next_state == "}") {
            tokens.emplace_back(TokenType::type_rcurly_brace, "}");
            token_accepted = true;
        }
        else if (next_state == "if") {
            tokens.emplace_back(TokenType::type_keyword, "if");
            token_accepted = true;
        }
        else if(next_state == "++"){
            tokens.emplace_back(TokenType::type_unaryop, "++");
            token_accepted = true;
        }
        else if(next_state == ">="){
            tokens.emplace_back(TokenType::type_binop, ">=");
            token_accepted = true;
        }
        else if(next_state == "<="){
            tokens.emplace_back(TokenType::type_binop, "<=");
            token_accepted = true;
        }
        else if(next_state == ";"){
            tokens.emplace_back(TokenType::type_semicolon, ";");
            token_accepted = true;
        }
        else if(next_state == "="){
            tokens.emplace_back(TokenType::type_assign_op, "=");
            token_accepted = true;
        }
        else {
            // TODO: add the rest of the tokens.
            // TODO: Make sure to flag the 'token_accepted' as true when you accept a token.
            /* TODO:
             *      a. Implement the rest of the keywords, i.e., else, while, extern, asm, for
             *      b. Implement dentifiers.
             *      c. Implement numbers.
             *      d. Implement strings.
             *      e. Implement comments.
             *      f. [Extra Credit] Implement a lexical error check. In the case of an error,
             *         the cause of the error ("Invalid Number" or "Invalid String") should go to the lexeme.
             */
        }
        // If we have already accepted a token, we will start from an empty state.
        if (token_accepted){
            current_state = "";
            next_state = "";
            token_accepted = false;
        }
        else{
            // No token has been accepted by this character. Let's proceed!
            current_state = next_state;
        }
    }
    return tokens;
}

TokenType Token::getType() {
    return this->type;
}

std::string Token::getLexeme() {
    return this->lexeme;
}

bool Token::operator==(const Token& other) const{
    return this->type == other.type && this->lexeme == other.lexeme;
}

bool Token::operator!=(const Token& other) const{
    return type != other.type || lexeme != other.lexeme;
}

std::string Token::get_repr()
{
    std::string return_str =  get_token_type_string(this->type) + ", \"" + this->lexeme + "\"";
    return return_str;
}

Token::Token(TokenType _type, std::string _lexeme) {
    this->type = _type;
    this->lexeme = std::move(_lexeme);
}

void printTokenStream(std::vector<Token> tokens) {
    for (auto& token : tokens) {
        std::cout << token.get_repr() << " ";
    }
}

std::string get_token_type_string(TokenType _type) {
    switch (_type) {
        case type_lpar:
            return "LPAR";
        case type_rpar:
            return "RPAR";
        case type_lcurly_brace:
            return "L-CURLY-BRACE";
        case type_rcurly_brace:
            return "R-CURLY-BRACE";
        case type_keyword:
            return "KEYWORD";
        case type_identifier:
            return "ID";
        case type_number:
            return "NUMBER";
        case type_string:
            return "STRING";
        case type_comment:
            return "COMMENT";
        case type_error:
            return "ERROR";
        case type_unaryop:
            return "UNOP";
        case type_binop:
            return "BINOP";
        case type_semicolon:
            return "SEMICOLON";
        case type_assign_op:
            return "ASSIGN";
    }
}

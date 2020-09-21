# COMS W4115: Programming Assignment 1 (Lexical Analysis)

## Course Summary

Course: COMS 4115 Programming Languages and Translators (Fall 2020)  
Website: https://www.rayb.info/fall2020  
University: Columbia University  
Instructor: Prof. Baishakhi Ray


## Logistics
* **Announcement Date:** Wednesday, September 16, 2020
* **Due Date:** Wednesday, September 30, 2020 by 11:59 PM. **No extensions!**
* **Total Points:** 100


## Assignment

In lecture, you learned that the first task in a compiler's workflow is lexical analysis. A **lexical analyzer** (or **tokenizer**) converts the raw sequence of characters from the code into sequence of tokens. In order to do that, the lexical analyzer scans through the sequence of characters in the code, groups them together into lexemes, and identifies the token class for each lexeme. For this programming assignment, you will gain hands-on experience with lexical analysis and implement your own lexical analyzer. You will implement a partial lexical analyzer (implemented in C++) that scans streams of C code.

### Setup

Please follow these instructions prior to starting the assignment:

1. Install `cmake` from [here](https://cmake.org/download/), or run `sudo apt-get install cmake` in your terminal/shell.
2. Run our `build.sh` script as follows: `bash build.sh`.

### Main Assignment (100 Points)

We have provided a C++ file, [`src/Lexer.cpp`](src/Lexer.cpp), as well as a header file, [`src/Lexer.h`](src/Lexer.h), that contain setup code and helper classes/functions for tokens, token classes, state transitions, and outputting tokens. Your task will be to fill in the missing items of the tokenizer to generate all tokens for an input code snippet.

The TODO comments indicate all parts of the lexical analyzer that you need to implement in this assignment:
1. [`stateTransition`](src/Lexer.cpp#L36): we have implemented the state transition for the `if` keyword. You are responsible for implementing the rest of the state transitions.
2. [`tokenizeCode`](src/Lexer.cpp#L59): we have generated tokens for parentheses, curly braces, and the `if` keyword. You are responsible for generating the rest of the tokens.

We have provided below a list of token classes you must support:

* [ ] **Keywords (20 Points)**: any tokens from the list [_**if**_/_**else**_, _**for**_, _**while**_, _**extern**_, _**asm**_]
	* Token class: _KEYWORD_
* [ ] **Identifiers (20 Points)**: any tokens that begin with an **_alphabetic_** (including both capital and lowercase) character or an **_underscore_** (_), followed by at most 16 alphanumeric characters and/or underscore (EXCEPT for the keyword tokens)
	* Examples of valid identifiers: **test**, **test1**, **_id1**, and **test_1_id_2**
	* Token class: _ID_
* [ ] **Numbers (20 Points)**: any numerical tokens optionally containing a **_decimal point/period_** (.), _i.e._, both integers and floating-point numbers
    * Examples of valid numbers: **1**, **1.0**, **1.01**, and **.01**
    * Token class: _NUMBER_
* [ ] **Strings (20 Points)**: any tokens represented by a sequence of characters (including the empty sequence) that begins and ends with double quotes ("). You are **not** required to handle escape characters like `\"`.
	* Examples of strings: **"Hello"**, **""**, and **"1.01"**
	* Token class: _STRING_
* [ ] **Comments (20 Points)**: any tokens represented by a sequence of characters beginning with a double slash (**//**) and that ends with a newline (**\n**)
	* Examples of comments: **//Hello\n**, **//""\n**, and **//"1.01"\n**
	* Token class: _COMMENT_
* [ ] **Operators (0 Points)**: any tokens represented by a unary operator, binary operator, or an assignment operator, specifically from the list [_**++**_,&nbsp;_**--**_,&nbsp;_**>**_,&nbsp;_**<**_,&nbsp;_**>=**_,&nbsp;_**<=**_,&nbsp;_**==**_,&nbsp;_**=**_]
	* Token classes: _UNOP_, _BINOP_, _ASSIGNOP_
	* We have already implemented **some** of these operators for you. You _**DON'T**_ need to implement the rest; we will **NOT** have any test cases containing any of the unimplemented operators.
* [ ] **Parentheses, Braces, and Semicolons (0 Points)**: any tokens from the list [_**(**_,&nbsp;_**)**_,&nbsp;_**{**_,&nbsp;_**}**_,&nbsp;_**;**_]
	* Token classes: _LPAR_, _RPAR_, _LBRACE_, _RBRACE_, _SEMICOLON_
	* We have already implemented parentheses, braces, and semicolons for you.

You are not required to handle standalone whitespaces (_e.g._, **\t**, **\n**, **\r**, etc.); if you encounter them in the character stream, please make sure to properly ignore them (*e.g.*, do not characterize them as identifiers).

### Example

Here is a sample code snippet and the expected output of lexical analyzer once you have completed the implementation:

**Input:** 
```
if(n > 0) {
    print("Hello World");
}
```
**Expected Output:**
```        
<KEYWORD, if>           
<LPAR, (>
<ID, n>
<BINOP, >>
<NUMBER, 0> 
<RPAR, )>    
<L-CURLY-BRACE, {>
<ID, print>
<LPAR, (>
<STRING, "Hello World">
<RPAR, )>
<SEMICOLON, ;> 
<R-CURLY-BRACE, }>
```
**Note:** You can print such representation of token sequences using [`printTokenStream`](src/Main.cpp#8) function in `src/Main.cpp` file. 

We have provided a test suite in [`src/LexerTest.cpp`](src/LexerTest.cpp), which contains relevant test cases for your main assignment. You can run [`bash test.sh`](test.sh) to verify your test cases are passing.


### Extra Credit (30 Points)

You learned in lecture that lexical analysis can handle errors. You now have the opportunity to figure out how to handle these errors inside your lexical analyzer by detecting and localizing them.

Inside the `tokenizeCode` function, there is a TODO comment for lexical errors:
* **Detection (10 Points)**: determine if an error exists at all and output the result.
* **Localization (20 Points)**: determine the cause(s) of any error that exists. There are 2 different causes of lexical errors that you need to support:
	* **Invalid Number**: any tokens that begin as valid numbers, but that do not actually match the pattern of numbers (_e.g._, **1.** and **1.1r**)
	* **Invalid String**: any tokens that begin as valid strings, but that do not actually match the pattern of strings (_e.g._, **"hello**, **"_**)

Again, we have provided a test suite in [`src/ExtraCreditTest.cpp`](src/ExtraCreditTest.cpp), which contains relevant test cases for the extra credit part of your assignment. You can run [`bash extra_credit.sh`](extra_credit.sh) to verify your test cases are passing.


### Additional Notes
1. The provided test cases are **examples only**, and we may run your code with different test suites.
2. Be careful about the [corner cases](src/Lexer.cpp#L13) during your implementation.
3. For debugging, you may use our [`src/Main.cpp`](src/Main.cpp), which provides some helper functions to help you debug your code.


## Submission
For this programming assignment, you will have to implement the functionality in `src/Lexer.cpp`. Please commit and push your changes to the *master* branch of remote repository created for **your own** assignment. Additionally,

1. Please make sure all of the code you would like us to grade is inside `Lexer.cpp`, and try not to modify any other files in the directory.
2. Please make sure not to modify the `.gitignore` file during submission.
3. Please run [`build.sh`](build.sh) to make sure that **project builds properly** before submitting the assignment. 


## Piazza

If you have any questions about this programming assignment, please post them in the Piazza forum for the course, and an instructor will reply to them as soon as possible. Any updates to the assignment itself will be available in Piazza.


## Disclaimer

This assignment belongs to Columbia University. It may be freely used for educational purposes.

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

In lecture, you have been learning about lexical analysis and finite automata. In particular, you learned that programs can be classified by token roles or token classes. For this programming assignment, you will gain hands-on experience with lexical analysis and implement your own lexical analyzer to generate a token sequence from a program source.

### Setup

Please follow these instructions prior to starting the assignment:

1. Install `cmake` from [here](https://cmake.org/download/), or run `sudo apt-get install cmake` in your terminal/shell.
2. Run our `build.sh` script as follows: `bash build.sh`.

### Main Assignment (100 Points)

We have provided a C++ file, [`src/Lexer.cpp`](src/Lexer.cpp), as well as a header file, [`src/Lexer.h`](src/Lexer.h), that contain setup code and helper classes/functions for tokens, token classes, state transitions, and outputting tokens. Your task will be to fill in the missing items of the tokenizer to generate all tokens for an input code snippet.

The TODO comments indicate all parts of the lexical analyzer that you need to implement in this assignment:
1. [`stateTransition`](src/Lexer.cpp#L28): we have implemented the state transition for the `if` keyword. You are responsible for implementing the rest of the state transitions.
2. [`tokenizeCode`](src/Lexer.cpp#L50): we have generated tokens for parentheses, curly braces, and the `if` keyword. You are responsible for generating the rest of the tokens.

We have provided below a list of token classes you must support:

* [ ] **Keywords (20 Points)**: any tokens from the list [_**if**_/_**else**_, _**for**_, _**while**_, _**extern**_, _**asm**_]
	* Token class: _Keyword_
* [ ] **Identifiers (20 Points)**: any tokens that begin with an **_alphabetic_** (including both capital and lowercase) character or an **_underscore_** (_), followed by at most 16 alphanumeric characters and/or underscore (EXCEPT for the keyword tokens)
	* Examples of valid identifiers: **test**, **test1**, **_id1**, and **test_1_id_2**
	* Token class: _Identifier_
* [ ] **Numbers (20 Points)**: any numerical tokens optionally containing a **_decimal point/period_** (.), _i.e._, both integers and floating-point numbers
    * Examples of valid numbers: **1**, **1.0**, **1.01**, and **.01**
    * Token class: _Number_
* [ ] **Strings (20 Points)**: any tokens represented by a sequence of characters (including the empty sequence) that begins and ends with double quotes (")
	* Examples of strings: **"Hello"**, **""**, and **"1.01"**
	* Token class: _String_
* [ ] **Comments (20 Points)**: any tokens represented by a sequence of characters beginning with a double slash (**//**) and that ends with a newline (**\n**)
	* Examples of comments: **//Hello\n**, **//""\n**, and **//"1.01"\n**
	* Token class: _Comment_

You are not required to handle standalone whitespaces (_e.g._, **\t**, **\n**, **\r**, etc.), but if you don't handle them, make sure to properly ignore them.

Here is a sample code snippet: 

### Example

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

We have provided a test suite in [`src/LexerTest.cpp`](src/LexerTest.cpp), which contains relevant test cases for your main assignment. You can run [`bash test.sh`](test.sh) to verify your test cases are passing.


### Extra Credit (30 Points)

You learned in lecture that lexical analysis can handle errors. You now have the opportunity to figure out how to handle these errors inside your lexical analyzer by detecting and localizing them.

Inside the `tokenizeCode` function, there is a TODO comment for lexical errors:
* **Detection (10 Points)**: determine if an error exists at all and output the result.
* **Localization (20 Points)**: determine the cause(s) of any error that exists. There are 2 different causes of lexical errors that you need to support:
	* **Invalid Number**: any tokens that begin as valid numbers, but that do not actually match the pattern of numbers (_e.g._, **1.** and **1.1r**)
	* **Invalid String**: any tokens that begin as valid strings, but that do not actually match the pattern of strings (_e.g._, **"hello**, **"_**, and **""_**)

Again, we have provided a test suite in [`src/ExtraCreditTest.cpp`](src/ExtraCreditTest.cpp), which contains relevant test cases for the extra credit part of your assignment. You can run [`bash extra_credit.sh`](extra_credit.sh) verify your test cases are passing.


### Additional Notes
1. The provided test cases are **examples only**, and we may run your code with different test suites.
2. Be careful about the [corner cases](src/Lexer.cpp#L13) during your implementation.
3. For debugging, you may use our [`src/Main.cpp`](src/Main.cpp), which provides some helper functions to help you debug your code.


## Submission
For this programming assignment, you will submit `Lexer.cpp` with the implemented functionality. Please commit and push `Lexer.cpp` to the *master* branch of the remote repository. Additionally,

1. Please make sure all of the code you would like us to grade is inside `Lexer.cpp`, and try not to modify any other files in the directory.
2. Please make sure not to modify the `.gitignore` file during submission.


## Piazza

If you have any questions about this programming assignment, please post them in the Piazza forum for the course, and an instructor will reply to them as soon as possible. Any updates to the assignment itself will be available in Piazza.


## Disclaimer

This assignment belongs to Columbia University. It may be freely used for educational purposes.

## Lexical Analysis code patch - 1

1. Copy the [`state.patch`](state.patch) file in your assignment directory. 
2. Check whether you can apply the patch automatically by running `git apply --check state.patch`.
3. If you **do not** see any `error` in your screen that means you **can apply the patch automatically**. 
4. Run the command `patch -p1 < state.patch`.
5. The patch will be applied to the appropriate location. 
6. Now run 
    1. `git add src/Lexer.cpp`
    2. `git commit -m "Apply state transition patch"`
7. In case you see any `error`during step 2, apply the following patch manually.
    ```diff
    --- a/src/Lexer.cpp
    +++ b/src/Lexer.cpp
    @@ -43,6 +43,13 @@ std::string stateTransition(std::string current_state, char ch) {
         else if (current_state == "i" && ch == 'f') {
             return "if";
         }
    +    else if ((current_state == "<" || current_state == ">") && ch == '='){
    +       current_state.push_back(ch);
    +       return current_state;
    +    }
    +    else if (current_state == "+" && ch == '+'){
    +       return "++";
    +    }
         // TODO: implement the rest of the state transitions.
         else {
             return "Not implemented error!";
   ```  
   
   **Explanation:** Copy the following code 
   ```c++
       else if ((current_state == "<" || current_state == ">") && ch == '='){
          current_state.push_back(ch);
          return current_state;
       }
       else if (current_state == "+" && ch == '+'){
          return "++";
       }
   ```   
   after the second `else if` block (where the return value is `"if"`) in `src/Lexer.cpp`. 
   

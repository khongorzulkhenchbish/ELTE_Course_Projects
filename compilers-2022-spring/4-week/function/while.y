%baseclass-preinclude <iostream>

%lsp-needed

%token T_PROGRAM
%token T_BEGIN
%token T_END
%token T_INTEGER 
%token T_BOOLEAN
%token T_SKIP
%token T_IF
%token T_THEN
%token T_ELSE
%token T_ENDIF
%token T_WHILE
%token T_DO
%token T_DONE
%token T_READ
%token T_WRITE
%token T_SEMICOLON
%token T_ASSIGN
%token T_OPEN
%token T_CLOSE
%token T_NUM
%token T_TRUE
%token T_FALSE
%token T_ID

    /* ----- Solution ----- */

%token T_FUNCTION
%token T_RETURN
%token T_COMMA

    /* ----- Solution END ----- */

%left T_OR T_AND
%left T_EQ
%left T_LESS T_GR
%left T_ADD T_SUB
%left T_MUL T_DIV T_MOD
%nonassoc T_NOT

%start program

%%

program:
    T_PROGRAM T_ID declarations T_BEGIN statements T_END
    {
        std::cout << "start -> T_PROGRAM T_ID declarations T_BEGIN statements T_END" << std::endl;
    }
;

declarations:
    // empty
    {
        std::cout << "declarations -> epsilon" << std::endl;
    }
|
    declaration declarations
    {
        std::cout << "declarations -> declaration declarations" << std::endl;
    }
;

declaration:
    T_INTEGER T_ID T_SEMICOLON
    {
        std::cout << "declaration -> T_INTEGER T_ID T_SEMICOLON" << std::endl;
    }
|
    T_BOOLEAN T_ID T_SEMICOLON
    {
        std::cout << "declaration -> T_BOOLEAN T_ID T_SEMICOLON" << std::endl;
    }

    /* ----- Solution ----- */

|
    function_declaration
    {
        std::cout << "declaration -> function_declaration" << std::endl;
    }

    /* ----- Solution END ----- */
;

statements:
    statement
    {
        std::cout << "statements -> statement" << std::endl;
    }
|
    statement statements
    {
        std::cout << "statements -> statement statements" << std::endl;
    }
;

statement:
    T_SKIP T_SEMICOLON
    {
        std::cout << "statement -> T_SKIP T_SEMICOLON" << std::endl;
    }
|
    assignment
    {
        std::cout << "statement -> assignment" << std::endl;
    }
|
    read
    {
        std::cout << "statement -> read" << std::endl;
    }
|
    write
    {
        std::cout << "statement -> write" << std::endl;
    }
|
    branch
    {
        std::cout << "statement -> branch" << std::endl;
    }
|
    loop
    {
        std::cout << "statement -> loop" << std::endl;
    }

    /* ----- Solution ----- */

|
    function_call T_SEMICOLON
    {
        std::cout << "statement -> function_call T_SEMICOLON" << std::endl;
    }

    /* ----- Solution END ----- */
;


assignment:
    T_ID T_ASSIGN expression T_SEMICOLON
    {
        std::cout << "assignment -> T_ID T_ASSIGN expression T_SEMICOLON" << std::endl;
    }
;

read:
    T_READ T_OPEN T_ID T_CLOSE T_SEMICOLON
    {
        std::cout << "read -> T_READ T_OPEN T_ID T_CLOSE T_SEMICOLON" << std::endl;
    }
;

write:
    T_WRITE T_OPEN expression T_CLOSE T_SEMICOLON
    {
        std::cout << "write -> T_WRITE T_OPEN expression T_CLOSE T_SEMICOLON" << std::endl;
    }
;

branch:
    T_IF expression T_THEN statements T_ENDIF
    {
        std::cout << "branch -> T_IF expression T_THEN statements T_ENDIF" << std::endl;
    }
|
    T_IF expression T_THEN statements T_ELSE statements T_ENDIF
    {
        std::cout << "branch -> T_IF expression T_THEN statements T_ELSE statements T_ENDIF" << std::endl;
    }
;

loop:
    T_WHILE expression T_DO statements T_DONE
    {
        std::cout << "loop -> T_WHILE expression T_DO statements T_DONE" << std::endl;
    }
;

    /* ----- Solution ----- */

function_declaration:
    T_FUNCTION T_ID T_OPEN declaration_parameters T_CLOSE declarations T_BEGIN function_statements T_END T_SEMICOLON
    {
        std::cout << "declaration -> T_FUNCTION T_ID T_OPEN declaration_parameters T_CLOSE declarations T_BEGIN function_statements T_END T_SEMICOLON" << std::endl;
    }
|
    T_FUNCTION T_INTEGER T_ID T_OPEN declaration_parameters T_CLOSE declarations T_BEGIN function_statements T_END T_SEMICOLON
    {
        std::cout << "declaration -> T_FUNCTION T_INTEGER T_ID T_OPEN declaration_parameters T_CLOSE declarations T_BEGIN function_statements T_END T_SEMICOLON" << std::endl;
    }
|
    T_FUNCTION T_BOOLEAN T_ID T_OPEN declaration_parameters T_CLOSE declarations T_BEGIN function_statements T_END T_SEMICOLON
    {
        std::cout << "declaration -> T_FUNCTION T_BOOLEAN T_ID T_OPEN declaration_parameters T_CLOSE declarations T_BEGIN function_statements T_END T_SEMICOLON" << std::endl;
    }
;
   /* A better, more scalable solution would be to have a rule which contains all the types, i.e.
    * type:
    *       T_INTEGER
    *       {...}
    * |
    *       T_BOOLEAN
    *       {...}
    * |
    *       //empty (void type)
    *       {...}
    */

function_statements:
    function_statement
    {
        std::cout << "function_statements -> function_statement" << std::endl;
    }
|
    function_statement function_statements
    {
        std::cout << "function_statements -> function_statement function_statements" << std::endl;
    }
;

function_statement:
    T_SKIP T_SEMICOLON
    {
        std::cout << "function_statement -> T_SKIP T_SEMICOLON" << std::endl;
    }
|
    assignment
    {
        std::cout << "function_statement -> assignment" << std::endl;
    }
|
    read
    {
        std::cout << "function_statement -> read" << std::endl;
    }
|
    write
    {
        std::cout << "function_statement -> write" << std::endl;
    }
|
    function_branch
    {
        std::cout << "function_statement -> function_branch" << std::endl;
    }
|
    function_loop
    {
        std::cout << "function_statement -> function_loop" << std::endl;
    }
|
    T_RETURN expression T_SEMICOLON
    {
        std::cout << "function_statement -> T_RETURN expression T_SEMICOLON" << std::endl;
    }
;

function_branch:
    T_IF expression T_THEN function_statements T_ENDIF
    {
        std::cout << "function_branch -> T_IF expression T_THEN function_statements T_ENDIF" << std::endl;
    }
|
    T_IF expression T_THEN function_statements T_ELSE function_statements T_ENDIF
    {
        std::cout << "function_branch -> T_IF expression T_THEN function_statements T_ELSE function_statements T_ENDIF" << std::endl;
    }
;

function_loop:
    T_WHILE expression T_DO function_statements T_DONE
    {
        std::cout << "function_loop -> T_WHILE expression T_DO function_statements T_DONE" << std::endl;
    }
;

declaration_parameters:
    // empty
    {
        std::cout << "declaration_parameters -> epsilon" << std::endl;
    }
|
    declaration_parameter
    {
        std::cout << "declaration_parameters -> declaration_parameter" << std::endl;
    }
|
    declaration_parameter T_COMMA declaration_parameters
    {
        std::cout << "declaration_parameters -> declaration_parameter T_COMMA declaration_parameters" << std::endl;
    }
;

declaration_parameter:
    T_INTEGER T_ID
    {
        std::cout << "declaration_parameter -> T_INTEGER T_ID" << std::endl;
    }
|
    T_BOOLEAN T_ID
    {
        std::cout << "declaration_parameter -> T_BOOLEAN T_ID" << std::endl;
    }
;

parameters:
    // empty
    {
        std::cout << "parameters -> epsilon" << std::endl;
    }
|
    expression
    {
        std::cout << "parameters -> expression" << std::endl;
    }
|
    expression T_COMMA parameters
    {
        std::cout << "parameters -> expression T_COMMA parameter" << std::endl;
    }
;

function_call:
    T_ID T_OPEN parameters T_CLOSE
    {
        std::cout << "function_call -> T_ID T_OPEN parameters T_CLOSE" << std::endl;
    }
;
    /* ----- Solution END ----- */

expression:
    T_NUM
    {
        std::cout << "expression -> T_NUM" << std::endl;
    }
|
    T_TRUE
    {
        std::cout << "expression -> T_TRUE" << std::endl;
    }
|
    T_FALSE
    {
        std::cout << "expression -> T_FALSE" << std::endl;
    }
|
    T_ID
    {
        std::cout << "expression -> T_ID" << std::endl;
    }
|
    expression T_ADD expression
    {
        std::cout << "expression -> expression T_ADD expression" << std::endl;
    }
|
    expression T_SUB expression
    {
        std::cout << "expression -> expression T_SUB expression" << std::endl;
    }
|
    expression T_MUL expression
    {
        std::cout << "expression -> expression T_MUL expression" << std::endl;
    }
|
    expression T_DIV expression
    {
        std::cout << "expression -> expression T_DIV expression" << std::endl;
    }
|
    expression T_MOD expression
    {
        std::cout << "expression -> expression T_MOD expression" << std::endl;
    }
|
    expression T_LESS expression
    {
        std::cout << "expression -> expression T_LESS expression" << std::endl;
    }
|
    expression T_GR expression
    {
        std::cout << "expression -> expression T_GR expression" << std::endl;
    }
|
    expression T_EQ expression
    {
        std::cout << "expression -> expression T_EQ expression" << std::endl;
    }
|
    expression T_AND expression
    {
        std::cout << "expression -> expression T_AND expression" << std::endl;
    }
|
    expression T_OR expression
    {
        std::cout << "expression -> expression T_OR expression" << std::endl;
    }
|
    T_NOT expression
    {
        std::cout << "expression -> T_NOT expression" << std::endl;
    }
|
    T_OPEN expression T_CLOSE
    {
        std::cout << "expression -> T_OPEN expression T_CLOSE" << std::endl;
    }

    /* ----- Solution ----- */

|
    function_call
    {
        std::cout << "expression -> T_ID T_OPEN parameters T_CLOSE" << std::endl;
    }

    /* ----- Solution END ----- */

;

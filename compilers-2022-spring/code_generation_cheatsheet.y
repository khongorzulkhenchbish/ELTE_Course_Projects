/* For code generation for compilers we use assembly language. Idea: 
In assembly you don't have loops, but you can achieve the same thing with 
jump statements. in C++, in a for loop statement, you do the things inside 
the loop, increment the counter, evaluate if the loop should end or not and 
then repeat the process. all that is done with the special syntax. 
In assembly you have to do those things explicitly, declare where the loop 
starts (start label), do the things inside ($6->expr_code), check if the 
loop should end (cmp eax ...), if so, exit the loop (jump end), otherwise 
increase the counter (inc dword ...) and start the loop again (jmp start). */

// task: add code generation support for the "++" and "--" operators.
expression:
T_ID T_INC
{ 
  /* semantic starts */ 
  if( symbol_table.count(*$1) == 0 )
  {
    std::stringstream ss;
    ss << "Undeclared variable: " << *$1 << std::endl;
    error( ss.str().c_str() );
  }
  if (symbol_table[*$1].decl_type != integer)
  {
    std::stringstream ss;
    ss << "Non-integer value can not be incremented!" << std::endl;
    error( ss.str().c_str() );
  }
  /* semantic ends */ 
  /* code generation starts */ 
  $$ = new expression_descriptor(integer, "mov eax, ["+symbol_table[*$1].label+"]\n" +
                                          // assembly: mov destination, source
                                          // copy address into eax
                                          "add eax, 1\n" +
                                          // increment eax by 1
                                          "mov ["+symbol_table[*$1].label+"], eax\n");
                                          // copy eax into address
                                          // now the ID got increased by 1.
  /* code generation ends */ 
  delete $1;
}

T_ID T_DEC
{
    if( symbol_table.count(*$1) == 0 )
    {
      std::stringstream ss;
      ss << "Undeclared variable: " << *$1 << std::endl;
      error( ss.str().c_str() );
    }
    if (symbol_table[*$1].decl_type != integer)
    {
      std::stringstream ss;
      ss << "Non-integer value can not be decremented!" << std::endl;
      error( ss.str().c_str() );
    }
    $$ = new expression_descriptor(integer, "mov eax, ["+symbol_table[*$1].label+"]\n" +
                                            "sub eax, 1\n" +
                                            "mov ["+symbol_table[*$1].label+"], eax\n");
    delete $1;
}


// task. add code generation support for the newly introduced "for loop"
loop:
T_FOR T_ID T_ASSIGN expression T_TO expression T_DO statements T_DONE
// for i := 1+2 to 3+4 do i:i+1 done
{
    if( symbol_table.count(*$2) == 0 )
    {
        std::stringstream ss;
        ss << "Undeclared variable: " << *$2 << std::endl;
        error( ss.str().c_str() );
    }
    if(symbol_table[*$2].decl_type != integer || $4->expr_type != integer || $6->expr_type != integer)
    {
       std::stringstream ss;
       ss << d_loc__.first_line << ": Type error." << std::endl;
       error( ss.str().c_str() );
    }
    std::string start = new_label();
    std::string end = new_label();
    $$ = new std::string("" +
            $4->expr_code +
            // eval 1+2 into eax register, now eax = 3
            "mov [" + symbol_table[*$2].label + "], eax\n" +
            // i := eax(which is 3), now i = 3
            start + ":\n" +
            // start the loop 
            $6->expr_code +
            // eval 3+4 into eax, now eax = 7
            "cmp eax, [" + symbol_table[*$2].label + "]\n" +
            // eax == i ? => check if 3 is equal to 7
            "jb near " + end + "\n" +
            // if true end the loop
            *$8 +
            // exec i:= i + 1
            "inc dword [" + symbol_table[*$2].label + "]\n" +
            // inc DWORD PTR [var] — add one to the 32-bit integer stored at location var
            "jmp " + start + "\n" +
            // go to the start of the loop
            end + ":\n");
    delete $2;
    delete $4;
    delete $6;
    delete $8;
}

// task. goto - Hint for code generation: a label declaration in While 
// is a label in the assembly, while to goto should be compiled to a 
// "jmp <label>" instruction
statement:
T_ID T_COLON
{ 
    /* semantic starts */
    if( symbol_table.count(*$1) > 0 )
    {
        std::stringstream ss;
        ss << "Re-declared identifier: " << *$1 << ".\n"
        << "Line of previous declaration: " << symbol_table[*$1].decl_row << std::endl;
        error( ss.str().c_str() );
    }
    /* semantic check ends */
    /* code generation start because of new_label(0) */
    symbol_table[*$1] = var_data( d_loc__.first_line, goto_label, new_label() );
    $$ = new std::string(symbol_table[*$1].label + ":\n");
    /* code generation end */
    delete $1;
}
|
T_GOTO T_ID T_SEMICOLON
{
    if( symbol_table.count(*$2) == 0 || symbol_table[*$2].decl_type != goto_label)
    {
        std::stringstream ss;
        ss << "Undeclared label: " << *$2 << std::endl;
        error( ss.str().c_str() );
    }
    /* code gen start */
    $$ = new std::string("jmp " + symbol_table[*$2].label + "\n");
    /* code gen end */
    delete $2;
}


// task. Power operator: <exp1> ** <exp2>
expression T_POW expression
{
  if($1->expr_type != integer || $3->expr_type != integer)
  {
     std::stringstream ss;
     ss << d_loc__.first_line << ": Type error." << std::endl;
     error( ss.str().c_str() );
  }
  std::string zero = new_label();
  std::string loop = new_label();
  std::string end = new_label();
  $$ = new expression_descriptor(integer, "" +
    $3->expr_code +     // eval exp2 into eax
    "mov ebx, eax\n" +  // ebx = exp2
    $1->expr_code +     // eval exp1 into eax
    "mov ecx, eax\n"    // ecx = exp1

    "cmp ebx, 0\n" +            // if exp2 = 0
    "je near " + zero + "\n" +  // x^0 = 1
    "cmp ebx, 1\n" +            // if exp2 = 1
    "je near " + end + "\n" +   // x^1 = x
    "jmp near " + loop + "\n" + // pow > 1

    zero + ":\n" +              // 
    "mov eax, 1\n" +            // eax = 1
    "jmp near " + end + "\n" +  // end the loop

    loop + ":\n" +              // start of the loop
    "mul ecx\n" +               // eax *= ecx
    "dec ebx\n" +               // ebx --
    "cmp ebx, 1\n" +            // ebx == 1
    "ja near " + loop + "\n" +  // if ebx(exp2) > 1 then start the loop again

    end + ":\n");
  delete $1;
  delete $3;
}


// task. string - Hint for code generation: a string can not be read nor printed out, 
// the only supported operations are the assignment,  length calculation and 
// two binary operators (+, *). Based on this, it is sufficient to only store 
// one numeric value (the length of the string) instead of the actual string
program:
if(v.second.decl_type == integer || v.second.decl_type == string_type)
    std::cout << v.second.label << ": resd 1" << std::endl;
    // Added check for string type, since it stores a numerical value,
    // it behaves the same as an integer here.
    
declaration:
T_STRING T_ID T_SEMICOLON
{
    if( symbol_table.count(*$2) > 0 )
    {
        std::stringstream ss;
        ss << "Re-declared variable: " << *$2 << ".\n"
        << "Line of previous declaration: " << symbol_table[*$2].decl_row << std::endl;
        error( ss.str().c_str() );
    }
    symbol_table[*$2] = var_data( d_loc__.first_line, string_type, new_label() );
    delete $2;
}

assignment:
T_ID T_ASSIGN expression T_SEMICOLON
{
  if($3->expr_type == string_type)
      $$ = new std::string("" +
                    $3->expr_code + 
                    // eval expr into eax
                    "mov [" + symbol_table[*$1].label + "], eax\n");
                    // assign eax into id, in other words assign expr value into id
}

expression:
T_STRING_LIT
{
    std::string length = std::string(std::to_string($1->length()-2));
    // get the length of the string instead of actual string
    $$ = new expression_descriptor(string_type, "mov eax, " + length + " \n");
    // save the length into eax register
    delete $1;
}
|
expression T_ADD expression
    {
        if($1->expr_type == boolean || $1->expr_type != $3->expr_type)
        {
           std::stringstream ss;
           ss << d_loc__.first_line << ": Type error." << std::endl;
           error( ss.str().c_str() );
        }
        if ($1->expr_type == integer && $3->expr_type == integer) {
            $$ = new expression_descriptor(integer, "" +
                    $3->expr_code +
                    "push eax\n" +
                    $1->expr_code +
                    "pop ebx\n" +
                    "add eax, ebx\n");
        }
        
        /* ----- Solution ----- */

        if ($1->expr_type == string_type && $3->expr_type == string_type) {
            $$ = new expression_descriptor(string_type, "" +
                    $3->expr_code +
                    "push eax\n" +
                    $1->expr_code +
                    "pop ebx\n" +
                    "add eax, ebx\n");
        }

        /* ----- Solution END ----- */

        delete $1;
        delete $3;
    }
  |
  expression T_MUL expression
    {
        if($1->expr_type == boolean || $3->expr_type != integer)
        {
           std::stringstream ss;
           ss << d_loc__.first_line << ": Type error." << std::endl;
           error( ss.str().c_str() );
        }
        if($1->expr_type == integer) {
            $$ = new expression_descriptor(integer, "" +
                    $3->expr_code +
                    "push eax\n" +
                    $1->expr_code +
                    "pop ebx\n" +
                    "mul ebx\n");
        }

        /* ----- Solution ----- */

        if($1->expr_type == string_type) {
            $$ = new expression_descriptor(string_type, "" +
                    $3->expr_code +
                    "push eax\n" +
                    $1->expr_code +
                    "pop ebx\n" +
                    "mul ebx\n");
        }

        /* ----- Solution END ----- */

        delete $1;
        delete $3;
    }
  | 
  expression T_EQ expression
    {

        /* ----- Solution ----- */

        if($1->expr_type != $3->expr_type || $1->expr_type == string_type)
        {
           std::stringstream ss;
           ss << d_loc__.first_line << ": Type error." << std::endl;
           error( ss.str().c_str() );
        }

        /*
        * Added check for string_type, since we should not be able to check if
        * strings are equal.
        */

        /* ----- Solution END ----- */

        $$ = new expression_descriptor(boolean, "" +
                $3->expr_code +
                "push eax\n" +
                $1->expr_code +
                "pop ebx\n" +
                "cmp eax, ebx\n" +
                "sete al\n");
        delete $1;
        delete $3;
    }
|
T_LENGTH T_OPEN expression T_CLOSE
{
    if($3->expr_type != string_type)
    {
       std::stringstream ss;
       ss << d_loc__.first_line << ": Type error." << std::endl;
       error( ss.str().c_str() );
    }
    $$ = new expression_descriptor(integer, "" + $3->expr_code);
    // save the value into eax
    delete $3;
}


// task. time: Hint for code generation: both the minutes and the hours should be
// extracted from the time literal, and store them like hours*28 + minutes. This 
// way the hours can be reached by ah register while the minutes by the al register.
program:
if(v.second.decl_type == time_type)
  std::cout << v.second.label << ": resw 1" << std::endl;

declaration:
T_ID 
{
  if(symbol_table[*$1].decl_type == time_type)
  {
      $$ = new expression_descriptor(symbol_table[*$1].decl_type,
              "mov ax, [" + symbol_table[*$1].label + "]\n");
  }
}
|
T_TIME T_ID T_SEMICOLON
{
    if( symbol_table.count(*$2) > 0 )
    {
        std::stringstream ss;
        ss << "Re-declared variable: " << *$2 << ".\n"
        << "Line of previous declaration: " << symbol_table[*$2].decl_row << std::endl;
        error( ss.str().c_str() );
    }
    symbol_table[*$2] = var_data( d_loc__.first_line, time_type, new_label() );
    delete $2;
}
assignment:
T_ID T_ASSIGN expression T_SEMICOLON
{
  if($3->expr_type == time_type)
  $$ = new std::string("" +
        $3->expr_code +
        "mov [" + symbol_table[*$1].label + "], ax\n");
}
expression:
T_TIME_LIT
{
    std::string hour = $1->substr(0,2);
    std::string minute = $1->substr(3);
    $$ = new expression_descriptor(time_type, std::string("") + 
            "mov ah, " + hour + "\n" +
            "mov al, " + minute + "\n");
    delete $1;
}
expression T_EQ expression
{
    /* ----- Solution ----- */
    if($1->expr_type != $3->expr_type || $1->expr_type == time_type)
    {
       std::stringstream ss;
       ss << d_loc__.first_line << ": Type error." << std::endl;
       error( ss.str().c_str() );
    }

    /*
    * Added check for time_type, since we should not be able to check if
    * times are equal.
    */

    /* ----- Solution END ----- */

    $$ = new expression_descriptor(boolean, "" +
            $3->expr_code +
            "push eax\n" +
            $1->expr_code +
            "pop ebx\n" +
            "cmp eax, ebx\n" +
            "sete al\n");
    delete $1;
    delete $3;
}
|
T_HOUR T_OPEN expression T_CLOSE
    {
        if($3->expr_type != time_type)
        {
           std::stringstream ss;
           ss << d_loc__.first_line << ": Type error." << std::endl;
           error( ss.str().c_str() );
        }
        $$ = new expression_descriptor(integer, std::string("") +
                "xor eax, eax\n" +
                $3->expr_code +
                "mov al, ah\n" +
                "xor ah, ah\n");
        delete $3;
    }
|
    T_MINUTE T_OPEN expression T_CLOSE
    {
        if($3->expr_type != time_type)
        {
           std::stringstream ss;
           ss << d_loc__.first_line << ": Type error." << std::endl;
           error( ss.str().c_str() );
        }
        $$ = new expression_descriptor(integer, std::string("") + 
                "xor eax, eax\n" +
                $3->expr_code +
                "xor ah, ah\n");
        delete $3;
    }

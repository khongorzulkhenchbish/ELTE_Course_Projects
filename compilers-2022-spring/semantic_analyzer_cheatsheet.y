/* Semantic analysis checks 2 things. if the variable is declared before and if it's data type is as expected.
1. check ID declaration.
	in declaration: 
	symbol_table.count(*$ID_index) > 0 
	declared => print the line number and throw re-declared error, 
	undeclared => add into the symbol table: symbol_table[*$ID_index] = var_data( line_number, ID_type );
2. check ID type matches.
	in expression|statement: 
	(symbol_table.count(*$1) == 0)
	undeclared => throws undeclared error
	(symbol_table[*$1].decl_type != boolean) 
	unmatching type => throw type error, here the boolean is declared in the enum inside semantics.h file.
3. define the return type only inside expression:
	for example: expression T_ADD expression
	return type: $$ = new type(integer);
	for example: T_ID
	return type: $$ = new type(symbol_table[*$1].decl_type); --the id type can be anything */

// task. ++ and -- operators (both of them is working only on integer values)
expression:
T_ID T_INC
{ 
  /* works only on variables that are declared */ 
  if( symbol_table.count(*$1) == 0 )
  {
    std::stringstream ss;
    ss << "Undeclared variable: " << *$1 << std::endl;
    error( ss.str().c_str() );
  }
  /* works only on variables that has an integer type */
  if(symbol_table[*$1].decl_type != integer)
  {
    std::stringstream ss;
    ss << "Non-integer value can not be incremented!" << std::endl;
    error( ss.str().c_str() );
  }
  /* return type will be integer */
  $$ = new type(integer);
  /* frees the memory */
  delete $1;
}


// task. for loop (with a syntax like this: for <var> := <expr> to <expr> do <stmts> done)
loop:
T_FOR T_ID T_ASSIGN expression T_TO expression T_DO statements T_DONE
{
  /* checks if the <var> is declared */
  if( symbol_table.count(*$2) == 0 )
  {
    std::stringstream ss;
    ss << "Undeclared variable: " << *$2 << std::endl;
    error( ss.str().c_str() );
  }
  /* checks if the <var>, and both <expr> is of type integer */
  if(symbol_table[*$2].decl_type != integer || *$4 != integer || *$6 != integer)
  {
    std::stringstream ss;
    ss << d_loc__.first_line << ": Type error." << std::endl;
    error( ss.str().c_str() );
  }
  // 
  delete $2;
  delete $4;
  delete $6;
}


// task. time type (you can start off with this implementation - the lexical&syntax parts are done already)
declaration:
T_TIME T_ID T_SEMICOLON
{
  if( symbol_table.count(*$2) > 0 )
  {
    std::stringstream ss;
    ss << "Re-declared variable: " << *$2 << ".\n"
    << "Line of previous declaration: " << symbol_table[*$2].decl_row << std::endl;
    error( ss.str().c_str() );
  }
  // when the variable is declared for the first time, add it to the symbol table
  // var_data(int lineIndex, type variableType)
  symbol_table[*$2] = var_data( d_loc__.first_line, time_type );
  delete $2;
}

// task. extend the type-system with the new 'time_type' type
expression:
T_TIME_LIT 
{
    $$ = new type(time_type);
}

// task. the hour(...) and minute(...) functions can only accept a time typed expression
T_HOUR T_OPEN expression T_CLOSE
    {
        if(*$3 != time_type)
    {
       std::stringstream ss;
       ss << d_loc__.first_line << ": Type error." << std::endl;
       error( ss.str().c_str() );
    }
        $$ = new type(integer);
        delete $3;
    }
|
T_MINUTE T_OPEN expression T_CLOSE
{
    if(*$3 != time_type)
    {
       std::stringstream ss;
       ss << d_loc__.first_line << ": Type error." << std::endl;
       error( ss.str().c_str() );
    }
    $$ = new type(integer);
    delete $3;
}

// task. other binary operators behavior is not defined for the time type
expression T_EQ expression
{
    if(*$1 != *$3 || *$1==time_type)
    {
       std::stringstream ss;
       ss << d_loc__.first_line << ": Type error." << std::endl;
       error( ss.str().c_str() );
    }
    $$ = new type(boolean);
    delete $1;
    delete $3;
}


// task. string type (you can start off with this implementation - the lexical&syntax parts are done already)
 T_STRING T_ID T_SEMICOLON
 {
    if( symbol_table.count(*$2) > 0 )
		{
			std::stringstream ss;
			ss << "Re-declared variable: " << *$2 << ".\n"
			<< "Line of previous declaration: " << symbol_table[*$2].decl_row << std::endl;
			error( ss.str().c_str() );
		}
		symbol_table[*$2] = var_data( d_loc__.first_line, string);
    delete $2;
 }
// task. extend the type-system with the new 'string_type' type
expression:
T_STRING_LIT
{
    $$ = new type(string);
}

// task. the length(...) function can only accept string typed expression
T_LENGTH T_OPEN expression T_CLOSE
{
    if(*$3 != string)
    {
       std::stringstream ss;
       ss << d_loc__.first_line << ": Type error." << std::endl;
       error( ss.str().c_str() );
    }
    $$ = new type(integer);
    delete $3;   
}
// task. the + operator should work on two strings yielding a string (concatenation)
expression:
expression T_ADD expression
{
	if(*$1 == boolean || *$3 == boolean || *$1 != *$3)
	{
	std::stringstream ss;
	ss << d_loc__.first_line << ": Type error." << std::endl;
	error( ss.str().c_str() );
	}
	if(*$1 == integer)
	{
	    $$ = new type(integer);
	}
	else
	{
	    $$ = new type(string);
	}
	delete $1;
	delete $3;
}
// task. the * operator should work if its first argument is a string and the second is an integer, 
// task. resulting in a string (multiplication of the string)
expression:
expression T_MUL expression
{
if(*$1 == boolean || *$3 != integer)
{
   std::stringstream ss;
   ss << d_loc__.first_line << ": Type error." << std::endl;
   error( ss.str().c_str() );
}
if(*$1 == integer)
{
	    $$ = new type(integer);
}
else
{
    $$ = new type(string);
}
delete $1;
delete $3;


// task. goto, let us introduce the goto <label> and the <label>: statements 
// task. jumps are only possible backward, so first we have to have a 
// task. <label>: then after somewhere a goto <label> statement - let's check this!
T_ID T_COLON
{
	if( symbol_table.count(*$1) > 0 )
	{
	    std::stringstream ss;
	    ss << "Re-declared identifier: " << *$1 << ".\n"
	    << "Line of previous declaration: " << symbol_table[*$1].decl_row << std::endl;
	    error( ss.str().c_str() );
	}
	symbol_table[*$1] = var_data( d_loc__.first_line, goto_label );
	delete $1;
}
// task. more precisely, check if a goto is jumping to an already defined 
// task. label (OK), or not (a semantic error)
statement:
T_GOTO T_ID
{
	if( symbol_table.count(*$2) == 0 )
	{
		std::stringstream ss;
		ss << "Undeclared variable: " << *$2 << std::endl;
		error( ss.str().c_str() );
	}
	if (symbol_table[*$2].decl_type != goto_label)
	{
		std::stringstream ss;
		ss << d_loc__.first_line << ": Type error." << std::endl;
		error( ss.str().c_str() );
	}
	delete $2;
}
// task. enum type = {goto_label} in semantics.h

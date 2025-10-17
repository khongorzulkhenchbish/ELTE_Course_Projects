#ifndef SEMANTICS_H
#define SEMANTICS_H

#include<iostream>
#include<string>
#include<map>
#include<sstream>

    /* ----- Solution ----- */

enum type { integer, boolean, goto_label };

    /*
	* Added 'goto_lable' type
	* This solution is for when a lable and
	* variable cannot have the same name.
	* If you want the other solution, the best way is to 
	* declare another table in Parser.h which holds all labels.
	* Give it a try.
	*/

    /* ----- Solution END ----- */

struct var_data {
	int decl_row;
	type decl_type;
	var_data(){}
	var_data(int i, type t)
	{
		decl_row = i;
		decl_type = t;
	}
};

#endif

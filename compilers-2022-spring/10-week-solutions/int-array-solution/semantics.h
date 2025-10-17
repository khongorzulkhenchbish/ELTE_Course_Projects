#ifndef SEMANTICS_H
#define SEMANTICS_H

#include<iostream>
#include<string>
#include<map>
#include<sstream>

    /* ----- Solution ----- */

enum type { integer, boolean, int_arr };

    /*
	* Added int_arr types
	*/

    /* ----- Solution END ----- */

struct expression_descriptor {
	type expr_type;
	std::string expr_code;
	expression_descriptor(type t, std::string s) {
		expr_type = t;
		expr_code = s;
	}
};

struct var_data {
	int decl_row;
	type decl_type;
    std::string label;

    /* ----- Solution ----- */

	std::string size;
	var_data(){}
	var_data(int i, type t, std::string l, std::string s)
	{
		decl_row = i;
		decl_type = t;
        label = l;
		size = s;
	}

    /*
	* Added size to variable data so that
	* we can store how much space we need 
	* to allocate memory for arrays.
	*/

    /* ----- Solution END ----- */

};

#endif

//Author:    Khongorzul Khenchbish
//Date:      2020.03.17
//Title:     Block matrix

#include "block.h"
#include <iostream>
#include <iomanip>

using namespace std;

//Task: 	constructor with size
//Input:    int k     - the new size
//Output:   Block this - default matrix
//Activity: creates the array of the block of size k
Block::Block(int k, int l)
{
    if (k < 0 || l < 0) throw INVALID;
    _m1.clear();
    _m1.resize(k, vector<int>(k, 0));
    _m2.clear();
    _m2.resize(l, vector<int>(l, 0));
}

//Task: 	constructor the elements of the diagonal
//Input:    vector<int> v     - the new diagonal
//Output:   Diag this         - default matrix
//Activity: creates the array of the block and fills in its elements based on vector v
Block::Block(const std::vector<std::vector<int>>& b1, const std::vector<std::vector<int>>& b2)
{
    _m1 = b1;
    _m2 = b2;
}

//Task: 	copy constructor
//Input:    Block a    - matrix
//Output:   Block this - default matrix
//Activity: creates the array of the diagonal and fills in its elements based on matrix a
Block::Block(const Block& a)
{
    int side1 = a.getSize()[0];
    _m1.resize(side1);
    for(int i = 0; i < side1; ++i) _m1[i].resize(side1);

    for(int i = 0; i < side1; ++i) {
        for(int j = 0; j < side1; ++j) {
            _m1[i][j] = a._m1[i][j];
        }
    }

    int side2 = a.getSize()[1];
    _m2.resize(side2);
    for(int i = 0; i < side2; ++i) _m2[i].resize(side2);

    for(int i = 0; i < side2; ++i) {
        for(int j = 0; j < side2; ++j) {
            _m2[i][j] = a._m2[i][j];
        }
    }
}

//Task: 	assignment operator
//Input:    Diag a    - matrix
//Output:   Diag this - default matrix
//Activity: fills in the elements of the diagonal based on matrix a
Block& Block::operator=(const Block& a)
{
    int side1 = a.getSize()[0];
    int side2 = a.getSize()[1];
    reSize(side1, side2);

    for(int i = 0; i < side1; ++i) {
        for(int j = 0; j < side1; ++j) {
            _m1[i][j] = a._m1[i][j];
        }
    }

    for(int i = 0; i < side2; ++i) {
        for(int j = 0; j < side2; ++j) {
            _m2[i][j] = a._m2[i][j];
        }
    }
    return *this;
}

//Task: 	resizing a matrix
//Input:    int k     - the new size
//Output:   Diag this - default matrix
//Activity: resizes the matrix to k
void Block::reSize(int side1, int side2)
{
    if(side1 < 0 || side2 < 0) throw INVALID;
    _m1.resize(side1, vector<int>(side1, 0));
    _m2.resize(side2, vector<int>(side2, 0));
}

//Task: 	adding
//Input:    Diag a    - matrix
//          Diag b    - matrix
//Output:   Diag      - result matrix
//Activity: adds the elements of the diagonals of the matrices
Block operator+(const Block& a ,const Block& c)
{
    int side_a1 = a.getSize()[0];
    int side_a2 = a.getSize()[1];
    int side_c1 = c.getSize()[0];
    int side_c2 = c.getSize()[1];

    if(side_a1 != side_c1 || side_a2 != side_c2) throw Block::DIFFERENT;

    Block sum(side_a1, side_a2);

    for(int i = 0; i < side_a1; ++i) {
        for(int j = 0; j < side_a1; ++j) {
            sum._m1[i][j] = a._m1[i][j] + c._m1[i][j];
        }
    }

    for(int i = 0; i < side_a2; ++i) {
        for(int j = 0; j < side_a2; ++j) {
            sum._m2[i][j] = a._m2[i][j] + c._m2[i][j];
        }
    }

    return sum;
}

//Task: 	multiplying
//Input:    Diag a    - matrix
//          Diag b    - matrix
//Output:   Diag      - result matrix
//Activity: multiplies the elements of the diagonals of the matrices
Block operator*(const Block& a ,const Block& c)
{
    int side_a1 = a.getSize()[0];
    int side_a2 = a.getSize()[1];
    int side_c1 = c.getSize()[0];
    int side_c2 = c.getSize()[1];

    if(side_a1 != side_c1 || side_a2 != side_c2) throw Block::DIFFERENT;

    Block mul(side_a1, side_a2);

    int val = 0;

    for(int i = 0; i < side_a1; ++i) {
        for(int j = 0; j < side_a1; ++j) {
            val = 0;
            for(int k = 0; k < side_a1; ++k) {
                val += a._m1[i][k] * c._m1[k][j];
            }
            mul._m1[i][j] = val;
        }
    }

    for(int i = 0; i < side_a2; ++i) {
        for(int j = 0; j < side_a2; ++j) {
            val = 0;
            for(int k = 0; k < side_a2; ++k) {
                val += a._m2[i][k] * c._m2[k][j];
            }
            mul._m2[i][j] = val;
        }
    }

    return mul;
}

//Task: 	writing
//Input:    ostream os - target of writing
//          Diag a     - matrix
//Output:   ostream os - target of writing
//Activity: writes the elements of the matrix
ostream& operator<<(ostream& os, const Block& a)
{
    int side1 = a.getSize()[0];
    int side2 = a.getSize()[1];

    int side = side1 + side2;

    for(int i = 0; i < side; ++i) {
        for(int j = 0; j < side; ++j) {
            if(i < side1 && j < side1) {
                os << setw(4) << a._m1[i][j];
            } else if(i >= side1 && j >= side1) {
                os << setw(4) << a._m2[i-side1][j-side1];
            } else {
                os << setw(4) << 0;
            }
        }
        os << endl;
    }
    return os;
}

//Task: 	reading
//Input:    istream is - source of writing
//          Diag a     - matrix
//Output:   istream is - source of writing
//Activity: reads the elements of the diagonal of the matrix
istream& operator>>(istream& is, Block& a)
{
    int side1, side2;
    is >> side1 >> side2;
    a.reSize(side1, side2);

    for(int i = 0; i < side1; ++i) {
        for(int j = 0; j < side1; ++j) {
            is >> a._m1[i][j];
        }
    }

    for(int i = 0; i < side2; ++i) {
        for(int j = 0; j < side2; ++j) {
            is >> a._m2[i][j];
        }
    }

    return is;
}

//Task: 	getting
//Input:    int i,j - indexes of the element
//Output:   int     - the element of the matrix in the ith row and jth column
//Activity: gets the given element of the diagonal matrix
int Block::operator()(int i, int j) const
{
    int side1 = getSize()[0];
    int side2 = getSize()[1];
    int side = side1 + side2;

    if (i >= side || i < 0 || j >= side || j < 0) throw OVERINDEXED;
    if(i < side1 && j < side1) {
        return _m1[i][j];
    } else if(i >= side1 && j >= side1) {
        return _m2[i-side1][j-side1];
    }
    return 0;
}

//Author:    Khongorzul Khenchbish
//Date:      2020.03.17
//Title:     Block matrix

#include <iostream>
#include "block.h"

using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE


//class of menu for block matrix
class Menu
{
private:
    Block a;

    void menuWrite();
    void get() const;
    void print();
    void sum();
    void mul();
    void read();

public:
    Menu() : a(0,0) { }
    void run();
};

void Menu::run()
{
    int n = 0;
    do
    {
        menuWrite();
        cout << endl << ">>>>" ;
        cin >> n;
        switch(n)
        {
        case 1:
            get();
            break;
        case 2:
            print();
            break;
        case 3:
            sum();
            break;
        case 4:
            mul();
            break;
        case 5:
            read();
            break;
        }
    }
    while(n!=0);
}

void Menu::menuWrite()
{
    cout << endl << endl;
    cout << " 0. - Quit" << endl;

    cout << " 1. - Get an element of the matrix" << endl;
    cout << " 2. - Print matrix" << endl;
    cout << " 3. - Add matrices" << endl;
    cout << " 4. - Multiply matrices" << endl;
    cout << " 5. - Read matrix" << endl;
}

void Menu::get() const
{
    int i,j;
    cout << "Give the index of the row: ";
    cin >> i;
    cout << "Give the index of the column: ";
    cin >> j;
    try
    {
        cout << "a[" << i << "," << j << "]= " << a(i-1,j-1) << endl;
    }
    catch(Block::Exceptions ex)
    {
        if(ex == Block::OVERINDEXED)
            cout << "Overindexing!" << endl;
        else
            cout << "Unhandled ecxeption!" << endl;
    }
}


void Menu::print()
{
    cout << a << endl;
}

void Menu::sum()
{
    try
    {
        Block b;

        cout << "Give the block sizes and the items of the second  matrix: " << endl;
        cin >> b;
        cout << "Sum of the matrices: " << endl;
        cout << a + b << endl;
    }
    catch(Block::Exceptions ex)
    {
        if(ex == Block::INVALID)
            cout << "Invalid size!" << endl;
        if(ex == Block::DIFFERENT)
            cout << "Different sizes!" << endl;
    }
}

void Menu::mul()
{
    try
    {
        Block b;

        cout << "Give 2 block sizes and the items of the second  matrix: " << endl;
        cin >> b;
        cout << "Product of the matrices: " << endl;
        cout << a * b << endl;
    }
    catch(Block::Exceptions ex)
    {
        if(ex == Block::INVALID)
            cout << "Invalid size!" << endl;
        if(ex == Block::DIFFERENT)
            cout << "Different sizes!" << endl;
    }
}

void Menu::read()
{
    try
    {
        cout << "Give 2 block sizes and the items of the matrix: ";
        cin >> a;
    }
    catch(Block::Exceptions ex)
    {
        if(ex == Block::INVALID)
            cout << "Invalid size!" << endl;
        else
            cout << "Unhandled ecxeption!" << endl;
    }
}

int main()
{
    setlocale(LC_ALL,"Hun");
    Menu m;
    m.run();
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("create", "inp.txt")
{
    const string fileName = "inp.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }


    Block b;
    in >> b; // 2,1

    CHECK(b(0,0) == 5);
    CHECK(b(0,1) == 5);
    CHECK(b(1,0) == 5);
    CHECK(b(1,1) == 5);
    CHECK(b(2,2) == 5);


    Block a;
    in >> a; // 1,1

    CHECK(a(0,0)==3);
    CHECK(a(1,1)==3);


    Block c;
    in >> c; // 2, 3

    CHECK(c(0,0) == 1);
    CHECK(c(0,1) == 1);

    CHECK(c(1,0) == 1);
    CHECK(c(1,1) == 1);

    CHECK(c(2,2) == 1);
    CHECK(c(2,3) == 1);
    CHECK(c(2,4) == 1);

    CHECK(c(3,2) == 1);
    CHECK(c(3,3) == 1);
    CHECK(c(3,4) == 1);

    CHECK(c(4,2) == 1);
    CHECK(c(4,3) == 1);
    CHECK(c(4,4) == 1);


    //20 cases should be passed
}

TEST_CASE("getting an element of the matrix", "")
{
    Block a({ {1} }, { {1} } );
    CHECK(a(0,0) == 1);
    // 1 case should be passed
}


TEST_CASE("copy constructor", "inp.txt")
{
    const string fileName = "inp.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Block a;
    in >> a; // 2,1

    Block b = a;

    CHECK(a(0,0) == b(0,0));
    CHECK(a(0,1) == b(0,1));
    CHECK(a(1,0) == b(1,0));
    CHECK(a(1,1) == b(1,1));

    CHECK(a(2,2) == b(2,2));

    //4 cases
}


TEST_CASE("assignment operator", "inp.txt")
{
    const string fileName = "inp.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Block a, b; // 3
    in >> a; //1,1

    b = a; // check every non-zero item
    CHECK(a(0,0) == b(0,0));
    CHECK(a(0,1) == b(0,1));
    CHECK(a(1,0) == b(1,0));
    CHECK(a(1,1) == b(1,1));

    CHECK(a(2,2) == b(2,2));

    Block c; // 3
    c = b = a; // check every non-zero item
    CHECK(a(0,0) == c(0,0));
    CHECK(a(0,1) == c(0,1));
    CHECK(a(1,0) == c(1,0));
    CHECK(a(1,1) == c(1,1));

    CHECK(a(2,2) == c(2,2));

    a = a; // check every non-zero item
    CHECK(a(0,0) == a(0,0));
    CHECK(a(0,1) == a(0,1));
    CHECK(a(1,0) == a(1,0));
    CHECK(a(1,1) == a(1,1));

    CHECK(a(2,2) == a(2,2));
}


TEST_CASE("sum", "inp2.txt")
{
    const string fileName = "inp2.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Block a, b, c, d, f, z; //
    in >> a >> b >> z;

    c = a + b; // check every non-zero item
    d = b + a;

    CHECK(c(0,0) == d(0,0));
    CHECK(c(0,1) == d(0,1));
    CHECK(c(1,0) == d(1,0));
    CHECK(c(1,1) == d(1,1));

    CHECK(c(2,2) == d(2,2));
    CHECK(c(2,3) == d(2,3));
    CHECK(c(3,2) == d(3,2));
    CHECK(c(3,3) == d(3,3));


    d = (a + b) + c;
    f = a + (b + c); // check every non-zero item
    CHECK(d(0,0) == f(0,0));
    CHECK(d(0,1) == f(0,1));
    CHECK(d(1,0) == f(1,0));
    CHECK(d(1,1) == f(1,1));

    CHECK(d(2,2) == f(2,2));
    CHECK(d(2,3) == f(2,3));
    CHECK(d(3,2) == f(3,2));
    CHECK(d(3,3) == f(3,3));

    c = a + z; // check every non-zero item
    CHECK(c(0,0) == a(0,0));
    CHECK(c(0,1) == a(0,1));
    CHECK(c(1,0) == a(1,0));
    CHECK(c(1,1) == a(1,1));

    CHECK(c(2,2) == a(2,2));
    CHECK(c(2,3) == a(2,3));
    CHECK(c(3,2) == a(3,2));
    CHECK(c(3,3) == a(3,3));
}


TEST_CASE("multiply", "inp2.txt")
{
    const string fileName = "inp2.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Block a, b, c, d, e, z; // 3
    in >> a >> b >> z >> e;

    c = a * b;
    CHECK(c(0,0) == 3);
    CHECK(c(0,1) == 3);
    CHECK(c(1,0) == 7);
    CHECK(c(1,1) == 7);

    CHECK(c(2,2) == 11);
    CHECK(c(2,3) == 11);
    CHECK(c(3,2) == 15);
    CHECK(c(3,3) == 15);

    d = a * z;
    CHECK(d(0,0) == 0);
    CHECK(d(0,1) == 0);
    CHECK(d(1,0) == 0);
    CHECK(d(1,1) == 0);

    CHECK(d(2,2) == 0);
    CHECK(d(2,3) == 0);
    CHECK(d(3,2) == 0);
    CHECK(d(3,3) == 0);

    c = a * e;
    CHECK(c(0,0) == a(0,0));
    CHECK(c(0,1) == a(0,1));
    CHECK(c(1,0) == a(1,0));
    CHECK(c(1,1) == a(1,1));

    CHECK(c(2,2) == a(2,2));
    CHECK(c(2,3) == a(2,3));
    CHECK(c(3,2) == a(3,2));
    CHECK(c(3,3) == a(3,3));
}


TEST_CASE("exceptions", "")
{

    Block a(3,3);

    try
    {
        a(6,6);
    }
    catch(Block::Exceptions ex)
    {
        CHECK(ex == Block::OVERINDEXED);
    }

    try
    {
        a(-1,4);
    }
    catch(Block::Exceptions ex)
    {
        CHECK(ex == Block::OVERINDEXED);
    }

    Block emp;
    try {
        emp(2,5);
    }
    catch(Block::Exceptions ex)
    {
        CHECK(ex == Block::OVERINDEXED);
    }

    Block b(2,3);
    Block c(1,3);

    try
    {
        a = b;
    }
    catch(Block::Exceptions ex)
    {
        CHECK(ex == Block::DIFFERENT);
    }

    try
    {
        c = a + b;
    }
    catch(Block::Exceptions ex)
    {
        CHECK(ex == Block::DIFFERENT);
    }

    try
    {
        c = a * b;
    }
    catch(Block::Exceptions ex)
    {
        CHECK(ex == Block::DIFFERENT);
    }
}
#endif


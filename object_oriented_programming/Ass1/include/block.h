//Author:    Khongorzul Khenchbish
//Date:      2020.03.17
//Title:     Block matrix

#pragma once
#include <iostream>
#include <vector>

//Class of block matrices
//Methods: add, multiply, print, refer to an element
//Representation: only the nonzero block elements

class Block {
public:
    enum Exceptions{OVERINDEXED, NULLPART, DIFFERENT, INVALID};

    Block(){
    for(std::vector<int> v1 : _m1) v1.clear();
    for(std::vector<int> v2 : _m2) v2.clear();}
    Block(int k, int l);
    ~Block() { }
    Block(const std::vector<std::vector<int>> &b1, const std::vector<std::vector<int>> &b2);
    Block(const Block& a);
    Block& operator=(const Block& a);
    int* getSize() const {
        static int r[2];
        r[0] = _m1.size();
        r[1] = _m2.size();
        return r;
    }

    int operator()(int i, int j) const;
    //int& operator()(int i, int j);

    friend Block operator+ (const Block& a, const Block& c);
    friend Block operator* (const Block& a, const Block& c);
    friend std::istream& operator>> (std::istream& s, Block& a);
    friend std::ostream& operator<< (std::ostream& s, const Block& a);

private:
    std::vector<std::vector<int>> _m1;
    std::vector<std::vector<int>> _m2;

    void reSize(int k, int l);
};

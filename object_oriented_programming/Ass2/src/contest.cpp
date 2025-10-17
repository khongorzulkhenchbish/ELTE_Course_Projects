#include "contest.h"

using namespace std;

//Input:    string str  - the test file's name
//Activity: tries to open the given file. If the opening fails, it throws a "FileError" exception.
ContestEnor::ContestEnor(const std::string &filename) throw (FileError)
{
    _f.open(filename);
    if(_f.fail()) throw MissingInputFile;
}

//Task: 	Reading the next row of the input file
//Input:    ifstream _f  - the test file
//Output:   Contest _cur - the next contest
//          bool _end    - the end of the enumeration
//Activity:
void ContestEnor::next() {
    string line;
    getline(_f, line, '\n');
    if( !(_end = _f.fail()) ) {
        istringstream is(line);
        is >> _cur.anglerName >> _cur.contestId;
        _cur.catfish = 0, _cur.otherfish = 0;
        string fish;
        int size;
        while(is >> fish >> size) {
            if(fish == "catfish")
                ++_cur.catfish;
            else
                ++_cur.otherfish;
        }
    }
}

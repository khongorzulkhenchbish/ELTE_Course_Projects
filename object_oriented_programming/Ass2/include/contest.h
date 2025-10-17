#ifndef CONTEST_H
#define CONTEST_H

#pragma once

#include <fstream>
#include <sstream>
#include <string>

//Datatype of contests
struct Contest {
    std::string anglerName;
    std::string contestId;
    int catfish;
    int otherfish;
};


//Datatype of the enumerator of contests
//This is the enumerator for the first part
class ContestEnor {
    private:
        std::ifstream _f;
        Contest _cur;
        bool _end;

    public:
        enum FileError{MissingInputFile};
        ContestEnor(const std::string &filename) throw (FileError);
        void first() { next(); }
        void next();
        Contest current() const { return _cur; }
        bool end() const { return _end; }

};

#endif // CONTEST_H

#include <string>
#ifndef COLONY_H
#define COLONY_H


class Colony
{
    public:
        std::string _name;
        char _species;
        double _animals;
        unsigned int _turn;

        Colony() {}
        Colony(const std::string &n, const char &s, const int a = 0) : _name(n), _species(s), _animals(a) {}


        std::string name() const { return _name; }
        void changeAnimal(int a) { _animals += double(a); }
        void incTurn() { _turn ++; }
        void decAnimal(double a) { _animals=a; }
        void offspring(int n, double m) { if (_turn>0&&_turn%n==0) _animals+=m; }
        virtual ~Colony(){};
        friend std::ostream& operator<< (std::ostream& os, const Colony* c);
};





#endif // COLONY_H

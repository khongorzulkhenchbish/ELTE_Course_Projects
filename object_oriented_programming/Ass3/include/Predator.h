#ifndef PREDATOR_H
#define PREDATOR_H
#include "colony.h"
#include "Prey.h"

class Predator : public Colony {
    public:
        Predator(const std::string &n, const char &s, const int a) : Colony(n, s, a) {}
        virtual void attack(Prey* &prey) = 0;
        virtual ~Predator() {};


};

class Fox : public Predator {
    public:
        Fox(const std::string &n, const char &s, const int a) : Predator(n, s, a) {}

        void attack(Prey* &prey) override {
            this->incTurn();
            this->offspring(8,this->_animals/4);
            prey->attack(this);
        }
};

// class of Owl

class Owl : public Predator {
    public:
        Owl(const std::string &n, const char &s, const int a) : Predator(n, s, a) {}
        static Owl* instance();
        void attack(Prey* &prey) override {
            this->incTurn();
            this->offspring(8,2*(this->_animals/4));
            prey->attack(this);
        }
};

class Wolf : public Predator {
    public:
        Wolf(const std::string &n, const char &s, const int a) : Predator(n, s, a) {}
        void attack(Prey* &prey) override {
            this->incTurn();
            this->offspring(8,3*(this->_animals/4));
            prey->attack(this);
        }
};


#endif // PREDATOR_H

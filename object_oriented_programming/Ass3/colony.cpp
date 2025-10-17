#include "colony.h"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& os, const Colony* c)
{
    if(c->_species=='l' || c->_species=='h' || c->_species=='g') {
        os << "Prey: ";
    } else {
        os << "Pred: ";
    }
    os << c->name() << ", " << c->_animals <<", turn="<< c->_turn<< endl;
    return os;
}

#include "Prey.h"
#include "Predator.h"

//implementation of class Lemming

Lemming* Lemming::_instance=nullptr;
Lemming* Lemming::instance()
{
    if(_instance==nullptr) {
        _instance = new Lemming();
    }
    return _instance;
}

void Lemming::destroy()
{
	if ( nullptr!=_instance )
	{
		delete _instance;
		_instance = nullptr;
	}
}

Prey* Lemming::attack(Fox *f)
{
    this->incTurn();
    this->offspring(2,this->_animals);
    if(this->_animals>200) this->decAnimal(30);


    if(this->_animals>=4*f->_animals) {
        this->changeAnimal(-4*f->_animals);
    } else {
        f->decAnimal(f->_animals-f->_animals/4);
    }
    return this;
}

Prey* Lemming::attack(Owl *o)
{
    this->incTurn();
    this->offspring(2,this->_animals);
    if(this->_animals>200) this->decAnimal(30);


    if(this->_animals>=4*o->_animals) {
        this->changeAnimal(-4*o->_animals);
    } else {
        o->decAnimal(o->_animals-o->_animals/4);
    }
    return this;
}

Prey* Lemming::attack(Wolf *w)
{
    this->incTurn();
    this->offspring(2,this->_animals);
    if(this->_animals>200) this->decAnimal(30);


    if(this->_animals>=4*w->_animals) {
        this->changeAnimal(-4*w->_animals);
    } else {
        w->decAnimal(w->_animals-w->_animals/4);
    }
    return this;
}




Hare* Hare::_instance=nullptr;
Hare* Hare::instance()
{
    if(_instance==nullptr) {
        //_instance = new Hare();
    }
    return _instance;
}

void Hare::destroy()
{
	if ( nullptr!=_instance )
	{
		delete _instance;
		_instance = nullptr;
	}
}

Prey* Hare::attack(Fox *f)
{
    this->incTurn();
    this->offspring(2,this->_animals/2);
    if(this->_animals>100) this->decAnimal(20);


    if(this->_animals>=2*f->_animals) {
        this->changeAnimal(-2*f->_animals);
    } else {
        f->decAnimal(f->_animals-f->_animals/4);
    }
    return this;
}

Prey* Hare::attack(Owl *o)
{
    this->incTurn();
    this->offspring(2,this->_animals/2);
    if(this->_animals>100) this->decAnimal(20);


    if(this->_animals>=2*o->_animals) {
        this->changeAnimal(-2*o->_animals);
    } else {
        o->decAnimal(o->_animals-o->_animals/4);
    }
    return this;
}

Prey* Hare::attack(Wolf *w)
{
    this->incTurn();
    this->offspring(2,this->_animals/2);
    if(this->_animals>100) this->decAnimal(20);


    if(this->_animals>=2*w->_animals) {
        this->changeAnimal(-2*w->_animals);
    } else {
        w->decAnimal(w->_animals-w->_animals/4);
    }
    return this;
}


//implementation of class Wolf

Gopher* Gopher::_instance=nullptr;
Gopher* Gopher::instance()
{
    if(_instance==nullptr) {
       // _instance = new Gopher();
    }
    return _instance;
}

void Gopher::destroy()
{
	if ( nullptr!=_instance )
	{
		delete _instance;
		_instance = nullptr;
	}
}


Prey* Gopher::attack(Fox *f)
{
    this->incTurn();
    this->offspring(4,this->_animals);
    if(this->_animals>200) this->decAnimal(40);


    if(this->_animals>=2*f->_animals) {
        this->changeAnimal(-2*f->_animals);
    } else {
        f->decAnimal(f->_animals-f->_animals/4);
    }
    return this;
}

Prey* Gopher::attack(Owl *o)
{
    this->incTurn();
    this->offspring(4,this->_animals);
    if(this->_animals>200) this->decAnimal(40);


    if(this->_animals>=2*o->_animals) {
        this->changeAnimal(-2*o->_animals);
    } else {
        o->decAnimal(o->_animals-o->_animals/4);
    }
    return this;
}

Prey* Gopher::attack(Wolf *w)
{
    this->incTurn();
    this->offspring(4,this->_animals);
    if(this->_animals>200) this->decAnimal(40);


    if(this->_animals>=2*w->_animals) {
        this->changeAnimal(-2*w->_animals);
    } else {
        w->decAnimal(w->_animals-w->_animals/4);
    }
    return this;
}

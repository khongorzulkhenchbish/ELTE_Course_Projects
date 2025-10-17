#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>
#include "colony.h"
#include "Predator.h"

using namespace std;



void create(const string &str, vector<Prey*> &preys, vector<Predator*> &preds)
{
    ifstream f(str);
    if(f.fail()) { cout << "Can't find file!\n"; exit(1);}

    //number of the preys and predators colony
    int n, m;
    f >> n >> m;

    for(int i=0; i<n+m; ++i ){
        char ch; string name; int number;
        f >> name >> ch >> number;
        switch(int(ch)){
            case int('l') : preys.push_back(new Lemming(name, 'l', number)); break;
            case int('h') : preys.push_back(new Hare(name, 'h', number)); break;
            case int('g') : preys.push_back(new Gopher(name, 'g', number));  break;
            case int('f') : preds.push_back(new Fox(name, 'f', number)); break;
            case int('w') : preds.push_back(new Wolf(name, 'w', number)); break;
            case int('o') : preds.push_back(new Owl(name, 'o', number));   break;
        }
    }
}

void random_attack(vector<Prey*> &preys, vector<Predator*> &preds)
{
    try{
        bool l = true;
        int round = 1;
        double initialsum = 0;
        for(unsigned int i=0; i<preds.size(); ++i, ++round) initialsum += preds[i]->_animals;

        while(l) {
            double loopsum = 0;
            bool below4 = true;
            for(unsigned int i=0; i<preds.size(); ++i, ++round) {
                const int range_from  = 0;
                const int range_to    = preys.size()-1;
                random_device                  rand_dev;
                mt19937                        generator(rand_dev());
                uniform_int_distribution<int>  distr(range_from, range_to);

                int randIndex = distr(generator);

                cout << round << "-th turn before attack:" << endl;
                cout << preds[i] << preys[randIndex];

                preds[i]->attack(preys[randIndex]);

                cout << round << "-th turn after attack:" << endl;
                cout << preds[i] << preys[randIndex];

                below4 = below4 && (preds[i]->_animals <= 4);
                loopsum += preds[i]->_animals;
            }
            l = l && !(2*initialsum==loopsum || below4);
        }
    }catch(exception e){
        cout << e.what() << endl;
    }
}


void destroy(vector<Prey*> &preys, vector<Predator*> &predators)
{
    preys.clear();
    predators.clear();
    /*for(int i=0; i<(int)preys.size(); ++i) delete preys[i];
    for(int i=0; i<(int)predators.size(); ++i) delete predators[i];*/
}
//#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    vector<Prey*> preys;
    vector<Predator*> preds;
    create("inp.txt", preys, preds );
    random_attack(preys, preds);

    destroy(preys, preds);
    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("second loop, length based test", "t1.txt")
{
    vector<Predator*> preds;
    vector<Prey*> preys;

    create("t4.txt", preys, preds);
    random_attack(preys, preds);
    CHECK(preds.size()==0);
    destroy(preys, preds);


    create("t1.txt", preys, preds);
    random_attack(preys, preds);
    CHECK(preds.size()==1);
    CHECK(preds[0]->name()=="feathery");
    destroy(preys, preds);


    create("t3.txt", preys, preds);
    random_attack(preys, preds);
    CHECK(preds.size()==4);
    CHECK(preds[0]->name()=="feathery");
    CHECK(preds[1]->name()=="hungry");
    CHECK(preds[2]->name()=="hungry");
    CHECK(preds[3]->name()=="arctic");
    destroy(preys, preds);
}

TEST_CASE("second loop, first and last predator satisfies or not", "t1.txt")
{
    vector<Predator*> preds;
    vector<Prey*> preys;

    create("t3.txt", preys, preds);
    random_attack(preys, preds);
    CHECK(preds[0]->_animals<4);
    destroy(preys, preds);


    create("t1.txt", preys, preds);
    random_attack(preys, preds);
    CHECK(preds[preds.size()-1]->_animals<4);
    destroy(preys, preds);
}


TEST_CASE("offspring", "t5.txt")
{
    vector<Predator*> preds;
    vector<Prey*> preys;

    create("t5.txt", preys, preds);
    preds[0]->attack(preys[0]);
    preds[0]->attack(preys[0]);
    CHECK(preys[0]->_animals==26);
    destroy(preys, preds);


    create("t5.txt", preys, preds);
    preds[0]->attack(preys[0]);
    preds[0]->attack(preys[0]);
    CHECK(preds[0]->_animals==1);
    preds[0]->attack(preys[0]);
    preds[0]->attack(preys[0]);
    CHECK(preds[0]->_animals==1);
    preds[0]->attack(preys[0]);
    preds[0]->attack(preys[0]);
    CHECK(preds[0]->_animals==1);
    preds[0]->attack(preys[0]);
    CHECK(preds[0]->_animals==1);
    preds[0]->attack(preys[0]);
    CHECK(preds[0]->_animals==1.25);
    destroy(preys, preds);

}

TEST_CASE("attack", "t5.txt")
{
    vector<Predator*> preds;
    vector<Prey*> preys;

    //arctic fox attacks lemming
    create("t5.txt", preys, preds);
    preds[0]->attack(preys[0]);
    CHECK(preys[0]->_animals==146);
    CHECK(preds[0]->_animals==1);
    destroy(preys, preds);

    //arctic fox attacks hare
    create("t6.txt", preys, preds);
    preds[0]->attack(preys[0]);
    CHECK(preys[0]->_animals==12);
    CHECK(preds[0]->_animals==6);
    destroy(preys, preds);

    //arctic fox attacks gopher
    create("t7.txt", preys, preds);
    preds[0]->attack(preys[0]);
    CHECK(preys[0]->_animals==26);
    CHECK(preds[0]->_animals==7);
    destroy(preys, preds);
}
#endif

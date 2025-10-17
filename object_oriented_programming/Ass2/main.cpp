#include <iostream>
#include "contest.h"
#include "angler.h"

using namespace std;

//First task
//Activity: Looking for an angler who has caught >= 3 (only catfishes)
//linear search
bool first_search(const string &filename, Contest &elem)
{
    ContestEnor t(filename);
    bool l = false;
    for(t.first(); !l && !t.end(); t.next()) {
        l = t.current().catfish >= 3 && t.current().otherfish == 0;
        elem = t.current();
    }
    return l;
}

//Second task
//Count number of contest where the angler got only and more than 3 catfish
//Summation
void second_search(const string &filename, Angler &elem, int &contestCounter)
{
    AnglerEnor t(filename);
    for(t.first(); !t.end(); t.next()) {
        if(t.current().skillful)
            elem = t.current(),
            contestCounter += 1;
    }
}

//#define NORMAL_MODE
#ifdef NORMAL_MODE


int main() {
    string fileName;
    cout << "Enter the name of the input file, please: ";
    cin >> fileName;

    //FIrst task
    cout << "First task\n";
    try
    {
        Contest e;
        if(first_search(fileName, e)) {
            cout << e.anglerName<<" has cought "<<e.catfish<<" catfish(es) only on contest "<<e.contestId<<"\n";
        } else {
            cout<<"There is no angler matching our search criteria.\n";
        }
    } catch(ContestEnor::FileError err)
    {
        cerr<<"Can't find input file "<<fileName<<"!\n";
    }

    //Second task
    cout << "Second task\n";
    try
    {
        Angler e;
        int contestCounter = 0;
        second_search(fileName, e, contestCounter);
        if(contestCounter)
            cout << contestCounter << "\n";
        else
            cout << "There is no contest matching our search criteria.\n";
    } catch(ContestEnor::FileError err)
    {
        cerr<<"Can't find input file "<<fileName<<"!\n";
    }
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"


//linear search first part

TEST_CASE("first, empty file", "t0.txt") {
    Contest e;
    CHECK_FALSE(first_search("t0.txt", e));
}

TEST_CASE("first, one angler", "t1.txt") {
    Contest e;
    CHECK(first_search("t1.txt", e));
    CHECK(e.anglerName=="Peter");
}

TEST_CASE("first, more anglers", "t6.txt") {
    Contest e;

    CHECK(first_search("t6.txt", e));
    CHECK(e.anglerName=="John");
}

TEST_CASE("first, first angler meets the requirement", "t4.txt") {
    Contest e;
    CHECK(first_search("t4.txt", e));
    CHECK((e.anglerName=="Peter" && e.contestId=="Kiliti0512"));
}

TEST_CASE("first, last angler meets the requirement", "t5.txt") {
    Contest e;
    CHECK(first_search("t5.txt", e));
    CHECK((e.anglerName=="Nick" && e.contestId=="ABC123"));
}

TEST_CASE("first, there is no such angler", "t3.txt") {
    Contest e;
    CHECK_FALSE(first_search("t3.txt", e));
}

TEST_CASE("first, there exist an angler who meet requirement", "t7.txt") {
    Contest e;
    CHECK(first_search("t7.txt", e));
    CHECK((e.anglerName=="John" && e.contestId=="Budapest123"));
}

TEST_CASE("first, more anglers meet the requirements", "t6.txt") {
    Contest e;
    CHECK(first_search("t6.txt", e));
    CHECK(e.anglerName=="John");
}

// counting first part

TEST_CASE("first, line without catches", "t0.txt") {
    ContestEnor t("t0.txt");
    t.first();
    CHECK((t.current().catfish == 0 && t.current().otherfish == 0));
}

TEST_CASE("first, one catch", "t5.txt") {
    ContestEnor t("t5.txt");
    t.first();
    CHECK((t.current().catfish == 1 || t.current().otherfish == 1));
}

TEST_CASE("first, more catch", "t6.txt") {
    ContestEnor t("t6.txt");
    t.first();
    CHECK((t.current().catfish > 0 || t.current().otherfish > 0));
}

TEST_CASE("first, the first contest has catfish", "t4.txt") {
    ContestEnor t("t4.txt");
    t.first();
    CHECK((t.current().catfish > 0));
}

TEST_CASE("first, the last contest has catfish", "t6.txt") {
    ContestEnor t("t6.txt");
    t.first();
    while(!t.end()) {
        t.next();
    }
    CHECK((t.current().catfish > 0));
}

TEST_CASE("first, line without catfish (could have otherfish)", "t3.txt") {
    ContestEnor t("t3.txt");
    t.first();
    CHECK((t.current().catfish == 0 || t.current().otherfish >= 0));
}

TEST_CASE("first, Line with 2 catfishes and 1 otherfish ~ wrong pattern", "t6.txt") {
    ContestEnor t("t6.txt");
    t.first();
    CHECK((t.current().catfish < 3 || t.current().otherfish > 0));
}

TEST_CASE("first, Line with only and more catfishes", "t4.txt") {
    ContestEnor t("t4.txt");
    t.first();
    CHECK((t.current().catfish >=3 && t.current().otherfish == 0));
}

// counting second part

TEST_CASE("second, file without contest", "t0.txt") {
    int counter = 0;
    Angler a;
    second_search("t0.txt", a, counter);
    CHECK(counter==0);
}

TEST_CASE("second, file with only 1 contest", "t1.txt") {
    int counter = 0;
    Angler a;
    second_search("t1.txt", a, counter);
    CHECK((counter==1 && a.contestId=="Kiliti0512")==true);
}

TEST_CASE("second, more contests", "t6.txt") {
    int counter = 0;
    Angler a;
    second_search("t6.txt", a, counter);
    CHECK(counter==3);
}

TEST_CASE("second, first contest meet criteria", "t4.txt") {
    int counter = 0;
    Angler a;
    second_search("t4.txt", a, counter);
    CHECK((counter==1 && a.contestId=="Kiliti0512")==true);
}

TEST_CASE("second, last contest meet criteria", "t5.txt") {
    int counter = 0;
    Angler a;
    second_search("t5.txt", a, counter);
    CHECK((counter==1 && a.contestId=="ABC123")==true);
}

TEST_CASE("second, all contest doesn't meet criteria", "t3.txt") {
    int counter = 0;
    Angler a;
    second_search("t3.txt", a, counter);
    CHECK(counter==0);
}

TEST_CASE("second, among contest one meet the criteria", "t7.txt") {
    int counter = 0;
    Angler a;
    second_search("t7.txt", a, counter);
    CHECK((counter==1 && a.contestId=="Budapest123")==true);
}

TEST_CASE("second, there are more contests meet criteria", "t6.txt") {
    int counter = 0;
    Angler a;
    second_search("t6.txt", a, counter);
    CHECK(counter==3);
}

// linear search second part

TEST_CASE("second, no angler", "t0.txt") {
    AnglerEnor t("t0.txt");
    t.first();
    CHECK_FALSE(t.current().skillful);
}

TEST_CASE("second, 1 angler 1 contest", "t1.txt") {
    AnglerEnor t("t1.txt");
    t.first();
    CHECK(t.current().skillful==true);
}

TEST_CASE("second, one contest with more angler", "t9.txt") {
    AnglerEnor t("t9.txt");
    t.first();
    CHECK(t.current().skillful);
}

TEST_CASE("second, first one is skillful angler", "t4.txt") {
    AnglerEnor t("t4.txt");
    t.first();
    CHECK(t.current().skillful);
}

TEST_CASE("second, last one is skillful angler", "t5.txt") {
    AnglerEnor t("t5.txt");
    t.first();
    while(!t.end()) {
        t.next();
    }
    CHECK(t.current().skillful);
}

TEST_CASE("second, no contest with such skillful angler", "t3.txt") {
    AnglerEnor t("t3.txt");
    t.first();
    while(!t.end()) {
        CHECK_FALSE(t.current().skillful);
        t.next();
    }
}

TEST_CASE("second, there exist angler among contest", "t7.txt") {
    AnglerEnor t("t7.txt");
    t.first(), t.next();
    CHECK(t.current().skillful);
}

TEST_CASE("second, there are more skillful anglers", "t6.txt") {
    AnglerEnor t("t6.txt");
    t.first();
    CHECK(t.current().skillful);
    t.next();
    CHECK(t.current().skillful);
    t.next();
    CHECK(t.current().skillful);
}

#endif // NORMAL_MODE2

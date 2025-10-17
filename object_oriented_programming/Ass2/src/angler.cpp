
#include "angler.h"

using namespace std;

//next()    method for the second task
//Task: 	Reading the next angler with his ability
//Input:    ContestEnor tt  - the enumerator of contests
//Output:   Angler _cur     - the next angler
//          bool _end       - the end of the enumeration
//Activity:

void AnglerEnor::next()
{
    if( !(_end = _tt.end()) ){
        _cur.contestId = _tt.current().contestId;
        _cur.skillful = false;
        for( ; !_tt.end() && _tt.current().contestId == _cur.contestId; _tt.next() ){
            _cur.skillful = _cur.skillful || (_tt.current().catfish >= 3 && _tt.current().otherfish == 0);
        }
    }
}

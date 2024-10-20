#include <iostream>
#include "StudentDataBase.h"
#include "StudentNode.h"

using namespace std;

class DataRetrievalTool
{
private:
    string next; // next name in the data base
    string prev; // prev name in the data base
    string data; // current grade in the data base

public:
    DataRetrievalTool(); // default constructor
    string getNext();    // gets next
    string getPrev();    // gets prev
    string getData();    // gets data

    // friend classes so they can access private variables.
    // Otherwise, they cant change the next and prev varaibles
    friend class StudentDataBase;
    friend class StudentNode;
};
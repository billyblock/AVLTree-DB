#pragma once
#include <iostream>
using namespace std;

// lets student data base use student nodes without defining them yet
class StudentNode;
class DataRetrievalTool;

class StudentDataBase
{
private:
    StudentNode *root;

    // searches for the node with aName
    StudentNode *nodeSearch(string aName);
    // adds a new node with the name (key) and grade
    void addStudent(string key, string grade);
    // removes the node with that name (key)
    void removeStudent(string key);
    // changes nodes name to key
    void changeGrade(string key, string grade);

public:
    StudentDataBase(); // default constructor

    DataRetrievalTool *search(string key);
    DataRetrievalTool *modify(string key, string data);

    // let the student node access the root
    friend class StudentNode;
    friend class DataRetrievalTool;
};
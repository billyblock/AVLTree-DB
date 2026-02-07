#include "StudentDataBase.h"
#include "StudentNode.h"
#include "DataRetrievalTool.h"

void printOutput();                         // prints output for user
void parseInput();                          // determines what the user wants to do
void lookUp(string name);                   // Looks up student's grade
void print();                               // prints the tree in order
void reversePrint();                        // reverse prints the tree
void addStudent(string name, string grade); // adds a new student or changes grade
void removeStudent(string name);            // removes a student
string getName();                           // reads name in from input when needed

// Creates a global scope data base for the whole main to use.
// To view this varialbe in the debugger, use the "watch" menu
// Add the variable SDB in the debugger's watch menu
StudentDataBase *SDB = new StudentDataBase();

int main()
{
    printOutput();
    // Loops infinitely until the user exits
    while (true)
    {
        parseInput();
        cout << endl;
    }

}

string getName()
{
    // grab last name
    string lastName = "";
    cin >> lastName;
    // grab first name
    string firstName;
    cin >> firstName;
    // combine first and last name
    string name = lastName + " " + firstName;
    return name;
}

void print()
{
    // grab the first and last thing to print in the data base
    DataRetrievalTool *drt = SDB->search("");
    do
    {
        // print out the name of the next student
        cout << drt->getNext() << " ";
        // get the next student
        drt = SDB->search(drt->getNext());
        // print the data of the next student
        cout << drt->getData() << endl;
    } while (drt->getNext() != "");
}

void reversePrint()
{
    // grab the first and last thing to print in the data base
    DataRetrievalTool *drt = SDB->search("");
    do
    {
        // print out the name of the prev student (next in reverse)
        cout << drt->getPrev() << " ";
        // get the prev student
        drt = SDB->search(drt->getPrev());
        // print the data of the prev student
        cout << drt->getData() << endl;
    } while (drt->getPrev() != "");
}

void lookUp(string name)
{
    // find the student, then grab that students grade
    string grade = SDB->search(name)->getData();
    if (grade == "")
    {
        cout << name << " not found." << endl;
    }
    else
    {
        cout << name << " has grade: " << grade << endl;
    }
}

// Input for adding student or changing their name must be done
// in the format "lastName, firstName grade" given in the assignment sheet and discussed in class
// Using input with "name grade" will NOT work and will give an error like the files of test input
// If you would like to use test input on this file, you must change the lines with getName() to the lines that are commented
void addStudent(string name, string grade)
{
    // always adds or changes the grade of the student, if the data of the
    // drt is empty, we added, otherwise we changed the grade
    if (SDB->modify(name, grade)->getData() == "")
    {
        cout << "Added " << name << " with grade: " << grade << endl;
    }
    else
    {
        cout << "Changed " << name << " grade to: " << grade << endl;
    }
}

void removeStudent(string name)
{
    // always tries to remove student, if the data is empty, we didnt remove anyone
    if (SDB->modify(name, "")->getData() == "")
    {
        cout << name << " Not found." << endl;
    }
    else
    {
        cout << "Removed: " << name << endl;
    }
}

void parseInput()
{
    string command, name;
    cin >> command;
    if (command == "PRINT" || command == "print")
    {
        print();
    }
    else if (command == "RPRINT" || command == "rprint")
    {
        reversePrint();
    }
    else if (command == "EXIT" || command == "exit" || command == "QUIT" || command == "quit")
    {
        exit(0);
    }
    else if (command == "LOOKUP" || command == "lookup")
    {
        //cin >> name;
        name = getName();
        lookUp(name);
    }
    else if (command == "REMOVE" || command == "remove")
    {
        //cin >> name;
        name = getName();
        removeStudent(name);
    }
    else if (command == "ADD" || command == "add")
    {
        name = getName();
        //cin >> name;
        // add is the only command that requires a grade
        string grade;
        cin >> grade;
        addStudent(name, grade);
    }
    else if (command == "HELP" || command == "help")
    {
        printOutput();
    }
    else
    {
        cout << "error: term " << command << " unknown. Please try again." << endl;
    }
}

void printOutput()
{
    cout << "What would you like to do?" << endl;
    cout << "Options: " << endl;
    cout << "ADD (last name, first name) (Student Grade)" << endl;
    cout << "PRINT" << endl;
    cout << "RPRINT" << endl;
    cout << "REMOVE (last name, first name)" << endl;
    cout << "LOOKUP (last name, first name)" << endl;
    cout << "EXIT" << endl
         << endl;
}

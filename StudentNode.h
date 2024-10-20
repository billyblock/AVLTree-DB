#pragma once
// Let the student node use student data base without actually defining it yet
class StudentDataBase;
class DataRetrievalTool;

class StudentNode
{
private:
	int height;
	StudentNode *leftChild;
	StudentNode *rightChild;
	StudentNode *parent;
	// also the "key"
	string name;
	// also the "data"
	string grade;
	// Use a pointer to the data base the node is in to access the root
	StudentDataBase *SDB;

	// Searches for the key, returns true if found, also modifies the drt
	bool search(string key, DataRetrievalTool *drt);
	// Recursive method to find a node with aName as the name
	StudentNode *nodeSearch(string aName);
	// Returns the farthest right node starting from the node it is called on
	StudentNode *getGreatest();
	// Returns the farthest left node starting from the node it is called on
	StudentNode *getLeast();
	// Adds a node to the smallest node
	void addToLeast(StudentNode *newNode);
	// Adds a node to the greatest node
	void addToGreatest(StudentNode *newNode);
	// recursively adds a new node
	void addStudent(string key, string data);
	// recursively removes a student
	void removeStudent(string key);
	// fixes the height of the node
	void correctHeight();
	// finds imbalances and fixes them with rotations
	void correctBalance();
	// finds if the node is not balanced. right heavy is negative
	int getBalance();
	// Rotates this node down left and its right child up
	void rightRotation();
	// Rotates this node down right and its left child up
	void leftRotation();
	// calls right rotate on right child then left rotate on this node
	void rightLeftRotation();
	// calls left rotate on left child then right rotate on this node
	void leftRightRotation();

public:
	// Basic constructor
	StudentNode();
	// constructor with initial values
	StudentNode(string aName, string aGrade, StudentDataBase *aSDB);

	// lets student data base access private methods
	friend class StudentDataBase;
	friend class DataRetrievalTool;
};
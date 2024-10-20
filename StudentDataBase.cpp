#include "StudentDataBase.h"
#include "StudentNode.h"
#include "DataRetrievalTool.h"

StudentNode *StudentDataBase::nodeSearch(string aName)
{
    // You will never reach this part if you dont have a root
    // because you cant change the grade of someone that doesnt exist
    return root->nodeSearch(aName);
}

void StudentDataBase::addStudent(string key, string data)
{
    // if the root exists, add the node to the root
    if (root)
    {
        root->addStudent(key, data);
    }
    // if the root doesnt exist, create one
    else
    {
        root = new StudentNode(key, data, this);
    }
}
void StudentDataBase::removeStudent(string key)
{
    // Check if root exists before removing
    if (root)
    {
        // if the root has any child, remove the node recursively starting fromt the root
        if (root->leftChild || root->rightChild)
        {
            root->removeStudent(key);
            root->correctHeight();
            root->correctBalance();
        }
        else // if the root doesnt have children, remove the root
        {
            // This if is not required because the main file covers it
            // But if I were to use this outside of the file it wouldn't work
            if (root->name == key)
            {
                delete root;
                root = nullptr;
            }
        }
    }
}
void StudentDataBase::changeGrade(string key, string data)
{
    // Find the node we are changing, change its grade
    StudentNode *temp = nodeSearch(key);
    temp->grade = data;
}

StudentDataBase::StudentDataBase()
{
    root = nullptr;
}

// Algorithm given in class
DataRetrievalTool *StudentDataBase::search(string key)
{
    DataRetrievalTool *drt = new DataRetrievalTool();
    if (key == "")
    {
        if (root)
        {
            drt->next = root->getLeast()->name;
            drt->prev = root->getGreatest()->name;
        }
        return drt;
    }
    if (root)
    {
        root->search(key, drt);
    }
    return drt;
}
// Algorithm given in class
DataRetrievalTool *StudentDataBase::modify(string key, string data)
{
    DataRetrievalTool *drt = search(key);
    if (key == "" || drt->getData() == "" && data == "")
    {
        return drt;
    }
    if (drt->getData() == "" && data != "")
    {
        addStudent(key, data);
    }
    else if (drt->getData() != "" && data == "")
    {
        removeStudent(key);
    }
    else if (drt->getData() != "" && data != "")
    {
        changeGrade(key, data);
    }
    return drt;
}
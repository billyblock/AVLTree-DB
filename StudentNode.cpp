#include "StudentDataBase.h"
#include "StudentNode.h"
#include "DataRetrievalTool.h"

StudentNode::StudentNode()
{
    name = "";
    grade = "";
    height = 1;
    parent = nullptr;
    leftChild = nullptr;
    rightChild = nullptr;
}
StudentNode::StudentNode(string aName, string aGrade, StudentDataBase *aSDB)
{
    name = aName;
    grade = aGrade;
    SDB = aSDB;
    height = 1;
    parent = nullptr;
    leftChild = nullptr;
    rightChild = nullptr;
}

void StudentNode::addToLeast(StudentNode *newNode)
{
    // find the furthest left node
    if (leftChild)
    {
        leftChild->addToLeast(newNode);
    }
    else // place the new one
    {
        leftChild = newNode;
        if (newNode)
        {
            newNode->parent = this;
        }
    }
    // Correct the tree
    correctHeight();
    correctBalance();
}

void StudentNode::addToGreatest(StudentNode *newNode)
{
    // find the furthest right node
    if (rightChild)
    {
        rightChild->addToGreatest(newNode);
    }
    else // place a new node
    {
        rightChild = newNode;
        if (newNode)
        {
            newNode->parent = this;
        }
    }
    // Correct the tree
    correctHeight();
    correctBalance();
}

void StudentNode::correctHeight()
{
    // if the children are null, their height is 0
    int leftChildHeight = 0;
    int rightChildHeight = 0;
    // new height is the bigger of the 2 children
    if (leftChild)
    {
        leftChildHeight = leftChild->height;
    }
    if (rightChild)
    {
        rightChildHeight = rightChild->height;
    }
    if (leftChildHeight > rightChildHeight)
    {
        height = leftChildHeight + 1;
    }
    else
    {
        height = rightChildHeight + 1;
    }
}

void StudentNode::correctBalance()
{
    int balance = getBalance();
    // Unbalanced on the left side
    if (balance > 1)
    {
        // If left child -> right child is heavier
        if (leftChild->getBalance() < 0)
        {
            leftRightRotation();
        }
        else
        {
            rightRotation();
        }
        return;
    }
    // Unbalanced on the right side
    if (balance < -1)
    {
        // If right child -> left child is heavier
        if (rightChild->getBalance() > 0)
        {
            rightLeftRotation();
        }
        else
        {
            leftRotation();
        }
    }
}

int StudentNode::getBalance()
{
    int leftChildHeight = 0;
    int rightChildHeight = 0;
    int difference = 0;
    if (leftChild)
    {
        leftChildHeight = leftChild->height;
    }
    if (rightChild)
    {
        rightChildHeight = rightChild->height;
    }
    difference = leftChildHeight - rightChildHeight;
    // If difference is negative, right child is heavier
    // If difference is positive, left child is heavier
    return difference;
}

void StudentNode::addStudent(string key, string data)
{
    if (key < name)
    {
        if (leftChild)
        {
            // If you're adding to the heavier child, increase your height
            if (rightChild)
            {
                if (leftChild->height >= rightChild->height)
                {
                    height++;
                }
            }
            else
            {
                height++;
            }
            leftChild->addStudent(key, data);
        }
        else
        {
            // once you find the spot to add the new node, add it
            StudentNode *node = new StudentNode(key, data, SDB);
            leftChild = node;
            node->parent = this;
        }
    }
    else if (key > name)
    {
        if (rightChild)
        {
            // If you're adding to the heavier child, increase your height
            if (leftChild)
            {
                if (rightChild->height >= leftChild->height)
                {
                    height++;
                }
            }
            else
            {
                height++;
            }
            rightChild->addStudent(key, data);
        }
        else
        {
            // once you find the spot to add the new node, add it
            StudentNode *node = new StudentNode(key, data, SDB);
            rightChild = node;
            node->parent = this;
        }
    }
    // Correct the tree
    correctHeight();
    correctBalance();
}

StudentNode *StudentNode::nodeSearch(string aName)
{
    if (aName < name)
    {
        if (leftChild)
        {
            return leftChild->nodeSearch(aName);
        }
    }
    if (aName > name)
    {
        if (rightChild)
        {
            return rightChild->nodeSearch(aName);
        }
    }
    return this;
}
void StudentNode::removeStudent(string key)
{
    if (key < name)
    {
        if (leftChild)
        {
            leftChild->removeStudent(key);
        }
    }
    else if (key > name)
    {
        if (rightChild)
        {
            rightChild->removeStudent(key);
        }
    }
    else // once you get here, you are the node you have to remove
    {
        // bring the left child up
        if (leftChild)
        {
            // pointer reassignment for removing
            if (parent)
            {
                if (parent->rightChild == this)
                {
                    parent->rightChild = leftChild;
                }
                else
                {
                    parent->leftChild = leftChild;
                }
            }
            else
            {
                SDB->root = leftChild;
            }
            leftChild->parent = parent;
            if (rightChild)
            {
                rightChild->parent = leftChild;
                StudentNode *temp = leftChild->rightChild;
                leftChild->rightChild = rightChild;
                rightChild->addToLeast(temp);
                temp = nullptr;
                leftChild->correctHeight();
                leftChild->correctBalance();
            }
        }
        // bring the right child up
        else if (rightChild)
        {
            // pointer reassignment for removing
            if (parent)
            {
                if (parent->rightChild == this)
                {
                    parent->rightChild = rightChild;
                }
                else
                {
                    parent->leftChild = rightChild;
                }
            }
            else
            {
                SDB->root = rightChild;
            }
            rightChild->parent = parent;
            if (leftChild)
            {
                leftChild->parent = rightChild;
                StudentNode *temp = rightChild->leftChild;
                rightChild->leftChild = leftChild;
                leftChild->addToGreatest(temp);
                temp = nullptr;
                rightChild->correctHeight();
                rightChild->correctBalance();
            }
        }
        else
        {
            // if this node didnt have any children
            if (parent)
            {
                if (parent->rightChild == this)
                {
                    parent->rightChild = nullptr;
                }
                else
                {
                    parent->leftChild = nullptr;
                }
            }
        }
        delete this;
        return;
    }
    // fix the tree
    correctHeight();
    correctBalance();
}

StudentNode *StudentNode::getGreatest()
{
    StudentNode *temp = this;
    while (temp->rightChild)
    {
        temp = temp->rightChild;
    }
    return temp;
}

StudentNode *StudentNode::getLeast()
{
    StudentNode *temp = this;
    while (temp->leftChild)
    {
        temp = temp->leftChild;
    }
    return temp;
}
bool StudentNode::search(string key, DataRetrievalTool *drt)
{
    if (key == name)
    {
        // the previous thing to me is my left childs furthest right child
        if (leftChild)
        {
            drt->prev = leftChild->getGreatest()->name;
        }
        else
        {
            // if i didnt have a left child, the previous would be my parent if im the right child
            if (parent)
            {
                if (parent->rightChild == this)
                {
                    drt->prev = parent->name;
                }
                else if (parent->parent)
                {
                    // Go up the tree and find the first right child
                    for (StudentNode *temp = parent; temp->parent; temp = temp->parent)
                    {
                        if (temp->parent->rightChild == temp)
                        {
                            drt->prev = temp->parent->name;
                            break;
                        }
                    }
                }
            }
        }
        drt->data = grade;
        // the next thing would be my right childs furthest left node
        if (rightChild)
        {
            drt->next = rightChild->getLeast()->name;
        }
        else
        {
            // if i didnt have a right child, then the next is my parent if im the left child
            if (parent)
            {
                if (parent->leftChild == this)
                {
                    drt->next = parent->name;
                }
                else if (parent->parent)
                {
                    // go up the tree and find the first left child
                    for (StudentNode *temp = parent; temp->parent; temp = temp->parent)
                    {
                        if (temp->parent->leftChild == temp)
                        {
                            drt->next = temp->parent->name;
                            break;
                        }
                    }
                }
            }
        }
        return true;
    }
    // search left side if its less than the current node
    if (key < name)
    {
        if (leftChild)
        {
            return leftChild->search(key, drt);
        }
        else
        {
            drt->prev = name;
            return false;
        }
    }
    // search right side if its greater than the current node
    if (key > name)
    {
        if (rightChild)
        {
            return rightChild->search(key, drt);
        }
        else
        {
            drt->prev = name;
            return false;
        }
    }
    return false;
}

void StudentNode::rightRotation()
{
    // pointer reassignments for right rotating
    StudentNode *temp = leftChild;
    if (!parent)
    {
        SDB->root = leftChild;
    }
    else
    {
        if (parent->rightChild)
        {
            if (parent->rightChild == this)
            {
                parent->rightChild = temp;
            }
        }
        if (parent->leftChild)
        {
            if (parent->leftChild == this)
            {
                parent->leftChild = temp;
            }
        }
    }
    temp->parent = parent;
    parent = temp;
    leftChild = temp->rightChild;

    if (leftChild)
    {
        leftChild->parent = this;
    }

    temp->rightChild = this;
    correctHeight();
    temp->correctHeight();
}

void StudentNode::leftRotation()
{
    // pointer reassignments for left rotating
    StudentNode *temp = rightChild;
    if (!parent)
    {
        SDB->root = rightChild;
    }
    else
    {
        if (parent->rightChild)
        {
            if (parent->rightChild == this)
            {
                parent->rightChild = temp;
            }
        }
        if (parent->leftChild)
        {
            if (parent->leftChild == this)
            {
                parent->leftChild = temp;
            }
        }
    }
    temp->parent = parent;
    parent = temp;
    rightChild = temp->leftChild;

    if (rightChild)
    {
        rightChild->parent = this;
    }
    temp->leftChild = this;
    correctHeight();
    temp->correctHeight();
}
void StudentNode::rightLeftRotation()
{
    rightChild->rightRotation();
    leftRotation();
}
void StudentNode::leftRightRotation()
{
    leftChild->leftRotation();
    rightRotation();
}
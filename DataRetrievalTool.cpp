#include "DataRetrievalTool.h"

DataRetrievalTool::DataRetrievalTool()
{
    data = "";
    next = "";
    prev = "";
}

string DataRetrievalTool::getNext()
{
    return next;
}
string DataRetrievalTool::getPrev()
{
    return prev;
}
string DataRetrievalTool::getData()
{
    return data;
}

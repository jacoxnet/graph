// Edge matrix
#include <iostream>
using namespace std;
#include <vector>
#include <list>
using namespace std;
#include "matrix.h"

// Default constructor 
Matrix::Matrix()
{
}

Matrix::~Matrix()
{
}

void Matrix::resize(int size)
{
    graph.resize(size, vector<int> (size));

    // set all to NOEDGE
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            graph[i][j] = NOEDGE;
        }
    }
}

void Matrix::setedge(int x, int y)
{
    // since this is a nondirectional graph, x should always be <= y
    if (x > y)
    {
        swap(x, y);
    }
    graph[x][y] = EDGE;
}    

void Matrix::clearedge(int x, int y)
{
    if (x > y)
    {
        swap(x, y);
    }
    graph[x][y] = NOEDGE;
}

bool Matrix::isedge(int x, int y)
{
    if (x > y)
    {
        swap(x, y);
    }
    if (graph[x][y] == NOEDGE) 
    {
        return false;
    }
    else 
    {
        return true;
    }
}  

void Matrix::setlength(int x, int y, int d)
{
    if (x > y)
    {
        swap(x, y);
    }
    graph[x][y] = d;
}

int Matrix::getlength(int x, int y)
{
    if (x > y)
    {
        swap(x, y);
    }
    return graph[x][y];
}

list<int> Matrix::neighbors(int x)
{
    list<int> n;
    n.clear();
    for (int i = 0; i < graph.size(); i++)
    {
        if ((i != x) && isedge(i, x))
        {
            n.push_front(i);
        }
    }
    return n;
}

void Matrix::display()
{
    for (vector<int> x : graph)
    {
        for (int y : x)
        {
            cout << y << " ";
        }
        cout << endl;
    }
}

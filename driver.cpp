#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

#include "matrix.h"
/* #include "vertexlist.h" */

int main()
{
    const int SIZE = 20;
    const float DENSITY = 0.1;
    // LOWLENGTH and HILENGTH are the range of distances of edges
    const int LOWLENGTH = 2;
    const int HILENGTH = 10;
    const int INFINITE = SIZE + HILENGTH + 1;
    const int SOURCE = 0;
    srand(time(NULL));
    Matrix m;
    list<int> Q;    // holds vertices that haven't been analyzed
    list<int> R;    // holds vertices after analysis
    list<int> n;    // receives list of neighbors from matrix
    int dist[SIZE], prev[SIZE]; // holds sought-after values 
                                // - distance and parent vertex
    
    // set proper size of matrix
    m.resize(SIZE);

    // assign an edge based on probability density
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            // always an "edge" and 0 distance from x to x
            if (i == j)
            {
                m.Matrix::setedge(i, j);
                m.Matrix::setlength(i, j, 0);
            }
            // else assign an edge based on density probability
            else if ((rand() % 1000) < (DENSITY * 1000))
            {
                m.Matrix::setedge(i, j);
                int length = rand() % (HILENGTH - LOWLENGTH) + LOWLENGTH;
                m.Matrix::setlength(i, j, length);
            }
            else
            {
                m.Matrix::clearedge(i, j);
            }
        }
    }
 
    // start Dijkstra function

    // add all vertices to Q
    for (int i = 0; i < SIZE; i++)
    {
        Q.push_back(i);
        dist[i] = INFINITE;     // 
        prev[i] = INFINITE;
    }
    dist[SOURCE] = 0;

    while (!Q.empty())
    {
        // get element in Q with smallest dist[]
        int u = Q.front();
        for (list<int>::iterator it = next(Q.begin(), 1); it != Q.end(); ++it)
        {
            if (dist[*it] < dist[u])
            {
                u = *it;
            }
        }
        // erase the vertex with that index from Q
        Q.remove(u);
        // now iterate through neighbors of index
        n = m.neighbors(u);
        // pv iterates through neighbors
        for (list<int>::iterator pv = n.begin(); pv != n.end(); ++pv)
        {
            // only do this for nodes still in Q
            if (count(Q.begin(), Q.end(), *pv) != 0)
            {
                int alt = dist[u] + m.getlength(u, *pv);
                if (alt < dist[*pv])
                {
                    dist[*pv] = alt;
                    prev[*pv] = u;
                }
            }
        }
    }

    cout << "matrix:" << endl;
    m.display();
    for (int i = 1; i < SIZE; i++)
    {
        if (dist[i] == INFINITE)
        {
            cout << "no path from vertex " << i << " back to source" << endl;
        }
        else
        {
            cout << "path from vertex: " << i << " back to source, distance "<< dist[i] << endl;
            int j = i;
            do 
            {
                cout << "   node " << j << " to node " << prev[j] 
                    << " length " << m.getlength(j, prev[j]) << endl;
                j = prev[j];
            }
            while (j != SOURCE);
        }
    }
}
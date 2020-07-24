// Edge matrix
#include <vector>
#include <list>
using namespace std;

class Matrix
{
    private:
        vector<vector<int>> graph;
        const int EDGE = 1;
        const int NOEDGE = -1;
        
    public:
        Matrix();
        ~Matrix();
        void resize(int size);
        void setedge(int x, int y);
        void clearedge(int x, int y);
        bool isedge(int x, int y);
        void setlength(int x, int y, int d);
        int getlength(int x, int y);
        void display();
        list<int> neighbors(int x);
};
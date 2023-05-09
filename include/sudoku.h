#include "../lib/node.cpp"

class Sudoku
{
private:
    int format[9][9];
    Node matrix[9][9];
    Node temp[9][9];

    long int BackTrackCounter = 0;

public:
    Sudoku();
    ~Sudoku();
    void input();
    void output();
    void init();
    void LCV();
    void MRV(int *, int *);
    bool Solve();
    bool CommonArea(int, int, int, int);
    void Constraint();
    bool ForwardChecking();
    void MaxDegree(int *, int *);
    bool isfinished();
    void Print(int, int);
    bool isSafe(int, int, int);
    friend class node;
};

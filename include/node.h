class Node
{
private:
    int value;
    int list[10];
    bool fixed;

public:
    Node()
    {
    }
    ~Node()
    {
    }
    friend class Sudoku;
};

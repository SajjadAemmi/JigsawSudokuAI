class Node
{
public:
    Node();
    ~Node();
    friend class Sudoku;

private:
    int value;
    int list[10];
    bool fixed;
};
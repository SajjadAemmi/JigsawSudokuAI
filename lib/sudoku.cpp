#include <iostream>
#include <limits.h>
#include <fstream>
#include "../include/sudoku.h"

using namespace std;

Sudoku::Sudoku()
{
}

Sudoku::~Sudoku()
{
}

void Sudoku::input()
{
    fstream f;

    f.open("io/input/input.txt", ios::in);

    if (!f)
    {
        cout << "no file available\n";
        system("pause");
        exit(0);
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            f >> matrix[i][j].value;
        }
    }
    f.close();

    f.open("io/input/format.txt", ios::in);

    if (!f)
    {
        cout << "no file available\n";
        system("pause");
        exit(0);
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            f >> format[i][j];
        }
    }
    f.close();

    init();
}

void Sudoku::output()
{
    fstream f;

    f.open("io/output/solution.txt", ios::out);

    if (!f)
    {
        cout << "no file available\n";
        system("pause");
        exit(0);
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            f << matrix[i][j].value << " ";
        }
        f << "\n";
    }
    f.close();
}

void Sudoku::init()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (matrix[i][j].value == 0)
                matrix[i][j].fixed = false;
            else
                matrix[i][j].fixed = true;
        }
    }
}

void Sudoku::MRV(int *Row, int *Col)
{
    Constraint();
    int min = INT_MAX;
    int cntr;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (matrix[i][j].value == 0)
            {
                cntr = 0;
                for (int l = 1; l <= 9; l++)
                {
                    if (matrix[i][j].list[l] == 1)
                        cntr++;
                }
                if (cntr <= min)
                {
                    min = cntr;
                    *Row = i;
                    *Col = j;
                }
            }
        }
    }
}

void Sudoku::LCV()
{
}

void Sudoku::Constraint()
{

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (matrix[i][j].value == 0)
            {
                for (int l = 1; l <= 9; l++)
                {
                    matrix[i][j].list[l] = 1;
                }

                for (int l = 1; l <= 9; l++)
                {
                    for (int k = 0; k < 9; k++)
                    {
                        if (matrix[i][k].value == l && k != j)
                        {
                            matrix[i][j].list[l] = 0;
                        }
                        if (matrix[k][j].value == l && k != i)
                        {
                            matrix[i][j].list[l] = 0;
                        }
                    }
                    for (int k = 0; k < 9; k++)
                    {
                        for (int m = 0; m < 9; m++)
                        {
                            if (format[i][j] == format[k][m] && matrix[k][m].value == l && k != i && m != j)
                            {
                                matrix[i][j].list[l] = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}

bool Sudoku::ForwardChecking()
{
    Constraint();
    bool sw;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (matrix[i][j].value == 0)
            {
                sw = false;

                for (int l = 1; l <= 9; l++)
                {
                    if (matrix[i][j].list[l] == 1)
                    {
                        sw = true;
                        break;
                    }
                }
                if (sw == false)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void Sudoku::MaxDegree(int *Row, int *Col)
{
    // int max = 0;
    int max = INT_MIN;
    int cntr;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cntr = 0;
            if (matrix[i][j].value == 0)
            {
                for (int k = 0; k < 9; k++)
                {
                    if (matrix[i][k].value == 0 && k != j)
                    {
                        cntr++;
                    }
                    if (matrix[k][j].value == 0 && k != i)
                    {
                        cntr++;
                    }
                }
                for (int k = 0; k < 9; k++)
                {
                    for (int m = 0; m < 9; m++)
                    {
                        if (matrix[k][m].value == 0 && k != i && m != j && format[i][j] == format[k][m])
                        {
                            cntr++;
                        }
                    }
                }
                if (cntr >= max)
                {
                    max = cntr;
                    *Row = i;
                    *Col = j;
                }
            }
        }
    }
}

bool Sudoku::isfinished()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (matrix[i][j].value == 0)
                return false;

    return true;
}

bool Sudoku::Solve()
{
    if (isfinished())
        return true;

    int Row, Col;

    // MaxDegree(&Row, &Col);
    MRV(&Row, &Col);

    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(Row, Col, num))
        {
            matrix[Row][Col].value = num;

            Print(Row, Col);

            // if (ForwardChecking())
            //{
            if (Solve())
                return true;
            //}
            matrix[Row][Col].value = 0;

            Print(Row, Col);
        }
    }
    BackTrackCounter++;

    return false;
}

bool Sudoku::isSafe(int Row, int Col, int num)
{
    for (int i = 0; i < 9; i++)
        if (matrix[Row][i].value == num)
            return false;

    for (int i = 0; i < 9; i++)
        if (matrix[i][Col].value == num)
            return false;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (matrix[i][j].value == num && format[i][j] == format[Row][Col])
                return false;

    return true;
}

void Sudoku::Print(int Row, int Col)
{
    // Sleep(100);
    system("clear");

    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
        {
            cout << "_ _ _ _ _ _ _ _ _ _ _ _ _" << endl
                 << endl;
        }

        for (int j = 0; j < 9; j++)
        {
            // Color(14);

            if (j % 3 == 0)
            {
                cout << "| ";
            }

            // if (matrix[i][j].fixed == true)
            // 	Color(11);
            // else if (i == Row && j == Col)
            // 	Color(10);
            // else
            // 	Color(15);

            if (matrix[i][j].value == 0)
                cout << "_";
            else
                cout << matrix[i][j].value;

            cout << " ";
        }
        // Color(14);
        cout << "| ";

        if (i % 3 == 2)
            cout << endl;
        else
            cout << endl
                 << endl;
    }
    cout << "_ _ _ _ _ _ _ _ _ _ _ _ _";
    cout << "\n"
         << "BackTrack Counter: " << BackTrackCounter << endl;
}

#include <iostream>
#include <ctime>
#include "include/sudoku.h"

using namespace std;

// void Color(int number)
// {
// 	HANDLE Color;
// 	Color = GetStdHandle(STD_OUTPUT_HANDLE);
// 	SetConsoleTextAttribute(Color, number);
// }

int main()
{
	Sudoku sudoku;

	sudoku.input();

	clock_t start_time, end_time, exe_time;
	start_time = clock();

	if (sudoku.Solve() == true)
	{
		sudoku.Print(9, 9);
		sudoku.output();
	}
	else
		cout << "No solution exists" << endl;

	end_time = clock();
	exe_time = end_time - start_time;
	float t = ((float)exe_time) / CLOCKS_PER_SEC;

	cout << "\nexecution time: " << t << "\n";
	system("pause");
	return 0;
}

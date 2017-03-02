#include "SudokuPuzzle.h"
#include <Windows.h>


SudokuPuzzle::SudokuPuzzle(void) 
{
}

SudokuPuzzle::~SudokuPuzzle(void)
{
}

void SudokuPuzzle::Solve(char filenameIn[])
{
	// You will need to read the values of the Sudoku puzzle into your data structure
	LARGE_INTEGER start, end, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	// Solve the puzzle

	QueryPerformanceCounter(&end);
	float time = (end.QuadPart - start.QuadPart) / (static_cast<float> (frequency.QuadPart));

	Output();  // Output the solved puzzle
}

// This is an example of how you may output the solved puzzle
void SudokuPuzzle::Output() const
{
	ofstream fout("sudoku_solution.txt"); // DO NOT CHANGE THE NAME OF THIS FILE
	if(fout.is_open())
	{
		for(int y = 0; y < 9; ++y)
		{
			for(int x = 0; x < 9; ++x)
			{
				// output each grid value followed by " "
			}

			fout << endl;
		}
		fout.close();
	}
}

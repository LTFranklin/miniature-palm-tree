#pragma once

#include <iostream>
#include <fstream>
using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle(void);
	~SudokuPuzzle(void);

	void Solve(char filenameIn[]);

private:
	void Output() const;
};


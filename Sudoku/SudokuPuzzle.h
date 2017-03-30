#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "Cell.h"
#include "CellGroup.h"
#include "PuzzleGrid.h"

using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle(void);
	~SudokuPuzzle(void);

	void Solve(char filenameIn[]);




private:
	void Output(PuzzleGrid grid) const;
	void PrintGrid(PuzzleGrid grid) const;
	//should probably rename. Does the bulk of the solving (consider splitting into naked and hidden?)
	bool Work(CellGroup group);
	void CreateGrids(const char filenameIn[]);
	inline bool NakedSingles(CellGroup group);
	inline bool HiddenSingles(CellGroup group);

	PuzzleGrid rowGrid;
	PuzzleGrid columnGrid;
	PuzzleGrid blockGrid;
};


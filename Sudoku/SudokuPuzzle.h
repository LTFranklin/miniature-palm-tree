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
	void CreateGrids();
	//should probably rename. Does the bulk of the solving
	bool Work(CellGroup group);

private:
	void Output(PuzzleGrid grid) const;
	void PrintGrid(PuzzleGrid grid) const;

	PuzzleGrid rowGrid;
	PuzzleGrid columnGrid;
	PuzzleGrid blockGrid;
};


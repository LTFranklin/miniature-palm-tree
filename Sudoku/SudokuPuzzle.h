#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "Cell.h"
#include "CellGroup.h"

using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle(void);
	~SudokuPuzzle(void);

	void Solve(char filenameIn[]);




private:
	void Output() const;
	void PrintGrid(CellGroup row) const;
	//should probably rename. Does the bulk of the solving (consider splitting into naked and hidden?)
	inline bool Work(CellGroup activeGroup);
	inline void CreateGrids(const char filenameIn[]);
	inline bool NakedSingles(CellGroup activeGroup, vector<int> values);
	inline bool HiddenSingles(CellGroup activeGroup);
	inline bool NarrowOptions(CellGroup activeGroup, vector<int> values);

	CellGroup rowGrid[9];
	CellGroup columnGrid[9];
	CellGroup blockGrid[9];
};


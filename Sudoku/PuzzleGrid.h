#pragma once
#include "CellGroup.h"
#include "Cell.h"

class PuzzleGrid
{
public:
	PuzzleGrid();
	~PuzzleGrid();
	//Is this the best way?
	int GetCellGroupValues(const int groupPos, const int cellPos);
	void EditValue(const int groupPos, const int cellPos, const int inVal);
	Cell* GetCellRef(const int groupPos, const int cellPos);
	void SetRef(const int groupPos, const int cellPos, Cell* ref);
	CellGroup GetCellGroup(const int pos);

private:
	//9 CellGroups together to form the board
	CellGroup grid[9];
};


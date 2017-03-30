#include "PuzzleGrid.h"


PuzzleGrid::PuzzleGrid()
{
	for (int i = 0; i < 9; ++i)
	{
		CellGroup madeGroup;
		grid[i] = madeGroup;
	}
}

PuzzleGrid::~PuzzleGrid()
{
	
}

CellGroup PuzzleGrid::GetCellGroup(const int pos) const
{
	return grid[pos];
}

int PuzzleGrid::GetCellGroupValues(const int groupPos, const int cellPos) const
{
	return grid[groupPos].GetCellValue(cellPos);
}

void PuzzleGrid::EditValue(const int groupPos, const int cellPos, const int inVal)
{
	grid[groupPos].EditValue(inVal, cellPos);
}

Cell* PuzzleGrid::GetCellRef(const int groupPos, const int cellPos) const
{
	return grid[groupPos].GetCellRef(cellPos);
}

void PuzzleGrid::SetRef(const int groupPos, const int cellPos, Cell* ref)
{
	grid[groupPos].SetRef(cellPos, ref);
}
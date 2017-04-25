#pragma once
#include "Cell.h"

class CellGroup
{
public:
	//or this
	CellGroup();
	~CellGroup();
	int GetCellValue(const int pos) const;
	void EditValue(const int pos, const int inVal);
	Cell *GetCellRef(const int pos) const;
	void SetRef(const int pos, Cell* ref);
	void RemoveOption(const int pos, const int inVal);
	bool GetGiven(const int pos) const;
	int GetOptions(const int gPos, const int oPos) const;
	int GetOptionNum(const int pos) const;

	Cell* GetGroup();


private:
	Cell *group[9];
};


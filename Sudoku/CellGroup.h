#pragma once
#include "Cell.h"

class CellGroup
{
public:
	//or this
	CellGroup();
	~CellGroup();
	int GetCellValue(const int pos) const;
	void EditValue(const int inVal, const int pos);
	Cell* GetCellRef(const int pos) const;
	void SetRef(const int pos, Cell* ref);
	void RemoveOption(const int pos, const int inVal);
	bool GetGiven(const int pos) const;
	vector<int> GetOptions(const int pos) const;

private:
	Cell* group[9];
};


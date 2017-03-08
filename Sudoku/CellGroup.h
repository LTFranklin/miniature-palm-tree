#pragma once
#include "Cell.h"

class CellGroup
{
public:
	//or this
	CellGroup();
	~CellGroup();
	int GetCellValue(const int pos);
	void EditValue(const int inVal, const int pos);
	Cell* GetCellRef(const int pos);
	void SetRef(const int pos, Cell* ref);
	void RemoveOption(const int pos, const int inVal);
	bool GetGiven(const int pos);
	vector<int> GetOptions(const int pos);

private:
	Cell* group[9];
};


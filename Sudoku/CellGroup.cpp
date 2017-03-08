#include "CellGroup.h"

CellGroup::CellGroup()
{
	for (int i = 0; i < 9; ++i)
	{
		Cell* madeCell = new Cell;
		group[i] = madeCell;
	}
}

CellGroup::~CellGroup()
{
}

//look at removing needing the pos parameter if possible
int CellGroup::GetCellValue(const int pos)
{
	return group[pos]->GetValue();
}

void CellGroup::EditValue(const int inVal, const int pos)
{
	group[pos]->SetValue(inVal);
}

Cell* CellGroup::GetCellRef(const int pos)
{
	return group[pos];
}

void CellGroup::SetRef(const int pos, Cell* ref)
{
	group[pos] = ref;

}

void CellGroup::RemoveOption(const int pos, const int inVal)
{
	group[pos]->RemoveOption(inVal);
}

bool CellGroup::GetGiven(const int pos)
{
	return group[pos]->GetGiven();
}

vector<int> CellGroup::GetOptions(const int pos)
{
	return group[pos]->GetOptions();
}
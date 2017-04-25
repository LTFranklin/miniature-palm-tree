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
int CellGroup::GetCellValue(const int pos) const
{
	return group[pos]->GetValue();
}

void CellGroup::EditValue(const int pos, const int inVal)
{
	group[pos]->SetValue(inVal);
}

Cell* CellGroup::GetCellRef(const int pos) const
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

bool CellGroup::GetGiven(const int pos) const
{
	return group[pos]->GetGiven();
}

int CellGroup::GetOptions(const int gPos, const int oPos) const
{
	return group[gPos]->GetOptions(oPos);
}

int CellGroup::GetOptionNum(const int pos) const
{
	return group[pos]->GetOptionNum();
}

Cell* CellGroup::GetGroup()
{
	return group[0];
}
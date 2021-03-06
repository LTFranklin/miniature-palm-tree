#include "SudokuPuzzle.h"
#include <Windows.h>



SudokuPuzzle::SudokuPuzzle(void) 
{

}

SudokuPuzzle::~SudokuPuzzle(void)
{
}

void SudokuPuzzle::Solve(char filenameIn[])
{
	// You will need to read the values of the Sudoku puzzle into your data structure
	LARGE_INTEGER start, end, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	CreateGrids(filenameIn);

	//used to check if changes have been made
	bool rChange,cChange,bChange = true;
	int counter = 0;
	//loops while changes have been made. If a loop occurs with no changes, nothing further can be done
	do
	{
		for (int i = 0; i < 9; ++i)
		{
			rChange = Work(rowGrid[i]);
		}
		for (int i = 0; i < 9; ++i)
		{
			cChange = Work(columnGrid[i]);
		}
		for (int i = 0; i < 9; ++i)
		{
			bChange = Work(blockGrid[i]);
		}
		++counter;
	} while (rChange || cChange || bChange);
	 
	QueryPerformanceCounter(&end);    
	float time = (end.QuadPart - start.QuadPart) / (static_cast<float> (frequency.QuadPart));

	for (int i = 0; i < 9; ++i)
	{
		PrintGrid(rowGrid[i]);
	}
	Output();
	cout << time << "\n" << counter;
}

//comment out before submission
void SudokuPuzzle::CreateGrids(const char filenameIn[])
{
	//stream reader to read in values from the file
	ifstream streamReader(filenameIn);
	//two integer values to apply the row and column references to the blocks
	int x = 0;
	int y = 0;
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			//creates a base cell with a zero value
			Cell* madeCell = new Cell;
			//and sets the reference in their respective positions within the row and column grids 
			rowGrid[i].SetRef(j, madeCell);
			columnGrid[j].SetRef(i, madeCell);

			//every 3 values belong in different rows
			x = i / 3 + ((j/3) * 3);

			blockGrid[x].SetRef(y, madeCell);
			y++;
			//this resets the y values when it reaches the end of a row of grids
			if (y == 9 && x == 6 || y == 9 && x == 7)
			{
				y = 0;
			}
			//this reduces y by three if every 3 lines to ensure they are placed in the correct position
			if (y == 3 && x < 6 || y == 6 && x < 6 || y == 9)
			{
				y -= 3;
			}

			//reads the value into the int 
			int val;
			streamReader >> val;
			//which is used to apply it to the rowgrid grid
			rowGrid[i].EditValue(j, val);
			//as they all share the same references it isnt required read it into every grid

		}
	}
}

bool SudokuPuzzle::Work(CellGroup activeGroup)
{
	//create a vector containing all the known values in the group
	vector<int> values;
	int val;
	for (int i = 0; i < 9; ++i)
	{
		//use an int?
		val = activeGroup.GetCellValue(i);
		if (val != 0)
		{
			values.push_back(val);
		}
	}
	//if there is 9 values, the gorup is solved so there is no need to do anything
	if (values.size() == 9)
	{
		//cleaning up?
		values.clear();
		return false;
	}
	//Call naked and hidden singles, if changes and retrun true or false depending if changes have been made
	if (NarrowOptions(activeGroup, values) || NakedSingles(activeGroup, values) || HiddenSingles(activeGroup))
	{
		return true;
	}
	return false;
}

bool SudokuPuzzle::NarrowOptions(CellGroup activeGroup, vector<int> values)
{
	bool changes = false;
	//for every value in the group
	for (int i = 0; i < 9; ++i)
	{
		//do nothing if it is given
		if (activeGroup.GetGiven(i))
		{
			continue;
		}
		vector<int> v;
		for (int k = 0; k < activeGroup.GetOptionNum(i); ++k)
		{
			v.push_back(activeGroup.GetOptions(i, k));
		}
		//and remove all the known values form the cells possibilities
		for (int j = 0; j < values.size(); ++j)
		{
			if (std::find(v.begin(),v.end(), values[j]) != v.end())
			{
				activeGroup.RemoveOption(i, values[j]);
				changes = true;
			}
		}
		v.clear();
	}
	return changes;
}

bool SudokuPuzzle::NakedSingles(CellGroup activeGroup, vector<int> values)
{
	bool changesMade = false;
	for (int i = 0; i < 9; ++i)
	{
		//if there is only one option, assign it as the value and state a change has been made
		if (activeGroup.GetOptionNum(i) == 1)
		{
			activeGroup.EditValue(i, activeGroup.GetOptions(i, 0));
			values.push_back(activeGroup.GetCellValue(i));
			changesMade = true;
		}
	}
	return changesMade;
}

bool SudokuPuzzle::HiddenSingles(CellGroup activeGroup)
{
	bool changesMade = false;
	//for each group member
	for (int i = 0; i < 9; ++i)
	{
		//if it hasnt been solved
		if (activeGroup.GetCellValue(i) == 0)
		{
			vector <int> possibilities;
			//for each other group member
			for (int j = 0; j < 9; ++j)
			{
				if (i != j)
				{
					//for every option
					
					for (int k = 0; k < activeGroup.GetOptionNum(j); ++k)
					{
						//if the option isnt already known
						if (possibilities.capacity() == 0 || std::find(possibilities.begin(), possibilities.end(), activeGroup.GetOptions(j, k)) == possibilities.end())
						{
							//add it to the list
							possibilities.push_back(activeGroup.GetOptions(j, k));
						}
					}
				}
				else
				{
					continue;
				}
			}
			//for every option
			for (int j = 0; j < activeGroup.GetOptionNum(i); ++j)
			{
				//if that value isnt an option for another square
				if ((std::find(possibilities.begin(), possibilities.end(), activeGroup.GetOptions(i, j)) == possibilities.end()))
				{
					//set that option as the cells value
					activeGroup.EditValue(i, activeGroup.GetOptions(i, j));
					changesMade = true;
					continue;
				}
			}
			possibilities.clear();
		}
	}
	return changesMade;
}

//remove before submission
void SudokuPuzzle::PrintGrid(CellGroup row) const
{
	//used for testing purposes
	for (int i = 0; i < 9; ++i)
	{
		cout << " " << row.GetCellValue(i) << " ";
	}
	cout << "\n" << "\n";

}

// This is an example of how you may output the solved puzzle
void SudokuPuzzle::Output() const
{
	ofstream fout("sudoku_solution.txt"); // DO NOT CHANGE THE NAME OF THIS FILE
	if(fout.is_open())
	{
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				fout << rowGrid[i].GetCellValue(j) << " ";
			}
			fout << "\n";
		}

	}
	fout.close();
}

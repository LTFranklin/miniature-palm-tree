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
	CreateGrids();

	//used to check if changes have been made
	bool rChange,cChange,bChange = true;
	//loops while changes have been made. If a loop occurs with no changes, nothing further can be done
	do
	{
		for (int i = 0; i < 9; ++i)
		{
			rChange = Work(rowGrid.GetCellGroup(i));
		}
		for (int i = 0; i < 9; ++i)
		{
			cChange = Work(columnGrid.GetCellGroup(i));
		}
		for (int i = 0; i < 9; ++i)
		{
			bChange = Work(blockGrid.GetCellGroup(i));
		}
	} while (rChange || cChange || bChange);

	PrintGrid(rowGrid);
	cout << "\n";

	QueryPerformanceCounter(&end);
	float time = (end.QuadPart - start.QuadPart) / (static_cast<float> (frequency.QuadPart));

	Output(rowGrid);  // Output the solved puzzle
}


 void SudokuPuzzle::CreateGrids()
{
	//stream reader to read in values from the file
	ifstream streamReader("sudoku_puzzle.txt");
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
			rowGrid.SetRef(i, j, madeCell);
			columnGrid.SetRef(j, i, madeCell);


			//every 3 values belong in different rows in both directions. variable i is used to set the base value of x, and j is used to adjust it in increments of three 
			if (i < 3)
			{
				x = 0;
			}
			else if (3 <= i && i < 6)
			{
				x = 1;
			}
			else if (6 <= i)
			{
				x = 2;
			}
			if (j < 3)
			{
				x += 0;
			}
			else if (3 <= j && j < 6)
			{
				x += 3;
			}
			else if (6 <= j)
			{
				x += 6;
			}
			blockGrid.SetRef(x, y, madeCell);
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
			rowGrid.EditValue(i, j, val);
			//as they all share the same references it isnt required read it into every grid

		}
	}
}

bool SudokuPuzzle::Work(CellGroup group)
{
	//used to determine if the entire function needs to recurse to take into account any made changes
	bool changesMade = false;
	//create a vector containing all the known values in the group
	vector<int> values;
	for (int i = 0; i < 9; ++i)
	{
		if (group.GetCellValue(i) != 0)
		{
			values.push_back(group.GetCellValue(i));
		}
	}
	//if there is 9 values, the gorup is solved so ther is no need to do anything
	if (values.size() == 9)
	{
		//cleaning up?
		values.clear();
		return false;
	}

	//NAKED SINGLES
	bool loop;
	do
	{
		loop = false;
		//for every value in the group
		for (int i = 0; i < 9; ++i)
		{
			//do nothing if it is given
			if (group.GetGiven(i))
			{
				continue;
			}
			//and remove all the known values form the cells possibilities
			for (int j = 0; j < values.size(); ++j)
			{
				group.RemoveOption(i, values[j]);
			}
			//if there is only one option, assign it as the value and state a change has been made
			if (group.GetOptions(i).size() == 1)
			{
				group.EditValue(group.GetOptions(i)[0], i);
				values.push_back(group.GetCellValue(i));
				changesMade = true;
				loop = true;
			}
		}
	} while (loop);
	//cleaning up?
	values.clear();

	//HIDDEN SINGLES
	do
	{
		loop = false;
		//for each group memeber
		for (int i = 0; i < 9; ++i)
		{
			//if it hasnt been solved
			if (group.GetCellValue(i) == 0)
			{
				vector <int> possibilities;
				//for each other group member
				for (int j = 0; j < 9; ++j)
				{
					if (i != j)
					{
						//for every option
						for (int k = 0; k < group.GetOptions(j).size(); ++k)
						{
							//if the option isnt already known
							if (std::find(possibilities.begin(), possibilities.end(), group.GetOptions(j)[k]) == possibilities.end())
							{
								//add it to the list
								possibilities.push_back(group.GetOptions(j)[k]);
							}
						}
					}
					else
					{
						continue;
					}
				}
				//for every option
				for (int j = 0; j < group.GetOptions(i).size(); ++j)
				{
					//if that value isnt an option for another square
					if ((std::find(possibilities.begin(), possibilities.end(), group.GetOptions(i)[j]) == possibilities.end()))
					{
						group.EditValue(group.GetOptions(i)[j], i);
						changesMade = true;
						loop = true;
						continue;
					}
				}
			}
		}
	} while(loop);
	if (changesMade)
	{
		Work(group);
		return true;
	}
	return false;
}


void SudokuPuzzle::PrintGrid(PuzzleGrid grid) const
{
	//used for testing purposes
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			cout << " " << grid.GetCellGroupValues(i, j) << " ";
		}
		cout << "\n" << "\n";
	}
}


// This is an example of how you may output the solved puzzle
void SudokuPuzzle::Output(PuzzleGrid grid) const
{
	ofstream fout("sudoku_solution.txt"); // DO NOT CHANGE THE NAME OF THIS FILE
	if(fout.is_open())
	{
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				fout << grid.GetCellGroupValues(i, j) << " ";
			}
			fout << "\n";
		}
		fout.close();
	}
}

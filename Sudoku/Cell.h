#pragma once
#include <vector>
#include <algorithm>

using namespace std;

class Cell
{
public:
	//not sure what to do about this
	Cell();
	~Cell();

	//sets the cells value (should only be used once ideally)
	void SetValue(const int inVal);
	//get the cells value for printing
	int GetValue() const;
	//gets how the value was found (true = provided, false = deduced)
	bool GetGiven() const;
	//get the cells possible values
	int GetOptions(const int i) const;
	void RemoveOption(const int inVal);
	int GetOptionNum() const;

private:
	//value of the cell
	int value;
	//true means it was originally given, false means it was worked out by the program
	bool given;
	//Contains all the possible values of the cell
	//used a vector over int array as it is unlikely a square has 9 possibilities and an aray would have to account for that
	vector<int> options;
	//There is no reason to change given after initialisation !(assuming its given when the cell is created)! thus the method need not be public
	void SetGiven(bool);
	//this should only be used when the value is first given, so it shouldnt be public
	void AddOptions();
};


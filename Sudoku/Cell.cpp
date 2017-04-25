#include "Cell.h"

Cell::Cell()
{
	SetValue(NULL);
	SetGiven(true);
	AddOptions();
}

Cell::~Cell()
{	
	delete this;
}

void Cell::SetValue(const int inVal)
{
	//this stops the program from overwriting a given value other then when the grid is created
	if (value != 0 && given == true)
	{
		throw exception("Editing a given value");
	}
	//used for error checking (should be removed) incase a value too high/low is given by mistake
	if (0 > inVal > 9)
	{
		throw exception("Invalid value: " + inVal);
	}
	//the value should only get set to 0 when being intialised, so if the handed to it is 0 it can be changed
	if (inVal == 0)
	{
		SetGiven(false);
		value = inVal;		
	}
	//if neither of the previous conditions are made then the value is modifiable, thus should be changed to the value
	else 
	{
		value = inVal;
		//if the value is set, then there is no longer a need for the options anymore, thus it  should be removed
		options.clear();
	}
}

int Cell::GetValue() const
{
	return value;
}

void Cell::SetGiven(const bool inGiven)
{
	given = inGiven;
}

bool Cell::GetGiven() const
{
	return given;
}

void Cell::AddOptions()
{
	for (int i = 1; i < 10; ++i)
	{
		options.push_back(i);
	}
}

void Cell::RemoveOption(const int inVal)
{
	options.erase(std::remove(options.begin(), options.end(), inVal), options.end());
}

int Cell::GetOptions(const int i) const
{
	if (i < options.size())
	{
		return options[i];
	}
	else
	{
		return NULL;
	}
}


int Cell::GetOptionNum() const
{
	return options.size();
}
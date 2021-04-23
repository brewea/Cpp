/*
 * Name: Carter Brewer
 * Date Submitted: 1 March 2021
 * Lab Section: 001
 * Assignment Name: Lab 5 - Spell Checker Using A Hash Table
 */


#include <iostream>
#include <functional>
#include <string>
#include "stringset.h"
using namespace std;


Stringset::Stringset() : table(4), num_elems(0), size(4)
{}
//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
	return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
	return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
	return size;
}

void Stringset::insert(string word)
{
	//Implement this function
	hash<string> hashedWord;
	int insert_location = hashedWord(word) % size;
	if (size != num_elems)
	{
		if (!table[insert_location].empty())
		{
			if (!find(word))
			{
				table[insert_location].push_back(word);
				num_elems++;
			}
			else
			{
				cout << "This word exists already" << endl;
			}
		}
		else
		{
			table[insert_location].push_back(word);
			num_elems++;
		}
	}
	else
	{
		table.resize(size * 2);
		size = size * 2;
		int newInsertLocation = hashedWord(word) % size;
		table[newInsertLocation].push_back(word);
		num_elems++;
		for (int i = 0; i < size; ++i)
		{
			list<string>::iterator pos;
			for (pos = table[i].begin(); pos != table[i].end(); pos++)
			{
				newInsertLocation = hashedWord(*pos) % size;
				table[newInsertLocation].push_back(*pos);
				pos = table[i].erase(pos);
			}
		}
	}
}

bool Stringset::find(string word) const
{
	//Implement this function
	hash<string> hashedWordToFind;
	int looking_location = hashedWordToFind(word) % size;
	list<string>::const_iterator pos;
	for (pos = table[looking_location].begin();
		pos != table[looking_location].end(); pos++)
	{
		if (word == *pos){return true;}
	}
	return false;
}

void Stringset::remove(string word)
{
	//Implement this function
	hash<string> hashedWordToRemove;
	int removal_location = hashedWordToRemove(word) % size;
	list<string>::iterator pos;
	for (pos = table[removal_location].begin(); 
		 pos != table[removal_location].end(); pos++)
	{
		if (word == *pos)
		{
			pos = table[removal_location].erase(pos);
			num_elems--;
		}
	}

}

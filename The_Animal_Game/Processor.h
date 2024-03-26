#pragma once
#ifndef PROCESSOR_H_
#define PROCESSOR_H_
#include <map>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct TAnimal
{
	string name;
	string question;
};

class TProcessor
{
public:

	int last_key; // используется для нумерации каждой новой записи в data.txt

	void saveToFile( map<int, TAnimal>& data );

	string removePrefixAndSuffix( string question );

	void loadFromFile( map<int, TAnimal>& data );

	pair<string, string> createNewEntry();

	void addNewEntry( map<int, TAnimal>& data, string newAnimal, string newQuestion );

	void addUnique( vector<string>& vec, string value );
};

#endif


#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;


namespace TheAnimalGame
{
	static  int largest_key;

	struct TAnimal
	{
		string name;
		string question;
	};

	static void saveToFile(map<int, TAnimal>& data)
	{
		ifstream existingFile("data.txt");
		ofstream newFile("data_temp.txt");

		for (auto& pair : data)
		{
			newFile << pair.first << "\n";
			newFile << pair.second.name << "\n";
			newFile << pair.second.question << "\n";
		}

		if (existingFile.is_open())
		{
			newFile << existingFile.rdbuf();
			existingFile.close();
		}

		newFile.close();
		remove("data.txt");
		ignore = rename("data_temp.txt", "data.txt");
	}

	static string removePrefixAndSuffix(string question)
	{
		std::string prefix = "это ";
		std::string suffix = "?";

		if (question.rfind(prefix, 0) == 0)
		{
			question.erase(0, prefix.length());
		}

		if (!question.empty() && question[question.length() - 1] == suffix[0])
		{
			question.erase(question.length() - 1);
		}

		return question;
	}

	static void loadFromFile(map<int, TAnimal>& data)
	{
		ifstream file("data.txt");
		if (file.is_open())
		{
			string key;
			while (getline(file, key))
			{
				TAnimal animal;
				getline(file, animal.name);
				getline(file, animal.question);

				int int_key = stoi(key);
				++int_key;

				data[int_key] = animal;
			}
			file.close();
		}
	}

	static void createAndAddNewEntry(map<int, TAnimal>& data)
	{
		string newAnimal, newQuestion;
		cin >> newAnimal;
		cin.ignore();
		getline(cin, newQuestion);
		newQuestion = removePrefixAndSuffix(newQuestion);
		data.clear();
		data[largest_key] = { newAnimal, newQuestion };
		saveToFile(data);
		loadFromFile(data);
	}

	static void addUnique(vector<string>& vec, string value)
	{
		if (find(vec.begin(), vec.end(), value) == vec.end())
		{
			vec.push_back(value);
		}
	}
}

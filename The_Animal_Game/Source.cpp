#include "TProcessor.cpp"
#include <iostream>
using namespace TheAnimalGame;
using namespace std;

int main()
{
	/*system( "chcp 1251" );
	setlocale( LC_ALL, "" );*/

	map<int, TAnimal> data;
	bool flagEndCycle = false;
	bool guessedRight = false;
	string yes = "да";
	string no = "нет";
	vector<string> exclusionAnimals;
	vector<string> exclusionNamesOfAnimals;
	string answer;
	largest_key = 1;

	loadFromFile(data);

	if (data.empty())
	{
		data[0] = { "гончая собака", "собака" };
		saveToFile(data);
		loadFromFile(data);
	}

	auto firstElement = prev(data.end());
	largest_key = firstElement->first;
	int inner_key = largest_key;
	cout << "Задумайте животное.\n";

	while (!flagEndCycle)
	{
		for (inner_key; inner_key > 0; inner_key--)
		{

			auto it = find(exclusionAnimals.begin(), exclusionAnimals.end(), data[inner_key].question);

			if ((it == exclusionAnimals.end()) || exclusionAnimals.empty())
			{
				cout << "Это животное - " + data[inner_key].question + "?\n";
				cin >> answer;
			}

			addUnique(exclusionAnimals, data[inner_key].question);

			if ((answer != no) && (answer != yes))
			{
				cout << "Нужно ответить „да“ либо „нет“, попробуйте еще раз.\n";
				flagEndCycle = true;
				break;
			}

			if (answer == yes)
			{
				string typeOfAnimal = data[inner_key].question;

				for (inner_key; inner_key > 0; inner_key--)
				{
					if (data[inner_key].question == typeOfAnimal)
					{
						addUnique(exclusionNamesOfAnimals, data[inner_key].name);
						cout << data[inner_key].name + "?\n";
						cin >> answer;

						if (answer == yes)
						{
							cout << "Ура, я угадала!\n";
							flagEndCycle = true;
							guessedRight = true;
							break;
						}
					}
				}

				if (!guessedRight)
				{
					cout << "Увы, я не угадала ваше животное. Назовите мне его и введите вопрос, на который нужно ответить „да“ для вашего животного и „нет“ для ";

					for (auto& value : exclusionNamesOfAnimals)
					{
						cout << value << ' ';
					}

					cout << "\n";
					cout << "Формат ввода текста:  имя_животного это вид_животного? \n";
					createAndAddNewEntry(data);
					flagEndCycle = true;
					cout << "Спасибо, теперь я знаю что вы загадали!\n";
					break;
				}

				if (flagEndCycle)
				{
					break;
				}
			}

			if (data[inner_key].name == "гончая собака")
			{
				cout << "Увы, я не угадала ваше животное. Назовите мне его и введите вопрос, на который нужно ответить „да“ для вашего животного и „нет“ для ";

				for (auto& value : exclusionAnimals)
				{
					cout << value << ' ';
				}

				cout << "\n";
				cout << "Формат ввода текста: „имя_животного это вид_животного?“\n";
				createAndAddNewEntry(data);
				flagEndCycle = true;
				cout << "Спасибо, теперь я знаю что вы загадали!\n";
				break;
			}
		}
	}

}



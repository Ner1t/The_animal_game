#include "TProcessor.cpp"
#include <iostream>
using namespace TheAnimalGame;
using namespace std;

int main()
{
	/*system( "chcp 1251" );     //Оставил на всякий случай.
	setlocale( LC_ALL, "" );*/

	map<int, TAnimal> data;
	bool flagEndCycle = false;
	bool guessedRight = false;
	vector<string> exclusionAnimals;
	vector<string> exclusionNamesOfAnimals;
	string yes = "да";
	string no = "нет";
	string answer;
	int inner_key;
	largest_key = 1;

	loadFromFile( data );

	if ( data.empty() )
	{
		data[0] = { "гончая собака", "собака" };
		saveToFile( data );
		loadFromFile( data );
	}

	auto firstElement = prev( data.end() );
	largest_key = firstElement->first;
	inner_key = largest_key;

	cout << "Задумайте животное.\n";
	cout << "\n";

	while ( !flagEndCycle )
	{
		for ( inner_key; inner_key >= 0; inner_key-- )
		{
			auto it = find( exclusionAnimals.begin(), exclusionAnimals.end(), data[inner_key].question ); // проверка на уникальность типа животного.

			if ( ( it == exclusionAnimals.end() ) || exclusionAnimals.empty() )
			{
				if ( data.size() == 1 ) // стартовое условие.
				{
					cout << "Это животное - " + data[inner_key].name + "?\n";
				}
				else
				{
					cout << "Это животное - " + data[inner_key].question + "?\n";
				}

				cin >> answer;
			}

			addUnique( exclusionAnimals, data[inner_key].question );

			if ( ( answer != no ) && ( answer != yes ) )
			{
				cout << "Нужно ответить „да“ либо „нет“, попробуйте еще раз.\n";
				flagEndCycle = true;
				break;
			}

			if ( answer == yes )
			{
				string typeOfAnimal = data[inner_key].question;

				for ( inner_key; inner_key >= 0; inner_key-- )
				{
					if ( data[inner_key].question == typeOfAnimal ) //условие для работы с подтипами.
					{
						addUnique( exclusionNamesOfAnimals, data[inner_key].name );

						if ( data.size() != 1 ) //стартовое условие.
						{
							cout << data[inner_key].name + "?\n";
							cin >> answer;
						}

						if ( answer == yes )
						{
							cout << "Ура, я угадала!\n";
							flagEndCycle = true;
							guessedRight = true;
							break;
						}
					}
				}

				if ( !guessedRight ) // случай когда такого ПОДТИПА не существует в базе.
				{
					cout << "Увы, я не угадала ваше животное. Назовите мне его и введите вопрос, на который нужно ответить „да“ для вашего животного и „нет“ для ";

					for ( auto& value : exclusionNamesOfAnimals )
					{
						cout << value << ' ';
					}

					cout << "\n";
					cout << "Формат ввода текста:  имя_животного это вид_животного? \n";
					auto nameType = createNewEntry();
					addNewEntry( data, nameType.first, nameType.second );
					flagEndCycle = true;
					cout << "Спасибо, теперь я знаю что вы загадали!\n";
					break;
				}

				if ( flagEndCycle )
				{
					break;
				}
			}

			if ( data[inner_key].name == "гончая собака" ) //случай когда такого ТИПА не существует в базе.
			{
				cout << "Увы, я не угадала ваше животное. Назовите мне его и введите вопрос, на который нужно ответить „да“ для вашего животного и „нет“ для ";

				for ( auto& value : exclusionAnimals )
				{
					cout << value << ' ';
				}

				cout << "\n";
				cout << "Формат ввода текста: „имя_животного это вид_животного?“\n";
				auto nameType = createNewEntry();
				addNewEntry( data, nameType.first, nameType.second );
				flagEndCycle = true;
				cout << "Спасибо, теперь я знаю что вы загадали!\n";
				break;
			}
		}
	}
	return 0;
};



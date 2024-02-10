#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

namespace TheAnimalGame
{
	struct TAnimal
	{
		string name;
		string question;
	};

	struct TProcessor
	{
		int last_key; // используется для нумерации каждой новой записи в data.txt

		//! Основной оператор
	//! Принимает ссылку на map с входными данными data
	//! Сохраняет новые данные путем Пересоздания файла data.txt
	//! с актуальными параметрами которые беруться из входного параметра.
		void saveToFile( map<int, TAnimal>& data )
		{
			ifstream existingFile;
			ofstream newFile;

			try
			{
				existingFile.open( "data.txt" );
				newFile.open( "data_temp.txt" );
			}

			catch ( const ifstream::failure& exp )
			{
				cerr << exp.what() << "\n";
				cerr << exp.code();
			}

			for ( auto& pair : data )
			{
				newFile << pair.first << "\n";
				newFile << pair.second.name << "\n";
				newFile << pair.second.question << "\n";
			}

			if ( existingFile.is_open() )
			{
				newFile << existingFile.rdbuf();
				existingFile.close();
			}

			newFile.close();
			remove( "data.txt" );
			ignore = rename( "data_temp.txt", "data.txt" );
		};

		//! Основной оператор
		//! Принимает строку question и редактирует ее по шаблонам. 
		//! Цель форматирования получить информацию по которой будет происходить сортировка.
		//! Возвращает отредактированную строку question.
		string removePrefixAndSuffix( string question )
		{
			std::string prefix = "это ";
			std::string suffix = "?";

			if ( question.rfind( prefix, 0 ) == 0 )
			{
				question.erase( 0, prefix.length() );
			}

			if ( !question.empty() && question[question.length() - 1] == suffix[0] )
			{
				question.erase( question.length() - 1 );
			}

			return question;
		};

		//! Основной оператор
		//! Принимает ссылку на map с входными данными data. 
		//! Загружает информацию из файла data.txt и заполняет ею data экземпляр структуры map.
		void loadFromFile( map<int, TAnimal>& data )
		{
			ifstream file;

			try
			{
				file.open( "data.txt" );
			}

			catch ( const std::ifstream::failure& exp )
			{
				cerr << exp.what() << "\n";
				cerr << exp.code();
			}

			if ( file.is_open() )
			{
				string key;
				while ( getline( file, key ) )
				{
					TAnimal animal;
					getline( file, animal.name );
					getline( file, animal.question );
					int int_key = stoi( key );
					data[int_key] = animal;
				}
				file.close();
			}
		};

		//! Основной оператор
		//! Получает из консоли 2 строки, обрабатывает и возращает. 
		//! Возвращаемое значение это пара строк.
		pair<string, string> createNewEntry()
		{
			string newAnimal, newQuestion;
			cin >> newAnimal;
			cin.ignore();
			getline( cin, newQuestion );
			newQuestion = removePrefixAndSuffix( newQuestion );
			return make_pair( newAnimal, newQuestion );
		};

		//! Основной оператор
		//! Принимает ссылку на map с входными данными data, и две строки.
		//! Добавляет в data новую запись с добавлением индекса.
		void addNewEntry( map<int, TAnimal>& data, string newAnimal, string newQuestion )
		{
			data.clear();
			data[++last_key] = { newAnimal, newQuestion };
			saveToFile( data );
			loadFromFile( data );
		};

		//! Основной оператор
		//! Принимает ссылку на vector с входными данными vec, строка value.
		//! Проверяет value и добавляет в vec только если она уникальна для vec.
		void addUnique( vector<string>& vec, string value )
		{
			if ( find( vec.begin(), vec.end(), value ) == vec.end() )
			{
				vec.push_back( value );
			}
		};
	};
};


#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
//using namespace std;

int largest_key = 1;

    struct TAnimal
    {
        std::string name;
        std::string question;
    };

    static void saveToFile( std::map<int, TAnimal>& data )
    {
        std::ifstream existingFile( "data.txt" );
        std::ofstream newFile( "data_temp.txt" );

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
        std::remove( "data.txt" );
        std::ignore = std::rename( "data_temp.txt", "data.txt" );
    }

     static std::string removePrefixAndSuffix( std::string question )
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
    }

     static void loadFromFile( std::map<int, TAnimal>& data )
    {
        std::ifstream file( "data.txt" );
        if ( file.is_open() )
        {
            std::string key;
            while ( std::getline( file, key) )
            {
                TAnimal animal;
                std::getline( file, animal.name );
                std::getline( file, animal.question );

                int int_key = stoi( key );
                ++int_key;

                data[int_key] = animal;
            }
            file.close();
        }
    }

     static void createAndAddNewEntry( std::map<int, TAnimal> data )
    {
        std::string newAnimal, newQuestion;
        std::cin >> newAnimal;
        std::cin.ignore();
        std::getline( std::cin, newQuestion );
        newQuestion = removePrefixAndSuffix( newQuestion );
        data.clear();
        data[largest_key] = { newAnimal, newQuestion };
        saveToFile( data );
        loadFromFile( data );
    }

     static void addUnique( std::vector<std::string>& vec, std::string value )
    {
        if ( std::find( vec.begin(), vec.end(), value ) == vec.end() )
        {
            vec.push_back( value );
        }
    }

    int main()
    {
        /*system( "chcp 1251" );
        setlocale( LC_ALL, "" );*/

        std::map<int, TAnimal> data;
        bool flagEndCycle = false;
        bool guessedRight = false;
        std::string yes = "да";
        std::string no = "нет";
        std::vector<std::string> exclusionAnimals;
        std::vector<std::string> exclusionNamesOfAnimals;
        std::string answer;
               
        loadFromFile( data );

        if ( data.empty() )
        {
            data[0] = { "гончая собака", "собака" };
            saveToFile( data );
            loadFromFile( data );
        } 

        auto firstElement = std::prev( data.end() );
        largest_key = firstElement->first;
        int inner_key = largest_key;
        std::cout << "Задумайте животное.\n";

        while ( !flagEndCycle )
        {
            for ( inner_key; inner_key > 0; inner_key-- )
            {

                auto it = std::find( exclusionAnimals.begin(), exclusionAnimals.end(), data[inner_key].question );

                if ( ( it == exclusionAnimals.end() ) || exclusionAnimals.empty() )
                {
                    std::cout << "Это животное - " + data[inner_key].question + "?\n";
                    std::cin >> answer;
                }

                addUnique( exclusionAnimals, data[inner_key].question );

                if ( ( answer != no ) && ( answer != yes ) )
                {
                    std::cout << "Нужно ответить „да“ либо „нет“, попробуйте еще раз.\n";
                    flagEndCycle = true;
                    break;
                }

                if ( answer == yes )
                {
                    std::string typeOfAnimal = data[inner_key].question;

                    for ( inner_key; inner_key > 0; inner_key-- )
                    {
                        if ( data[inner_key].question == typeOfAnimal )
                        {
                            addUnique( exclusionNamesOfAnimals, data[inner_key].name );
                            std::cout << data[inner_key].name + "?\n";
                            std::cin >> answer;

                            if ( answer == yes )
                            {
                                std::cout << "Ура, я угадала!\n";
                                flagEndCycle = true;
                                guessedRight = true;
                                break;
                            }
                        }
                    }

                    if ( !guessedRight )
                    {
                        std::cout << "Увы, я не угадала ваше животное. Назовите мне его и введите вопрос, на который нужно ответить „да“ для вашего животного и „нет“ для ";

                        for ( auto& value : exclusionNamesOfAnimals )
                        {
                            std::cout << value << ' ';
                        }

                        std::cout << "\n";
                        std::cout << "Формат ввода текста:  имя_животного это вид_животного? \n";
                        createAndAddNewEntry( data );
                        flagEndCycle = true;
                        std::cout << "Спасибо, теперь я знаю что вы загадали!\n";
                        break;
                    }

                    if ( flagEndCycle )
                    {
                        break;
                    }
                }

                if ( data[inner_key].name == "гончая собака" )
                {
                    std::cout << "Увы, я не угадала ваше животное. Назовите мне его и введите вопрос, на который нужно ответить „да“ для вашего животного и „нет“ для ";

                    for ( auto& value : exclusionAnimals)
                    {
                        std::cout << value << ' ';
                    }

                    std::cout << "\n";
                    std::cout << "Формат ввода текста: „имя_животного это вид_животного?“\n";
                    createAndAddNewEntry( data );
                    flagEndCycle = true;
                    std::cout << "Спасибо, теперь я знаю что вы загадали!\n";
                    break;
                }
            }
        }
    }



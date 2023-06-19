#include "../inc/interface.hpp"
#include <string>

int main()
{
    try
    {
        //переменные для main.cpp
        std::string input_file;
        std::string output_file;

        setlocale(LC_ALL, "");

        
        std::wcout << L"Введите имя файла входных данных: ";
        std::cin >>  input_file;
        std::wcout << L"Введите имя файла для выходных данных: ";
        std::cin >>  output_file;
            
        Interface inter("./tmp/" + input_file, "./tmp/" + output_file);

    
    }
    catch(string error_message)
    {
        cout << error_message << endl;
        return 1;
    } 

    return 0;
}
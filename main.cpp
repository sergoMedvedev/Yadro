#include <iostream>
#include <string>


class IStorageDevice
{
public:
    void virtual read() = 0;
    void virtual write() = 0;
};

class Tape : public IStorageDevice
{
public:
    void read() override
    {
        //реализация чтения 
    }

    void write() override
    {
        // реализация записи 
    }
};

class DataProcess
{
public:
    void algorithm(Tape & name_file)
    {
        //алгоритм высолнения сортировки
    }
};

class Run
{
public:
    Run()
    {
        startApp();
    }
    
    void startApp()
    {
        setlocale(LC_ALL, "");

        std::string file_in;
        std::string file_out;

        std::wcout << L"Введите имя файла входных данных: ";
        std::cin >> file_in;
        std::wcout << L"Введите имя файла для выходных данных: ";
        std::cin >> file_out;
        


    }
};

int main()
{
    Run project;
}
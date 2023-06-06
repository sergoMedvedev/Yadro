#include <iostream>


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
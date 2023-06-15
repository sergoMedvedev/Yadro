#ifndef PARSCONFIG_H //проверка на одно поключение
#define PARSCONFIG_H

#include <string>
#include <iostream>
#include <fstream>

/*
Данный класс реализует методы обработки конфигурационного файла.
*/
class ParsConfig
{
public:
    //переменные
    double w_delay; //задержка на записе 
    double r_delay; // задержка на чтение 
    double tape_rewind; // перемотка ленты 
    double moov_one_position; //сдвиг ленты на одну позицию
    long int memory; // количество выделеноой памяти

    ParsConfig(std::string name_file);
    
private:
    void addInfo(std::string file); //Парсин файла cfg.txt 
};

#endif
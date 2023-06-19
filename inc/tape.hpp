#ifndef TAPPE_H
#define TAPPE_H


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "parsCfg.hpp"
#include "algorithm.hpp"
#include "windows.h"

#define DELIMITER " "

using namespace std;

 
class Tape 
{
public:
    //переменные
    string file_name_input; //имя входного файла 
    string file_name_output; // имя выходного файла 
    int name_number_buffer; // имя/номер буфера
    double w_delay; //задержка на записе 
    double r_delay; // задержка на чтение 
    double tape_rewind; // перемотка ленты 
    double moov_one_position; //сдвиг ленты на одну позицию
    long int memory; // количество выделеноой памяти
    unsigned int subSize;
    
    //конструктор
    Tape(string input_file, ParsConfig *parsFile);
    
    //конструктор для выходного файла 
    Tape(string out_file_name, int name_number_bufer, ParsConfig *parsFile);

    //метод открытия выходного файла
    static void write_sorted_data_in_outfile(string outFile, int number, double w_daley, double moov_one_position);

    //метод для наполнения буферов отсортированными числами
    static void write_in_buffer(vector<int> *subData, int *name_bufer, int *j, double w_delay, double moov_one_position);

    // закрытие и удаление буферов
    static void close_and_removing_buffers(vector<ifstream> *subFiles, int number_and_name_bufer); 
        
    
private:
    //метод прочтения входного файла, разделение его на буферы и сортировка их
    int read_inputFile(string fileName, int subSize);
        
    //метод открывания потоков для каждого буфера
    void read_buffers(int name_bufer);

};

#endif
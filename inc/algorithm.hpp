#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <queue>
#include <iostream>
#include <vector>
#include <fstream> 
#include <algorithm>

using namespace std;

class Algorithm
{
public:
    //статический метод сортировки буферов
    static void sort_buffer(std::vector<int> *subData, int *j);
       
    //метод слияния
    static void mergeFile(int number_and_name_bufer, std::vector<std::ifstream> *subFiles, std::string file_out_name); 
};

#endif
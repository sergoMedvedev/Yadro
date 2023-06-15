#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include "parsCfg.hpp"
#include "tape.hpp"
#include "constans.h"


class Interface
{
public:
    //переменные
    std::string name_file_input; //имя входного файла 
    std::string name_file_output; //имя выходного файла 

    //конструктор 
    Interface(std::string input, std::string output);

    void make_duffers_for_sort();
    
    void merging_buffers(int name_num_bufer);
};
#endif

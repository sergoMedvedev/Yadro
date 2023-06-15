#include "../inc/parsCfg.hpp"
    

//конструктор конфига   
ParsConfig::ParsConfig(std::string name_file)
{
    addInfo(name_file);
}

//Парсин файла cfg.txt
void ParsConfig::addInfo(std::string file) //Парсин файла cfg.txt
{
    //переменные
    std::string param;
    double value;
    std::ifstream fl(file);
    if (fl.is_open())
    {
        while (!(fl.eof()))
        {
            fl >> param;
            fl >> value;
            if (param == "w_delay") //проверка на число
            {   
                w_delay = value;
                continue;
            }
            else if (param == "r_delay")
            {
                r_delay = value;
                continue;
            }
            else if (param == "tape_rewind")
            {
                tape_rewind = value;
                continue;
            }
            else if (param == "moov_one_position")
            {
                moov_one_position = value;
                continue;
            }
            else if (param == "memory")
            {
                memory = value;
            }
        }  
    }
    else
    {
        std::cout << "problem with cfg.txt file";
    }

    fl.close(); // закрытие файла
}   
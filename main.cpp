#include <iostream>
#include <string>
#include <fstream>
using namespace std;


class IStorageDevice
{
public:
    void virtual read() = 0;
    void virtual write() = 0;
};

class Tape : public IStorageDevice
{


public:
    int a;

    Tape(int a)
    {

    }

    void read() override
    {
        //реализация чтения 
    }

    void write() override
    {
        // реализация записи 
    }
};

class Algorithm
{
public:
    void algorithm(Tape & name_file)
    {
        //алгоритм высолнения сортировки
    }
};



void worker()
{

    setlocale(LC_ALL, "");

        std::string file_in;
        std::string file_out;

        std::wcout << L"Введите имя файла входных данных: ";
        std::cin >> file_in;
        std::wcout << L"Введите имя файла для выходных данных: ";
        std::cin >> file_out;
    
}


class AddInfo
{
public:
    double write_delay; //задержка по записи 
    double delay_in_reading; // задержка по чтению
    double tape_rewind; // перемотка ленты 
    double shift_tape_one_position; // сдвижение ленты на одну позицию

    AddInfo(string name_file)
    {
        addInfo(name_file);
    }

    void arrayToNumberConst(double array[4])
    {
        for (int i =0; i<4; i++)
        {
            if (i == 0) write_delay = array[0];
            if (i == 1) delay_in_reading = array[1];
            if (i == 2) tape_rewind = array[2];
            if (i == 3) shift_tape_one_position = array[3];
        }
        
        cout << write_delay << endl;
        cout << delay_in_reading << endl;
        cout << tape_rewind << endl;
        cout << shift_tape_one_position << endl;
    }

    bool isNumber(string str)
    {
        if (!(str.empty()) && str.find_first_not_of("0123456789")) 
        {
            return true;
        }else
        {
            return false;
        }
    }

    double strToDouble(string str)
    {
        char chars[str.length() + 1];
        str.copy(chars, str.length() + 1);
        return atof(chars);
    }

    void addInfo(string file)
    {
        double array_number[4];
        int counter = 0;

        ifstream fl(file);
        string str;
        if (fl.is_open())
        {
            while (!(fl.eof()))
            {
                str = "";
                fl >> str;
                if (isNumber(str)) //проверка на число
                {   
                    array_number[counter] = strToDouble(str); 
                    counter++; 
                }
                continue;
            }  
        }else
        {
            cout << "problem with cfg.txt file";
        }
        fl.close(); // закрытие файла
        arrayToNumberConst(array_number);
    }
}; 

int main()
{
    string name_file = "cfg.txt";
    AddInfo file(name_file);
    //worker();

    return 0;
}





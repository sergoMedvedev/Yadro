#include <iostream> 
#include <fstream> 
#include <vector> 
#include <algorithm> 
#include <queue> 
#include <string>


#define DELIMITER " " 

//голобальные переменные
double write_delay; //задержка на записе 
double delay_in_reading; // задержка на чтение 
double tape_rewind; // перемотка ленты 
double shift_tape_one_position; //сдвиг ленты на одну позицию
long int memory; // количество выделеноой памяти
unsigned int subSize = (memory)/sizeof(int);

using namespace std;

//функции
//методы класса Tape
int read_for_bufer(string fileName, int subSize);
int write_in_bufer(vector<int> *subData, int name_bufer, int j);
void read_bufers(int name_bufer);
void write_sorted_data_in_outfile(string outFile, int number);
//ParsConfig
void addInfo(string file);
//Algorithm
static void sort_bufer(vector<int> *subData, int *j);
static void mergeFile(int number_and_name_bufer, vector<ifstream> *subFiles, string file_out_name);



class ParsConfig
{
    public:

    ParsConfig(string name_file)
    {
        addInfo(name_file);
    }

    void addInfo(string file)
    {
        double array_number[2];
        int counter = 0;

        ifstream fl(file);
        string param;
        double value;
        if (fl.is_open())
        {
            while (!(fl.eof()))
            {
                fl >> param;
                fl >> value;
                if (param == "write_delay") //проверка на число
                {   
                    write_delay = value;
                    continue;
                }
                else if (param == "delay_in_reading")
                {
                    delay_in_reading = value;
                    continue;
                }
                else if (param == "tape_rewind")
                {
                    tape_rewind = value;
                    continue;
                }
                else if (param == "shift_tape_one_position")
                {
                    shift_tape_one_position = value;
                    continue;
                }
                else if (param == "memory")
                {
                    memory = value;
                }
            }  
        }else
        {
            cout << "problem with cfg.txt file";
        }
        fl.close(); // закрытие файла
    }
    
};

class Tape 
{
public:
    //переменные
    static string status_tape; //состояние ленты(пока что не знаю буду ли использовать)
    string file_name_input;
    string file_name_output;
    int name_number_bufer;
    

    //конструктор для входного файла
    Tape(string input_file)
    {
        file_name_input = input_file;
        name_number_bufer = read_for_bufer(file_name_input, subSize);
    }

    //конструктор для выходного файла 
    Tape(string out_file_name, int name_number_bufer)
    {
        file_name_output = out_file_name;
        read_bufers(name_number_bufer);
    }

    //метод для наполнения буферов
    static void write_in_bufer(vector<int> *subData, int *name_bufer, int *j)
    {
        ofstream outputFile(to_string(*name_bufer));
        for (int k = 0; k < *j; ++k) // заполнение буфера отсортированными числами
        {  
            outputFile << (*subData)[k] << DELIMITER;
        }
        outputFile.close();
        name_bufer ++;
    }
        

    //метод спочтения файла для создания буферов
    int read_for_bufer(string fileName, int subSize)
        {
        int number_and_name_bufer; //номер и имя буфера 
        bool endOfFile = false; //хранит в себе состояние конец или нет файла 
        ifstream inputFile(fileName); 
        while (!endOfFile) //заполение вектора данными 
        { 
            vector<int> subData(subSize); // создаем вектор размера subSize
            for (int j = 0; j < subSize; ++j) //заполнение вектора на определённую величину
            {  
                if (!inputFile.eof())
                { 
                    inputFile >> subData[j]; 
                } else 
                { 
                    endOfFile = true; 
                    break; 
                }
            Algotithm::sort_bufer(&subData, &j);
            write_in_bufer(&subData, &number_and_name_bufer, &j);
            } 
        }
        inputFile.close();
        return number_and_name_bufer;
        }
    

    //метод открывания потоков для каждого буфера
    void read_bufers(int name_bufer)
    {
        vector<ifstream> subFiles(name_bufer); 
        for (int i = 0; i < name_bufer; ++i) { 
            subFiles[i].open(to_string(i)); 
        }
        Algotithm::mergeFile(name_number_bufer, &subFiles, file_name_output);
    } 
    

    //метод открытия выходного файла
    static void write_sorted_data_in_outfile(string outFile, int number)
    {
        ofstream outputFile(outFile);
        if (outputFile.is_open())
        {
            // загрузка в выодный файл числа 
            outputFile << number << DELIMITER;
        }else
        {
            cout << "ERROR" << endl;
        }
        outputFile.close();
    }
};

class Interface
{
public:

    //переменные
    string name_file_input; //имя входного файла 
    string name_file_output; //имя выходного файла 

    //конструктор 
    Interface(string input, string output)
    {
        name_file_input = "./tmp/"+input;
        name_file_output = "./tmp/"+output;
        make_dufers_for_sort();
    }

    void make_dufers_for_sort()
    {

        ParsConfig conf("./config/cfg.txt");

        Tape inFile(name_file_input);
        merging_bufers(&(inFile.name_number_bufer));
    }
    void merging_bufers(int *name_num_bufer )
    {
        Tape outFile(name_file_output, *name_num_bufer);

    }
};



class Algotithm
{
public:

    //статический метод сортировки буферов
    static void sort_bufer(vector<int> *subData, int *j)
        {
            sort((*subData).begin(), (*subData).begin() + *j);
        }
       

    //метод слияния
    static void mergeFile(int number_and_name_bufer, vector<ifstream> *subFiles, string file_out_name)
    {
        auto compare = [](pair<int, int>& a, pair<int, int>& b) { 
            return a.first > b.first; 
        }; 
    
        // Используем приоритетную очередь для хранения минимального элемента из каждого файла 
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> pq(compare); 
    
        for (int i = 0; i < number_and_name_bufer; ++i)
        { 
            int number; 
            (*subFiles)[i] >> number; 
            pq.push({number, i}); 
        } 
    
        while (!pq.empty()) 
        { 
            pair<int, int> minElem = pq.top(); 
            pq.pop(); 
            Tape::write_sorted_data_in_outfile(file_out_name, minElem.first);
            //outputFile << minElem.first << DELIMITER; 
            if (!(*subFiles)[minElem.second].eof()) 
            { 
                int number; 
                (*subFiles)[minElem.second] >> number; 
                pq.push({number, minElem.second}); 
            } 
        } 
    }
    
};

int main()
{
    cout << "hi";

    string in_file= "input.txt";
    string out_file = "output.txt";
   
    Interface inter(in_file,out_file);

    return 1;
}

    
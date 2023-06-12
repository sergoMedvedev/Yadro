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
            sort_bufer(&subData, &j);
            Tape::write_in_bufer(&subData, number_and_name_bufer, j);
            } 
        }
        inputFile.close();
        return number_and_name_bufer;
    }

int write_in_bufer(vector<int> *subData, int name_bufer, int j)
    {
        ofstream outputFile(to_string(name_bufer));
        for (int k = 0; k < j; ++k) // заполнение буфера отсортированными числами
        {  
            outputFile << (*subData)[k] << DELIMITER;
        }
        outputFile.close();
        name_bufer ++;
        return name_bufer;
    }

void read_bufers(int name_bufer)
    {
        vector<ifstream> subFiles(name_bufer); 
        for (int i = 0; i < name_bufer; ++i) { 
            subFiles[i].open(to_string(i)); 
        } 
    } 

void write_sorted_data_in_outfile(string outFile, int number)
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


//ParsConfig
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


//Algorithm
static void sort_bufer(vector<int> *subData, int *j)
        {
            sort((*subData).begin(), (*subData).begin() + *j);
        }

static void mergeFile(int number_and_name_bufer, vector<ifstream> *subFiles, string file_out_name)
    {
        Tape outpuyFils(file_out_name);
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
            outpuyFils.write_sorted_data_in_outfile(file_out_name, minElem.first);
            //outputFile << minElem.first << DELIMITER; 
            if (!(*subFiles)[minElem.second].eof()) 
            { 
                int number; 
                (*subFiles)[minElem.second] >> number; 
                pq.push({number, minElem.second}); 
            } 
        } 
    }





class Tape 
{
public:
    //переменные
    static string status_tape; //состояние ленты(пока что не знаю буду ли использовать)
    string file_name_input;
    string file_name_output;

    //конструктор для входного файла
    Tape(string input_file, unsigned int subSize)
    {
        file_name_input = input_file;
    }

    //конструктор для выходного файла 
    Tape(string out_file_name)
    {
        file_name_output = out_file_name;
    }

    //метод для наполнения буферов
    static int write_in_bufer(vector<int> *subData, int name_bufer, int j);

    //метод спочтения файла для создания буферов
    int read_for_bufer(string fileName, int subSize);
    

    //метод открывания потоков для каждого буфера
    void read_bufers(int name_bufer);
    

    //метод открытия выходного файла
    void write_sorted_data_in_outfile(string outFile, int number);
};



class ParsConfig
{
    public:

    ParsConfig(string name_file)
    {
        addInfo(name_file);
    }

    void addInfo(string file);
    
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
        name_file_input = input;
        name_file_output = output;
    }

    void make_dufers_for_sort()
    {
        //переменные 
        string input_name ="./tmp/input.txt";
        string output_name = "./tmp/output.txt";

        ParsConfig("./config/cfg.txt");
        cout << memory << endl; 

        Tape inFile(name_file_input, subSize);
        inFile.read_for_bufer(name_file_input, subSize);


        

    }
    void merging_bufers()
    {

    }

};
class Algotithm
{
public:

    //статический метод сортировки буферов
    static vector<int> sort_bufer(vector<int> *subData, int *j);
       

    //метод слияния
    static void mergeFile(int number_and_name_bufer, vector<ifstream> *subFiles, string file_out_name);
    
};




int main()
{
    cout << "hi";
    return 1;
}






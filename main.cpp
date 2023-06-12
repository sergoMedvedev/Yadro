#include <iostream> 
#include <fstream> 
#include <vector> 
#include <algorithm> 
#include <queue> 
#include <string> 

#define DELIMITER " " 

double write_delay; //задержка на записе 
double delay_in_reading; // задержка на чтение 
double tape_rewind; // перемотка ленты 
double shift_tape_one_position; //сдвиг ленты на одну позицию
long int memory; // количество выделеноой памяти

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

    
    Tape()
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
    string input_file;
    string output_file;
    unsigned int subSize;
    
    
    


    Algorithm(string input, string output)
    {
        this->input_file = input; 
        this->output_file = output;
        cout << sizeof(int) << endl;
        cout << memory << endl;
        this->subSize = (memory)/sizeof(int);
        

        externalSort(input_file,output_file, subSize);
    }

    // Функция для разделения файла на отсортированные подфайлы 
    int splitFile(string fileName, int subSize) { 
        ifstream inputFile(fileName); 
        int i = 0; 
        
        bool endOfFile = false; 
    
        while (!endOfFile) { //заполение вектора данными 
            vector<int> subData(subSize); // создаем вектор размера subSize
            int j; 
            for (j = 0; j < subSize; ++j) { 
                if (!inputFile.eof()) { 
                    inputFile >> subData[j]; 
                } else { 
                    endOfFile = true; 
                    break; 
                } 
            } 
    
            // Сортируем данные в подфайле 
            sort(subData.begin(), subData.begin() + j); // сотрировка вектора
            ofstream outputFile(to_string(i)); // создает файл с названием i 
            for (int k = 0; k < j; ++k) { // заполнение буфера отсортированными числами 
                outputFile << subData[k] << DELIMITER; 
            } 
    
            outputFile.close(); 
            i++; 
        } 
    
        inputFile.close(); 
        return i; 
    } 
 
    // Функция для слияния подфайлов в один отсортированный файл 
    void mergeFiles(string outputFileName, int n, int subSize) { 
        vector<ifstream> subFiles(n); 
        for (int i = 0; i < n; ++i) { 
            subFiles[i].open(to_string(i)); 
        } 
    
        // Открываем файл для вывода 
        ofstream outputFile(outputFileName); 
    
        auto compare = [](pair<int, int>& a, pair<int, int>& b) { 
            return a.first > b.first; 
        }; 
    
        // Используем приоритетную очередь для хранения минимального элемента из каждого файла 
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> pq(compare); 
    
        for (int i = 0; i < n; ++i) { 
            int number; 
            subFiles[i] >> number; 
            pq.push({number, i}); 
        } 
    
        while (!pq.empty()) { 
            pair<int, int> minElem = pq.top(); 
            pq.pop(); 
            outputFile << minElem.first << DELIMITER; 
    
            if (!subFiles[minElem.second].eof()) { 
                int number; 
                subFiles[minElem.second] >> number; 
                pq.push({number, minElem.second}); 
            } 
        } 
    
        for (int i = 0; i < n; ++i) { 
            subFiles[i].close(); 
            remove(to_string(i).c_str()); 
        } 
    
        outputFile.close(); 
    } 
 
    // Внешняя сортировка 
    void externalSort(string fileName, string outputFileName, int subSize) { 
        // Создаем отсортированные подфайлы 
        int numSubFiles = splitFile(fileName, subSize); 
        // Сливаем отсортированные подфайлы 
        mergeFiles(outputFileName, numSubFiles, subSize); 
    } 

};

class AddInfo
{
public:

    AddInfo(){}

    AddInfo(string name_file)
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



void worker()
{
    setlocale(LC_ALL, "");

    string file_in;
    string file_out;
    string cfg_name = "cfg.txt";

    wcout << L"Введите имя файла входных данных: ";
    cin >>  file_in;
    wcout << L"Введите имя файла для выходных данных: ";
    cin >>  file_out;
    

    AddInfo file("./config/"+cfg_name);
    Algorithm alg("./tmp/"+file_in,"./tmp/"+file_out);
    
}


 

int main()
{
    worker();
    
    

    return 0;
}




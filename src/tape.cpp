#include "../inc/tape.hpp"
#include "../inc/algorithm.hpp"


//конструктор для входного файла 
Tape::Tape(string input_file, ParsConfig *pasrCFG)
{
    this->w_delay = pasrCFG->w_delay;
    this->r_delay = pasrCFG->r_delay;
    this->tape_rewind = pasrCFG->tape_rewind;
    this->moov_one_position = pasrCFG->moov_one_position;
    this->subSize = (pasrCFG->memory)/sizeof(int);
    this->file_name_input = input_file;
    this->name_number_buffer = this->read_inputFile(file_name_input, this->subSize);
}

//конструктор для выходного файла 
Tape::Tape(string out_file_name, int name_number_buffer, ParsConfig *parsFile)
{
    this->file_name_output = out_file_name;
    this->name_number_buffer = name_number_buffer;
    this->w_delay = parsFile->w_delay;
    this->r_delay = parsFile->r_delay;
    this->tape_rewind = parsFile->tape_rewind;
    this->moov_one_position = parsFile->moov_one_position;
    this->read_buffers(name_number_buffer);
}

//метод для наполнения буферов отсортированными числами
void Tape::write_in_buffer(vector<int> *subData, int *name_buffer, int *j, double w_delay, double moov_one_position)
{
    ofstream outputFile(to_string(*name_buffer));
    if (outputFile.is_open())
    {
        for (int k = 0; k <= *j; ++k) // заполнение буфера отсортированными числами
        {  
            Sleep(1000*w_delay);
            Sleep(1000*moov_one_position);
            outputFile << (*subData)[k] << DELIMITER;
        }
        outputFile.close();
        name_buffer ++;  
    }
    else
    {
        throw "file did not open";
    }     
}
        
//метод прочтения входного файла, разделение его на буферы и сортировка их
int Tape::read_inputFile(string fileName, int subSize) //не static
{
    int number_and_name_buffer = 0; //номер и имя буфера 
    bool endOfFile = false; //хранит в себе состояние конец или нет файла 
    ifstream inputFile(fileName); 

    if (inputFile.is_open())
    {
        while (!endOfFile) //заполение вектора данными 
        { 
            vector<int> subData(subSize); // создаем вектор размера subSize
            for (int j = 0; j < subSize; ++j) //заполнение вектора на определённую величину
            {  
                Sleep(1000*this->moov_one_position);
                if (!inputFile.eof())
                { 
                    Sleep(1000*this->r_delay);
                    inputFile >> subData[j]; 
                } 
                else 
                { 
                    endOfFile = true; 
                    break; 
                }

                Algorithm::sort_buffer(&subData, &j); //статический метод класса Algorithm
                this->write_in_buffer(&subData, &number_and_name_buffer, &j, this->w_delay, this->moov_one_position);
            } 
            number_and_name_buffer++;
        }
        inputFile.close();
    }
    else
    {
        throw "file did not open";
    }

    
    if (number_and_name_buffer<=1)
    {
        number_and_name_buffer = 2;
    }
    
    return number_and_name_buffer - 1;
}

//метод открывания потоков для каждого буфера
void Tape::read_buffers(int name_bufer) // не static 
{
    vector<ifstream> subFiles(name_bufer);
    for (int i = 0; i < name_bufer; ++i) 
    { 
        subFiles[i].open(to_string(i));  
    }
    Algorithm::mergeFile(name_number_buffer, &subFiles, file_name_output, this->w_delay,this->r_delay, this->moov_one_position);
} 

//метод открытия выходного файла
void Tape::write_sorted_data_in_outfile(string outFile, int number, double w_daley, double moov_one_position)
{
    ofstream outputFile(outFile, ios::app);
    if (outputFile.is_open())
    {
        Sleep(1000*w_daley);
        Sleep(1000*moov_one_position);
        // загрузка в выходный файл числа 
        outputFile << number << DELIMITER;
    }
    else
    {
        throw "file did not open";
    }
    outputFile.close(); 
}

// закрытие и удаление буферов
void Tape::close_and_removing_buffers(vector<ifstream> *subFiles, int number_and_name_bufer)
{
    for (int i = 0; i < number_and_name_bufer; ++i) 
    { 
            (*subFiles)[i].close(); 
            remove(to_string(i).c_str());
    }
}

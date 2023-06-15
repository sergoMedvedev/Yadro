#include "../inc/algorithm.hpp"
#include "../inc/tape.hpp"


//статический метод сортировки буферов
void Algorithm::sort_buffer(std::vector<int> *subData, int *j)
{
    sort((*subData).begin(), (*subData).begin() + *j + 1);
}

//метод слияния1
void Algorithm::mergeFile(int number_and_name_bufer, vector<ifstream> *subFiles, string file_out_name)
{   
    auto compare = [](pair<int, int>& a, pair<int, int>& b) 
    { 
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
        
        if (!(*subFiles)[minElem.second].eof()) 
        { 
            int number; 
            (*subFiles)[minElem.second] >> number; 
            pq.push({number, minElem.second}); 
        } 
    }
    Tape::close_and_removing_buffers(subFiles, number_and_name_bufer);
}

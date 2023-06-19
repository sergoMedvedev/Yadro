#include "../inc/interface.hpp"


Interface::Interface(std::string input, std::string output)
{
    this->name_file_input = input;
    this->name_file_output = output;
    this->make_duffers_for_sort();
}

void Interface::make_duffers_for_sort()
{
    ParsConfig parsCFG(PATH_CONFIG); 
    Tape input(name_file_input, &parsCFG);
    this->merging_buffers(input.name_number_buffer, &parsCFG);
}

void Interface::merging_buffers(int name_num_buffer, ParsConfig *parsCnf)
{
    Tape outFile(this->name_file_output, name_num_buffer, parsCnf);
}

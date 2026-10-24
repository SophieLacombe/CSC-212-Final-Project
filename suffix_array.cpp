#include "suffix_array.h"

#include <fstream>
#include <string>

SuffixArray::SuffixArray(const std::string& filename){ 

    std::ifstream in(filename);
    std::string line;

    // skip header
    getline(in, line);

    while (getline(in, line))
    {
        size_t commaPos = line.find(',');

        if (commaPos == std::string::npos)
        {
            continue;
        }

        std::string word = line.substr(0, commaPos);
        std::string definition = line.substr(commaPos + 1);

        text += word;
        text += '|';
        text += definition;
        text += '\n';
    }

    size = text.size();
    suffixes = new int[size];
    for(int i = 0; i<size; i++){
        suffixes[i] = i;
    }
}

SuffixArray::~SuffixArray(){
    delete[] suffixes;
}

void SuffixArray::build(){

}
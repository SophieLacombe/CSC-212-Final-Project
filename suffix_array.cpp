#include "suffix_array.h"

#include <fstream>
#include <string>

void SuffixArray::loadDictionary(const std::string& filename)
{
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
}
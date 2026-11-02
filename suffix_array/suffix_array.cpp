#include "suffix_array.h"

#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>

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

/*void SuffixArray::build()
{
    std::sort(suffixes, suffixes + size,
        [this](int a, int b)
        {
            return std::lexicographical_compare(
                text.begin() + a, text.end(),
                text.begin() + b, text.end()
            );
        });
}*/

void SuffixArray::build()
{
    std::vector<int> rank(size);
    std::vector<int> tempRank(size);

    // Initial ranking by character
    for (int i = 0; i < size; i++)
    {
        suffixes[i] = i;
        rank[i] = static_cast<unsigned char>(text[i]);
    }

    for (int k = 1; k < size; k *= 2)
    {
        std::cout << "Starting k = " << k << std::endl;
        std::sort(suffixes, suffixes + size,
            [&](int a, int b)
            {
                if (rank[a] != rank[b])
                {
                    return rank[a] < rank[b];
                }

                int rankA =
                    (a + k < size) ? rank[a + k] : -1;

                int rankB =
                    (b + k < size) ? rank[b + k] : -1;

                return rankA < rankB;
            });

        tempRank[suffixes[0]] = 0;

        for (int i = 1; i < size; i++)
        {
            int prev = suffixes[i - 1];
            int curr = suffixes[i];

            bool sameRank =
                rank[prev] == rank[curr];

            bool sameNextRank =
                ((prev + k < size) ? rank[prev + k] : -1) ==
                ((curr + k < size) ? rank[curr + k] : -1);

            if (sameRank && sameNextRank)
            {
                tempRank[curr] = tempRank[prev];
            }
            else
            {
                tempRank[curr] = tempRank[prev] + 1;
            }
        }

        rank = tempRank;

        // All suffixes have unique ranks
        if (rank[suffixes[size - 1]] == size - 1)
        {
            break;
        }
    }
}

void SuffixArray::save()
{
    // Save text
    std::ofstream textFile("text.csv");

    textFile << text;

    textFile.close();

    // Save suffix array
    std::ofstream suffixFile("suffixes.csv");

    suffixFile << "Index\n";

    for (int i = 0; i < size; i++)
    {
        suffixFile << suffixes[i] << '\n';
    }

    suffixFile.close();
}

int SuffixArray::getSize(){
    return size;
}
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
        entryStarts.push_back(text.size());

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


void SuffixArray::build()
{
    std::vector<int> rank(size);
    std::vector<int> tempRank(size);

    std::string lowerText = text;

    for (char& c : lowerText)
    {
        c = std::tolower(static_cast<unsigned char>(c));
    }

    // Initial ranking by character
    for (int i = 0; i < size; i++)
    {
        suffixes[i] = i;
        rank[i] = static_cast<unsigned char>(lowerText[i]);
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
    std::ofstream textFile("text.bin", std::ios::binary);

    size_t textSize = text.size();

    textFile.write(reinterpret_cast<char*>(&textSize),
                   sizeof(textSize));

    textFile.write(text.data(), textSize);

    textFile.close();

    std::ofstream suffixFile("suffixes.bin",
                             std::ios::binary);

    suffixFile.write(reinterpret_cast<char*>(&size),
                     sizeof(size));

    suffixFile.write(reinterpret_cast<char*>(suffixes),
                     size * sizeof(int));

    suffixFile.close();

    std::ofstream entryFile(
        "entry_starts.bin",
        std::ios::binary);

    size_t entryCount = entryStarts.size();

    entryFile.write(
        reinterpret_cast<char*>(&entryCount),
        sizeof(entryCount));

    entryFile.write(
        reinterpret_cast<char*>(entryStarts.data()),
        entryCount * sizeof(int));

    entryFile.close();
}

/*void SuffixArray::save()
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
}*/

int SuffixArray::getSize(){
    return size;
}
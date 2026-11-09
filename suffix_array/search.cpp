#include "search.h"

#include <fstream>
#include <algorithm>

Search::Search(const std::string& textFile,
               const std::string& suffixFile)
{
    // Load text
    std::ifstream textIn(textFile, std::ios::binary);

    textIn.seekg(0, std::ios::end);
    size_t textSize = textIn.tellg();
    textIn.seekg(0);

    text.resize(textSize);
    textIn.read(text.data(), textSize);

    // Load suffix array
    std::ifstream suffixIn(suffixFile, std::ios::binary);

    suffixIn.seekg(0, std::ios::end);
    size_t suffixSize = suffixIn.tellg();
    suffixIn.seekg(0);

    suffixes.resize(suffixSize / sizeof(int));

    suffixIn.read(
        reinterpret_cast<char*>(suffixes.data()),
        suffixSize
    );

    lowerText = text;

    for (char& c : lowerText)
    {
        c = std::tolower(static_cast<unsigned char>(c));
    }
}

std::vector<int> Search::find(const std::string& query)
{
    std::vector<int> results;

    int left = 0;
    int right = suffixes.size();

    while (left < right)
    {
        int mid = left + (right - left) / 2;

        int compare =
            lowerText.compare(
                suffixes[mid],
                query.size(),
                query
            );

        if (compare < 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }

    int start = left;

    while (start < suffixes.size())
    {
        if (lowerText.compare(
                suffixes[start],
                query.size(),
                query) != 0)
        {
            break;
        }

        results.push_back(suffixes[start]);
        start++;
    }

    return results;
}
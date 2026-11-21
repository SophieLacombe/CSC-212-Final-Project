#include "search.h"

#include <fstream>
#include <algorithm>
#include <unordered_set>


Search::Search(const std::string& textFile,
               const std::string& suffixFile,
               const std::string& entryFile)
{
    // Load text
    std::ifstream textIn(textFile, std::ios::binary);

    size_t textSize;
    textIn.read(
        reinterpret_cast<char*>(&textSize),
        sizeof(textSize));

    
    text.resize(textSize);

    textIn.read(
        text.data(),
        textSize);

    // Load suffix array
    std::ifstream suffixIn(suffixFile, std::ios::binary);

    int suffixCount;
    suffixIn.read(
        reinterpret_cast<char*>(&suffixCount),
        sizeof(suffixCount));

    
    suffixes.resize(suffixCount);

    suffixIn.read(
        reinterpret_cast<char*>(suffixes.data()),
        suffixCount * sizeof(int));

    // Load entry starts
    std::ifstream entryIn(entryFile, std::ios::binary);

    size_t entryCount;
    entryIn.read(
        reinterpret_cast<char*>(&entryCount),
        sizeof(entryCount));

    
    entryStarts.resize(entryCount);

    entryIn.read(
        reinterpret_cast<char*>(entryStarts.data()),
        entryCount * sizeof(int));

    // Create lowercase version of text
    lowerText = text;

    for (char& c : lowerText)
    {
        c = std::tolower(
            static_cast<unsigned char>(c));
    }
}

std::vector<int> Search::find(const std::string& query)
{
    std::string lowerQuery = query;

    for (char& c : lowerQuery)
    {
        c = std::tolower(static_cast<unsigned char>(c));
    }

    std::vector<int> results;

    int left = 0;
    int right = suffixes.size();

    while (left < right)
    {
        int mid = left + (right - left) / 2;

        int compare =
            lowerText.compare(
                suffixes[mid],
                lowerQuery.size(),
                lowerQuery
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
                lowerQuery.size(),
                lowerQuery) != 0)
        {
            break;
        }

        results.push_back(suffixes[start]);
        start++;
    }

    return results;
}

std::vector<Entry> Search::formatResults(
    const std::vector<int>& matches)
{
    std::vector<Entry> results;

    std::unordered_set<int> seenEntries;

    for (int matchPos : matches)
    {
        auto it = std::upper_bound(
            entryStarts.begin(),
            entryStarts.end(),
            matchPos);

        if (it == entryStarts.begin())
        {
            continue;
        }

        --it;

        int entryIndex =
            std::distance(
                entryStarts.begin(),
                it);

        if (seenEntries.find(entryIndex) != seenEntries.end())
        {
            continue;
        }

        seenEntries.insert(entryIndex);

        int start = entryStarts[entryIndex];

        int end =
            (entryIndex + 1 < entryStarts.size())
            ? entryStarts[entryIndex + 1]
            : text.size();

        std::string rawEntry =
            text.substr(start, end - start);

        size_t pipePos =
            rawEntry.find('|');

        if (pipePos == std::string::npos)
        {
            continue;
        }

        Entry entry;

        entry.word =
            rawEntry.substr(0, pipePos);

        entry.definition =
            rawEntry.substr(pipePos + 1);

        if (!entry.definition.empty() &&
            entry.definition.back() == '\n')
        {
            entry.definition.pop_back();
        }

        results.push_back(entry);
    }

    return results;
}
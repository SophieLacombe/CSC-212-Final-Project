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

    //load entry starts
    std::ifstream entryIn(entryFile, std::ios::binary);

    entryIn.seekg(0, std::ios::end);
    size_t entrySize = entryIn.tellg();
    entryIn.seekg(0);

    entryStarts.resize(entrySize / sizeof(int));

    entryIn.read(
        reinterpret_cast<char*>(entryStarts.data()),
        entrySize
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
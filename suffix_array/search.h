#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>

struct Entry
{
    std::string word;
    std::string definition;
};

class Search
{
public:
    Search(const std::string& textFile,
           const std::string& suffixFile,
           const std::string& entryFile);

    std::vector<int> find(const std::string& query);
    std::vector<Entry> Search::formatResults(const std::vector<int>& matches);
    
private:
    std::string text;
    std::string lowerText;
    std::vector<int> suffixes;
    std::vector<int> entryStarts;
};

#endif
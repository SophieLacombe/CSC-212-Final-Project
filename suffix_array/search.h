#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>

class Search
{
public:
    Search(const std::string& textFile,
           const std::string& suffixFile);

    std::vector<int> find(const std::string& query);

private:
    std::string text;
    std::string lowerText;
    std::vector<int> suffixes;
};

#endif
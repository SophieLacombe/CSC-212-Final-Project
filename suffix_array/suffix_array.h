#ifndef SUFFIX_ARRAY_H
#define SUFFIX_ARRAY_H

#include <string>
#include <vector>

class SuffixArray {
public:
    SuffixArray(const std::string& filename);
    ~SuffixArray();

    SuffixArray(const SuffixArray&) = delete;
    SuffixArray& operator=(const SuffixArray&) = delete;

    void build();
    //void search(const std::string& query);
    void save();

    int getSize();

    

private:
    std::string text;  // entire dictionary
    std::vector<int> entryStarts; //vector of definition starts
    int* suffixes;     // array of starting positions
    int size;          // number of suffixes
};

#endif
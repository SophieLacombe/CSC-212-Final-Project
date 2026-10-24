#ifndef SUFFIX_ARRAY_H
#define SUFFIX_ARRAY_H

#include <string>
#include <vector>

class SuffixArray {
public:
    SuffixArray(const std::string& filename);
    ~SuffixArray();

    void build();
    void search(const std::string& query);

    

private:
    std::string text;  // entire dictionary

    int* suffixes;     // array of starting positions
    int size;          // number of suffixes
};

#endif
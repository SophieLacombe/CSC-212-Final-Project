#include "suffix_array.h"
#include <iostream>

int main() {
    // use suffix array
    std::cout << "Starting\n";

    SuffixArray dictionaryArray("clean_dictionary.csv");

    std::cout << "Constructor finished\n";
    std::cout << dictionaryArray.getSize() << '\n';
    dictionaryArray.build();
    dictionaryArray.save();
}
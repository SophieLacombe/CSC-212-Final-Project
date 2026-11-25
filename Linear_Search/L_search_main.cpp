#include "L_search.h"
#include <iostream>
#include <chrono>

int main(){


    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Starting\n";

    L_search dic_array("clean_dictionary.csv");

    std::vector<int> matches = dic_array.find("zebra");

    std::cout << "Matches found: " << matches.size() << "\n";

    std::vector<Entry> results = dic_array.format_results(matches);

    std::cout << "Results found: " << results.size() << "\n";

    for(size_t i = 0; i < results.size(); i++){
        std::cout << results[i].word;
        std::cout << " | ";
        std::cout << results[i].definition;
        std::cout << "\n";
    }



    auto end = std::chrono::high_resolution_clock::now();


    std::chrono::duration<double> duration = end - start;

    std::cout << "\nExecution time: " << duration.count() << " milliseconds\n";

    
}
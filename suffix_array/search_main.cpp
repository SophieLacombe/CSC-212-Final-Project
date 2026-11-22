#include "search.h"
#include <iostream>
#include <chrono>

int main() {
    // use search
    std::cout << "Starting\n";

    auto start = std::chrono::high_resolution_clock::now();

    Search testSearch("text.bin", "suffixes.bin", "entry_starts.bin");

    std::cout << "Constructor finished\n";
    std::vector<int> resultInd =  testSearch.find("zEbRa");

    std::cout << "Searching...\n";

    std::cout << "Matches: " << resultInd.size() << '\n';

    std::cout << "Before formatResults\n";
    std::vector<Entry> entries = testSearch.formatResults(resultInd);
    std::cout << "After formatResults\n";

    std::cout << "Entries: " << entries.size() << '\n';

    for (const auto& entry : entries) {
        std::cout << "Printing entry\n";
        std::cout << entry.word << " " << entry.definition << '\n';
    }

    auto end = std::chrono::high_resolution_clock::now();


    std::chrono::duration<double> duration = end - start;

    std::cout << "\nExecution time: " << duration.count() << " milliseconds\n";


    std::cout << "Done\n";

    std::vector<int> newres = testSearch.find("a");
    std::cout << "Matches: " << newres.size() << '\n';
}
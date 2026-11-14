#include "search.h"
#include <iostream>

int main() {
    // use search
    std::cout << "Starting\n";

    Search testSearch("text.bin", "suffixes.bin", "entry_starts.bin");

    std::cout << "Constructor finished\n";
    std::vector<int> resultInd =  testSearch.find("zebra");

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

    std::cout << "Done\n";

    std::vector<int> newres = testSearch.find("a");
    std::cout << "Matches: " << newres.size() << '\n';
}
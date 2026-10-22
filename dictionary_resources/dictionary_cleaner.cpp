#include <fstream>
#include <sstream>
#include <string>

int main() {
    std::ifstream in("english_dictionary.csv");
    std::ofstream out("clean_dictionary.csv");

    std::string line;

    getline(in, line);        // skip header
    out << "word,definition\n";

    while (getline(in, line)) {
        std::stringstream ss(line);

        std::string word, pos, definition;

        getline(ss, word, ',');
        getline(ss, pos, ',');
        getline(ss, definition);

        if (definition.size() >= 2 && definition.front() == '"' && definition.back() == '"'){ 
            definition = definition.substr(1, definition.size() - 2);
        }

        if(!word.empty() || !definition.empty()){
            out << word << "," << definition << "\n";

        }

        
    }
}
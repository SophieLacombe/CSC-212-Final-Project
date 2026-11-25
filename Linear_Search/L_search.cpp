#include "L_search.h"

#include <fstream>
#include <unordered_set>
#include <iostream>



L_search::L_search(const std::string& textfile){

    std::ifstream in(textfile);
    std::string line;

    // skip header
    getline(in, line);

    while (getline(in, line))
    {
        size_t commaPos = line.find(',');

        if (commaPos == std::string::npos)
        {
            continue;
        }

        entrystarts.push_back(text.size());
        std::string word = line.substr(0, commaPos);
        std::string definition = line.substr(commaPos + 1);

        text += word;
        text += '|';
        text += definition;
        text += '\n';
    }

    text_size = text.size();



    lower_text = text;

    for (char& c : lower_text){
        c = std::tolower(static_cast<unsigned char>(c));
    }


    std::cout << "Text size: " << text.size() << "\n";
    std::cout << "Entries: " << entrystarts.size() << "\n";


}


std::vector<int> L_search::find(const std::string& input){
    std::vector<int> results;

    for(int i = 0; i < lower_text.size(); i++){
        if(lower_text[i] == input[0]){
            int occurance = i;
            bool match = true;
            for(int k = 1; k < input.size(); k++){
                if(lower_text[i + k] != input[k]){
                    match = false;
                    break;
                }
            }
            if (match){
                results.push_back(occurance);
            }
            
        }
    }

    return results;
  
 }

 std::vector<Entry> L_search::format_results(const std::vector<int>Matches){
    std::vector<Entry> results;
    std::unordered_set<int> seenEntries;

    for(int i = 0; i < Matches.size(); i++){
        for(int e = 0; e < entrystarts.size(); e++){
            int start = entrystarts[e];
            int end;
            if(e+1 < entrystarts.size()){
                end = entrystarts[e+1];
            }
            else{
                end = entrystarts.size();
            }
            if(Matches[i] >= start and Matches[i] < end){
                if(seenEntries.find(start) == seenEntries.end()){
                
                    std::string sub = text.substr(start,end - start);
                    size_t pipepos = sub.find("|");

                    if (pipepos == std::string::npos){
                        continue;
                    }


                    Entry entry;
                    
                    entry.word = sub.substr(0, pipepos);
                    entry.definition = sub.substr(pipepos + 1);

                    if (!entry.definition.empty() and entry.definition.back() == '\n'){
                        entry.definition.pop_back();
                    }


                    results.push_back(entry);
                    seenEntries.insert(start);
                }
            }
        }
    }
    
    return results;
 }
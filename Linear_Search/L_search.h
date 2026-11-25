#ifndef L_SEARCH_H
#define L_SEARCH_H

#include <string>
#include <vector>


struct LinearEntry
{
    std::string word;
    std::string definition;
};

class L_search{


    private:
        std::string text;
        std::string lower_text;
        size_t text_size;
        std::vector<int> entrystarts;



    public:
        L_search(const std::string& textfile);
        std::vector<int> find(const std::string& input);
        std::vector<LinearEntry> format_results(const std::vector<int>Matches);
        
    
};




#endif
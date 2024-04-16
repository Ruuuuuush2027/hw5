#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordle_helper(const string& in, string floating, const set<string>& dict, size_t emp, string curr, set<string>& target);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    
    set<string> target;

    // count number of empty spaces
    size_t emp = 0;
    for(size_t i = 0; i < in.size(); i ++){
        if(in[i] == '-')
            emp ++;
    }

    wordle_helper(in, floating, dict, emp, "", target);

    return target;
}

// Define any helper functions here
void wordle_helper(const string& in, string floating, const set<string>& dict, size_t emp, string curr, set<string>& target){
    if(emp < floating.size())
        return;
    else if(curr.size() == in.size()){
        if(dict.find(curr) != dict.end() && floating.empty())
            target.insert(curr);
    }
    else if(in[curr.size()] != '-')
        wordle_helper(in, floating, dict, emp, curr + in[curr.size()], target);
    else{
        emp --;
        for(int i = 0; i < 26; i ++){
            char c = char(97 + i);
            size_t loc = floating.find(c);
            if(loc != std::string::npos){
                floating.erase(loc, 1);
                wordle_helper(in, floating, dict, emp, curr + c, target);
                floating += c;
            } else{
                wordle_helper(in, floating, dict, emp, curr + c, target);
            }
        }
    }
}
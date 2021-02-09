// Alexsander Bairez
// CS 251 -- Project 2
// January 27, 2021
// Professor Reckinger
// No creative component

#pragma once

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

// cleans up string and turns all into lowercase
// use the ispunct and isalpha
// returns a clean string with no punct in front or end
string cleanToken(string s) {
    // checks if empty string
    // returns ""
        if (s.size() < 1){
            return "";
        }
        // my way of checking if string s is not alphabet string
        int count = 0;
        for(int i = 0; i < s.size(); i++){
            if(!isalpha(s.at(i))){
                count++;
            }
        }
        // if all string is not an alphabet, return ""
        if ( count == s.size()){
            return "";
        }
        
        // checks front for punctuation and deletes if so
        while(ispunct(s.at(0))){
            s.erase(s.begin());
        
        }
        // checks end for punctuation and deletes if so
        while(ispunct(s[s.size()-1])){
            s.erase(s.size()-1);
        
        }
        // turns strings s into lowercase
        for (int i= 0; i < s.size(); i ++){
           s.at(i) = tolower(s.at(i)); 

        }

        
    return s;
}

// uses sstream to break down text and store in set
// returns set 
set<string> gatherTokens(string text) {
    set<string> tokens;
    
    stringstream s(text);
    
    string word;
    
    while(s >> word){
        word = cleanToken(word);
        // makes sure that the word is not empty
        if(!word.empty()){
            tokens.insert(word); 
        }
    }
    return tokens;  
}

// parses through file and populates index
// returns int with the pages processed
int buildIndex(string filename, map<string, set<string>>& index) { 
    // key-> text && value-> URL
    ifstream infile;
    infile.open(filename);
    string key;
    string value;
    int word =0;
    
    if (!infile.is_open()){
        return 0;
     }
    // read input and fills in the index
    getline(infile,value);
    while(!infile.eof() && !infile.fail()){
        // makes sure that the value/ URL isn't empty
        // if empty, ignore
        if (value == ""){
            continue;
        }
        word++;
        //cout << value << endl;
        // use another getline to get text
        getline(infile,key);
        //cout << key << endl;
        // store the set of tokens
        set<string> tokens = gatherTokens(key);
        // making sure we dont have repeated keys in map
        for(auto t: tokens){
            index[t].insert(value);
        }
        getline(infile,value);
    }
    
    return word;
}

// creates the new set with updated URL's
// Used the set_union, referenced a youtube video by code_report
// used <iterator> since the functions require iterators
// returns set
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    set<string> temp;
    stringstream s(sentence);
    string word;
    int counter = 1;
    
    s >> word;
    word = cleanToken(word);    
    temp = index[word];
    
    while(s >> word){
        // makes sure first word gets added to set without checking for + or -
            if(word.at(0) == '-'){ // accounts for difference
            // use cleanToken() to get rid of '-'
                set<string> set; 
                word = cleanToken(word);
                for(auto x: temp){
                    if(index[word].count(x) == 0){
                        set.insert(x);
                    }
                }
                temp = set;
                result = temp;
                
            }
            else if(word[0] == '+'){ // acounts for intersection
            // use cleanToken() to get rid of '+'
                set<string> newSet;
                word = cleanToken(word);
                    for(auto x: index[word]){
                        if(temp.count(x) == 1){
                            newSet.insert(x);
                        }
                    }
                    temp = newSet;
                    result = temp;
                
            }else{ // accounts for union
                word = cleanToken(word);
                // using the set_union function from C++ library
                set_union(temp.begin(), temp.end(), index[word].begin(), index[word].end(), inserter(result, result.end()));
                temp = result;
              }
              counter++;
        }
        // checks to see if there was only a single word as input
        if( counter == 1){
            return temp;
        }

    return result; 
}

// searchEngine() builds the "search bar" 
// makes sure it follows proper layout
// returns void
void searchEngine(string filename) {
    map<string, set<string>> index;
    set<string> tokens;
    cout << "Stand by while building index..." << endl;
    int pages = buildIndex(filename, index);
    int unique = 0;
    int pageMatches = 0;
    string input;
    for(auto i : index){
        unique++;
    }
    cout << "Indexed " << pages << " pages containing " << unique << " unique terms" << endl;
    cout << endl;
    
    while(input != "\n"){
        cout << "Enter query sentence (press enter to quit): ";
        getline(cin, input);
        if(input.size() >= 1){
            tokens = findQueryMatches(index, input);
            for(auto t : tokens){
                pageMatches++;
            }
            pageMatches = tokens.size();
            cout << "Found " << pageMatches << " matching pages" << endl;
            for(auto x : tokens){
                cout << x << endl;
            }        
        }
        else if (input.size() == 0){
            cout << "Thank you for searching!";
            exit(0);
        }
        cout << endl;
    }
    
}



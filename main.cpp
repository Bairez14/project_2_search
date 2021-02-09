// Alexsander Bairez
// CS 251 -- Project 2
// Professor Reckinger
// January 27, 2021


#include <iostream>
#include "search.h"
#include <string>
#include <sstream>
#include <stdio.h>
#include <ctype.h>

using namespace std;

int main(){
// Main is used to check functions and make sure everything is working correctly

    //Milestone 1 ; Checks all edge cases
    //returns text
    string t = "...H.eL.lo... I am Alex...";
    string clean = cleanToken(t);
    string numbers = "98124";
    string clean2 = cleanToken(numbers);
    string upperCase = "WORLD";
    string clean3 = cleanToken(upperCase);
    
    
    if (t == "h.el.lo... i am alex"){
        cout << "Strings match" << endl;
    } else{
        cout << "Strings are messed up" << endl;
    }
    
    if (clean2 == ""){
        cout << "Strings match" << endl;
    } else{
        cout << "Strings are messed up" << endl;
    }
    
    if (clean3 == "world"){
        cout << "Strings match" << endl;
    } else{
        cout << "Strings are messed up" << endl;
    }
    
    cout << "Messy : " << t << endl;
    cout << "Clean: " << clean << endl;
    cout << "Messy : " << numbers << endl;
    cout << "Clean: " << clean2 << endl;
    cout << "Messy : " << upperCase << endl;
    cout << "Clean: " << clean3 << endl;
    
    // Milestone 2: Checks to make sure 
    // string is stored correctly in set
    // returns a set
    set<string> tokens = gatherTokens("to be or not to be");
    set<string> tokensANS = tokens;
    tokensANS.insert("to");
    tokensANS.insert("be");
    tokensANS.insert("or");
    tokensANS.insert("not");
    cout << "1. " << (tokensANS.size() == 4) << endl;
    cout << "2. " << (tokens == tokensANS) << endl;
    
    // Milestone 3: 
    map<string, set<string>> index;

    cout << buildIndex("tiny.txt" , index) << endl;
    for(auto e:index){
        cout << e.first << " --> ";
        for(auto x: e.second){
            cout << x << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    // Milestone 4:
    set<string> newS = findQueryMatches(index, "blue -fish bread +orange");
    
    // Milestone 5 
    searchEngine("tiny.txt");
    
    return 0;
}


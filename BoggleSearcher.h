#ifndef BOGGLESEARCHER_H_INCLUDED
#define BOGGLESEARCHER_H_INCLUDED

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct st { // A data structure which represents a step, with an affiliated location.
    st(int s, int m);
    int step;
    int location;
};

class BoggleSearcher { // A class to be used to search a board. A class contains a library (vector) of found words,
                        // a function to fill this vector, a function to print it, and a struct to resemble
                        // each word in the vector.
private:
    struct foundWord { // A data structure which represents each word found.
        // It contains a single word and the number of steps to reach the word.
        foundWord(string w, vector<st> s);
        string word; // This represents the string of the found word.
        vector<st> steps; // This represents the order of steps and locations for the found word.
        int instances; // This represents the number of times the word has appeared.
    };
    vector<foundWord> found;
public:
    void SearchForWord(vector<char> brd, int loc, string prog, vector<int> swept, vector<st> steps, Dictionary srch);
    void PrintFoundWords(vector<char> brd, bool showBoard);

};

#endif // BOGGLESEARCHER_H_INCLUDED

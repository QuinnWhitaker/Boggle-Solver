#include <iostream>
#include "dictionary.h"
#include "BoggleSearcher.h"
#include "otherFunctions.h"
#include <vector>
using namespace std;

int c2i(char c) { // Converts a lowercase letter to an integer from 0 to 25
    // returns -1 if a non-lowercase, non-alphabetical character was inputted
    // Pre: A character is given.
    // Post: An integer corresponding to the given character is returned.
    if (c == 'a') return 0;
    else if (c == 'b') return 1;
    else if (c == 'c') return 2;
    else if (c == 'd') return 3;
    else if (c == 'e') return 4;
    else if (c == 'f') return 5;
    else if (c == 'g') return 6;
    else if (c == 'h') return 7;
    else if (c == 'i') return 8;
    else if (c == 'j') return 9;
    else if (c == 'k') return 10;
    else if (c == 'l') return 11;
    else if (c == 'm') return 12;
    else if (c == 'n') return 13;
    else if (c == 'o') return 14;
    else if (c == 'p') return 15;
    else if (c == 'q') return 16;
    else if (c == 'r') return 17;
    else if (c == 's') return 18;
    else if (c == 't') return 19;
    else if (c == 'u') return 20;
    else if (c == 'v') return 21;
    else if (c == 'w') return 22;
    else if (c == 'x') return 23;
    else if (c == 'y') return 24;
    else if (c == 'z') return 25;
    else return -1;
}

char c2c(int i) { // Converts an integer to the corresponding lowercase letter, from the above function.
    // returns '@' if an int not between 0 and 25 was inputted.
    // Pre: An integer is given.
    // Post: The corresponding character to the given int, as defined by the function c2i, is returned.
    if (i == 0) return 'a';
    else if (i == 1) return 'b';
    else if (i == 2) return 'c';
    else if (i == 3) return 'd';
    else if (i == 4) return 'e';
    else if (i == 5) return 'f';
    else if (i == 6) return 'g';
    else if (i == 7) return 'h';
    else if (i == 8) return 'i';
    else if (i == 9) return 'j';
    else if (i == 10) return 'k';
    else if (i == 11) return 'l';
    else if (i == 12) return 'm';
    else if (i == 13) return 'n';
    else if (i == 14) return 'o';
    else if (i == 15) return 'p';
    else if (i == 16) return 'q';
    else if (i == 17) return 'r';
    else if (i == 18) return 's';
    else if (i == 19) return 't';
    else if (i == 20) return 'u';
    else if (i == 21) return 'v';
    else if (i == 22) return 'w';
    else if (i == 23) return 'x';
    else if (i == 24) return 'y';
    else if (i == 25) return 'z';
    else return '@';
}

Node::Node() {
    // Pre: A node's values have not been set yet.
    // Post: All of the node's pointers are set to nullptr, and all of its bools are set to false.
    for (int i = 0; i < 26; i++) {
        n[i] = nullptr;
        flag[i] = false;
    }
}

void Dictionary::init() {
    // Due to multiple constructors having almost identical bodies of code,
    // this function represents the body of code which they both share.
    // Pre: Dictionary is not initialized.
    // Post: Dictionary is initialized.
    numWords = 0;
    root = new Node;
}

void Dictionary::addWord(string line) { // This function adds the string argument to the dictionary.
    // Pre: The given string is not added to the dictionary
    // Post: The string is added to the dictionary. The number of words in the dictionary is incremented by 1.
    // If the inputted string isn't a word, the function returns.

    if (line.length() == 0) return;

    Node* curr = new Node; // This node will represent the node index as it goes through the branch pathway.
    curr = root; // It is first set to the root, as all words do.

    int i;
    for (i = 0; i < line.length(); i++) // For each letter in the given string
    {
        if (curr->n[c2i(line[i])] == nullptr) { // If the node path of the current letter is null,
            curr->n[c2i(line[i])] = new Node; // make a new node
        }
        curr = curr->n[c2i(line[i])]; // Whether or not a new node was made, set the node index to the next path associated with the current letter.
    }
    curr->flag[c2i(line[i-1])] = true; // Set the very last node's flag to true, to symbolize that this path is now defined as a word.

    numWords++; // increment the number of words in the dictionary.
}

Dictionary::Dictionary() { // Constructor #1. This does not take a string, this simply creates the dictionary.
    init();
}

Dictionary::Dictionary(string line) { // Constructor #2. This constructor creates the dictionary, then adds the string
                                    // argument as a word to the dictionary.
    init();
    addWord(line);
}

bool Dictionary::isPrefix(string line) {
    // Pre: A string is given, and we are unsure whether this arrangement of characters has a branch in our dictionary.
    // Post: If we have not reached a nullptr through navigating the designated characters, then this will return true,
    // otherwise this will return false.

    if (line.length() == 0) return false;

    Node* curr = root;

    for (int i = 0; i < line.length(); i++)
    {
        if (curr->n[c2i(line[i])] == nullptr) return false;
        curr = curr->n[c2i(line[i])];
    }
    return true;

    // Similarly to addWord, a node index is created to navigate the pathways. If at any point the path of the current letter is
    // false, we will know that this arrangement of letters hasn't been defined yet, and the function will stop to return false.
    // If no null pointers are found on the path, the function will return true.
}

bool Dictionary::isWord(string line) {
    // Pre: A string is given, and we are unsure whether it is in the dictionary.
    // Post: After searching the path similarly to addWord and isPrefix, if the end node's flag bool is true, we will return
    // true.

    if (line.length() == 0) return false;

    Node* curr = root;

    int i;
    for (i = 0; i < line.length(); i++)
    {
        if (curr->n[c2i(line[i])] == nullptr) return false;
        curr = curr->n[c2i(line[i])];
    }
    return curr->flag[c2i(line[i-1])];

    // Almost exactly similar to isPrefix, the only exception being that instead of automatically returning true at the end,
    // the state of the flag at the end node is instead returned. This is to ensure that the word has been
    // defined as a word in the dictionary, by means of the addWord function. (A piece of a defined word will return true
    // from isPrefix, but unless the entire pathway has been defined as a word, the function isWord will still return false.)
}

int Dictionary::wordCount() {return numWords;} // This function returns the number of words in the dictionary.

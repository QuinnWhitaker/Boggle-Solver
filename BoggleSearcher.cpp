#include <iostream>
#include "dictionary.h"
#include "BoggleSearcher.h"
#include "otherFunctions.h"
#include <vector>
using namespace std;

st::st(int s, int m) {
    step = s;
    location = m;
}

BoggleSearcher::foundWord::foundWord(string w, vector<st> s) {
    word = w;
    steps = s;
    instances = 1;
}

void BoggleSearcher::SearchForWord(vector<char> brd, int loc, string prog, vector<int> swept, vector<st> steps, Dictionary srch) {
    // Pre: Given a board, a location on the board, a string resembling the progress of a word being found,
    // a series of locations on the board that have already been scanned, a series of steps that have already been taken, and a dictionary
    // to search, this function will determine whether to recursively check this location to see if the character at this location on the board
    // is a part of the given dictionary.
    // Post: By the end of the function, the program will either deem this location not a prefix, in which case it stops, or it will check whether this
    // current progress is a word, in which case, if it is, it will add the word to the dictionary declared this class. It will then check to see which
    // locations have not been checked by this current chain, and recursively call this function to check those locations. If all locations have been checked,
    // the recursion stops.
    swept.push_back(loc); // Declaring the current location as already checked in this chain.
    prog += brd[loc]; // Adding the character to the current progress.
    if (!srch.isPrefix(prog)) return; // If our current path isn't a prefix to a word, then stop searching this location.
    int sz = steps.size();
    if (sz > 0) { // If there is 1 or more steps already in this chain,
        st newStep((steps[sz - 1].step + 1), loc);
        steps.push_back(newStep); // Make a new step using the current location, and the next step number, then add it to the step list.
    }
    else {
        st newStep(1, loc);
        steps.push_back(newStep); // Otherwise make a new step with the current location and step 1, then add it to the list.
    }
    if (srch.isWord(prog)) { // If our current path makes a word in our search dictionary, add the word to our found word vector.
        bool alreadyAdded = false; // bool to represent whether the word has already been added to the foundword vector.
        for (int i = 0; i < found.size(); i++) {
            if (prog == found[i].word) {
                alreadyAdded = true;
                found[i].instances++;
            }
        }
        if (!alreadyAdded) {
            foundWord f(prog, steps);
            found.push_back(f);
        }

    }

    vector<int> otherLocs = Positions(loc); // Declare the other locations to search based on the current location.
    bool alreadySwept;
    for (int i = 0; i < otherLocs.size(); i++) { // For each surrounding location
        alreadySwept = false;
        for (int i2 = 0; i2 < swept.size(); i2++) { // For every location that was already swept in this chain
            if (otherLocs[i] == swept[i2]) alreadySwept = true; // If the current surrounding location is found
            // in the swept vector, this location has already been swept in the chain.
        }
        if (!alreadySwept) { // If the location was NOT swept in the chain, begin recursion.
            SearchForWord(brd, otherLocs[i], prog, swept, steps, srch);
        }
    }
}

void BoggleSearcher::PrintFoundWords(vector<char> brd, bool showBoard) {
    // Pre: The current list of found words has yet to be printed.
    // Post: The function prompts the user to print the board or just the words. If just the words are printed,
    // They are printed numerically and without a board to show the pattern. If it is printed with a board,
    // The word, followed by how many words have been found, followed by how many times the word appeared,
    // followed by the board alignment of the first instance of this word, are each printed.
    // This process is repeated for every word found.
    for (int i = 0; i < found.size(); i++) { // For each word in the found vector
        if (!showBoard) {
                printFixedSpaces(i + 1, howManySpaces(found.size() - 1));
                cout << i + 1 << "        "; // If board is not being shown, print in the format "#        word"
        }
        else cout << "Word: "; // Otherwise print in the format "Word: word"
        cout << found[i].word << endl;
        if (showBoard) { // If board is being shown, then print "Number of words: #" followed by the board with steps.
            cout << "Number of words: " << i + 1 << endl;
            cout << "Number of times this word appears: " << found[i].instances << endl;

            int maxSpaces = howManySpaces(found[i].steps.size());

            int r = 0; // Index for row, resets to 0 each time the end of a row is reached.
            for (int i2 = 0; i2 < board_w*board_l; i2++) { // For each location on the board
                bool isStep = false; // Bool to determine whether the current location should be marked as a step.
                for (int i3 = 0; i3 < found[i].steps.size(); i3++) { // For every step in the current word
                    if (i2 == found[i].steps[i3].location) isStep = true; // If the current location on the board is a location of a step,
                    // then we'll mark this location as a step.
                }
                if (isStep) cout << "'";
                else cout << " ";
                cout << brd[i2];
                if (isStep) cout << "'";
                else cout << " ";
                r++;
                if (r%board_w == 0) { // If we've reached the right side of the board
                    cout << "        "; // Print a large gap to begin the affiliated row for the step numbers.
                    int pval;
                    for (int i3 = i2 - board_w + 1; i3 < i2 + 1; i3++) {
                        pval = 0;
                        for (int i4 = 0; i4 < found[i].steps.size(); i4++) {
                            if (i3 == found[i].steps[i4].location) pval = found[i].steps[i4].step;
                        }
                        printFixedSpaces(pval, maxSpaces);
                        if (pval == 0) cout << "-";
                        else cout << pval;
                        cout << "   ";
                    }
                    cout << endl;
                    r = 0;
                }
            }
            cout << "Press ENTER to continue." << endl;
            string input;
            getline(cin, input);
        }
    }
}

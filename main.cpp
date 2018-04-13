#include <iostream>
#include "dictionary.h"
#include "BoggleSearcher.h"
#include "otherFunctions.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

bool promptYesNo(string question, string input) {
    cout << question << " ";
    while (true) {
        getline(cin, input);
        if (input == "y") return true;
        else if (input == "n") return false;
        else cout << "Enter 'y' or 'n': ";
    }
}

int main()
{
    Dictionary d;

    ifstream myFile("dictionary.txt");
    string line;
    string input = "";
    vector <char> board;
    vector<st> steps;
    vector<int> sweep;
    string p = "";

    BoggleSearcher b;

    while (getline(myFile, line)) {
        d.addWord(line);
    }
    cout << "Loaded " << d.wordCount() << " words." << endl;

    bool manualBoard = promptYesNo("Enter board manually? (y/n)", input);

    if (!manualBoard) {
        srand (time(NULL));
        for (int i = 0; i < board_l * board_w; i++) board.push_back(c2c(rand() % 26));
    }
    else {
        cout << "Enter Board" << endl;
        cout << "-----------" << endl;
        cout << "(Enter " << board_w << " alphabetical letters per row, each separated by a space.)" << endl;
        for (int i = 0; i < board_l; i++) {
            while (true) {
                cout << "Row " << i << ": ";
                getline(cin, input);
                if (input.length() >= board_w * 2 - 1) {
                    bool isFormat = true;
                    for (int i2 = 0; i2 < input.length(); i2+= 2) {
                        if (!isAlph(input[i2]) || (input[i2 + 1] != ' ' && i2+1 != board_w * 2 - 1)) isFormat = false;
                    }
                    if (isFormat) {
                        for (int i2 = 0; i2 < input.length(); i2+= 2) {
                            board.push_back(input[i2]);
                        }
                        break;
                    }

                }
                cout << "Invalid format of row. Enter " << board_w << " letters, each separated by a space. " << endl;
            }
        }
    }

    cout << "Board: " << endl;
    for (int i = 0; i < board.size(); i++) {
        cout <<  " " << board[i] << " ";
        if (((i+1)%board_w) == 0) cout << endl;
    }

    for (int i = 0; i < board_w * board_l; i++) { // For each letter on the board
        steps.clear();
        sweep.clear();
        p = "";
        b.SearchForWord(board, i, p, sweep, steps, d);
    }
    b.PrintFoundWords(board, promptYesNo("Show board for each result? (y/n)", input));

}

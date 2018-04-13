#include <iostream>
#include "dictionary.h"
#include "BoggleSearcher.h"
#include "otherFunctions.h"
#include <vector>
using namespace std;

bool isAlph(char &c) {
// Pre: Given a character c, the function checks whether the character is alphabetical
// Post: If the character was an uppercase letter, it is converted to lowercase.
// If the character is a lowercase letter the function returns true, otherwise false.

    if (c == 'a' || c == 'b' || c == 'c' || c == 'd' ||
        c == 'e' || c == 'f' || c == 'g' || c == 'h' ||
        c == 'i' || c == 'j' || c == 'k' || c == 'l' ||
        c == 'm' || c == 'n' || c == 'o' || c == 'p' ||
        c == 'q' || c == 'r' || c == 's' || c == 't' ||
        c == 'u' || c == 'v' || c == 'w' || c == 'x' ||
        c == 'y' || c == 'z') return true;
    else if (c == 'A') {
        c = 'a';
        return true;
    }
    else if (c == 'B') {
        c = 'b';
        return true;
    }
    else if (c == 'C') {
        c = 'c';
        return true;
    }
    else if (c == 'D') {
        c = 'd';
        return true;
    }
    else if (c == 'E') {
        c = 'e';
        return true;
    }
    else if (c == 'F') {
        c = 'f';
        return true;
    }
    else if (c == 'G') {
        c = 'g';
        return true;
    }
    else if (c == 'H') {
        c = 'h';
        return true;
    }
    else if (c == 'I') {
        c = 'i';
        return true;
    }
    else if (c == 'J') {
        c = 'j';
        return true;
    }
    else if (c == 'K') {
        c = 'k';
        return true;
    }
    else if (c == 'L') {
        c = 'l';
        return true;
    }
    else if (c == 'M') {
        c = 'm';
        return true;
    }
    else if (c == 'N') {
        c = 'n';
        return true;
    }
    else if (c == 'O') {
        c = 'o';
        return true;
    }
    else if (c == 'P') {
        c = 'p';
        return true;
    }
    else if (c == 'Q') {
        c = 'q';
        return true;
    }
    else if (c == 'R') {
        c = 'r';
        return true;
    }
    else if (c == 'S') {
        c = 's';
        return true;
    }
    else if (c == 'T') {
        c = 't';
        return true;
    }
    else if (c == 'V') {
        c = 'v';
        return true;
    }
    else if (c == 'W') {
        c = 'w';
        return true;
    }
    else if (c == 'X') {
        c = 'x';
        return true;
    }
    else if (c == 'Y') {
        c = 'y';
        return true;
    }
    else if (c == 'Z') {
        c = 'z';
        return true;
    }
    else return false;

}

vector<int> Positions(int root) { // This function takes a position on the board (in vector/array form, 0-15 for a 16 element board),
    // and returns a vector of ints, each representing the surrounding spaces. For instance, entering 5 into this function will return
    // a vector with 0, 1, 2, 4, 6, 8, 9, 10 for a 16 element board. Entering 11 will return a vector with 6, 7, 10, 14, 15 for the same board.

    // Pre: A value of a space on the board vector is given.
    // Post: A vector containing all the surrounding spaces of the given location is returned, unless the given value is invalid.
    vector<int> ret; // The vector to be returned.

    if (root <= -1 || root >= board_l*board_w) {
        cout << "ERROR: Invalid root" << endl;
        ret.push_back(-1);
        return ret;
    }

    bool isTop = (root >= 0 && root < board_w);
    bool isLeft = (root % board_w == 0);
    bool isRight = ((root + 1) % board_w == 0);
    bool isBottom = (root >= board_w * board_l - board_w && root < board_w * board_l);
    // These four bools represent whether the given value is touching
    // the affiliated edges of the board, so as to not include the nonexistent values in those directions.

    if (!isRight) ret.push_back(root + 1); // East
    if (!isBottom && !isLeft) ret.push_back(root + board_w - 1); // Southeast
    if (!isBottom) ret.push_back(root + board_w); // South
    if (!isBottom && !isRight) ret.push_back(root + board_w + 1); // Southwest
    if (!isLeft) ret.push_back(root - 1); // West
    if (!isTop && !isLeft) ret.push_back(root - board_w - 1); // Northwest
    if (!isTop) ret.push_back(root - board_w); // North
    if (!isTop && !isRight) ret.push_back(root - board_w + 1); // Northeast

    return ret;


}

int howManySpaces(int x) {
    // Pre: Given an integer, printing size is unknown.
    // Post: Returns an int representing how many characters the given int takes up, for printing purposes.
    // if the int is zero, we'll know immediately that it only has one digit.
    if (x == 0) return 1;
    int r = 1; // The return value
    int t = 10; // This index will continuously multiply by ten until it is greater than or equal to x.
    // Each time it multiplies, r will be increased by 1.

    // If x is negative, the negative sign takes up one space, so increment r by one.
    // The algorithm that will be used however is only implemented by positive numbers, so multiply
    // x by -1.
    if (x < 0) {
        r++;
        x *= -1;
    }

    while (true) {
        if (x < t) return r;
        r++;
        t*=10;
    }
}

void printFixedSpaces(int x, int maxSpaces) {
    // Pre: Given a number, and a max number of spaces to print the number by.
    // Post: A number of spaces are printed to place next to a number that would be
    // coming afterwards. For instance, if we want 0 in three spaces, "  " would be
    // printed so that 0 could be printed afterwards to take a total of 3 spaces.

    int spaces = howManySpaces(x);

    if (spaces > maxSpaces) return;

    for (int i = 0; i < maxSpaces - spaces; i++) cout << " ";
}



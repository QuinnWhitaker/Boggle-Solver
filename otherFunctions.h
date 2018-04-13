#ifndef OTHERFUNCTIONS_H_INCLUDED
#define OTHERFUNCTIONS_H_INCLUDED

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const int board_w = 4;
const int board_l = 4;

bool isAlph(char &c);
vector<int> Positions(int root);
int howManySpaces(int x);
void printFixedSpaces(int x, int maxSpaces);

#endif // OTHERFUNCTIONS_H_INCLUDED

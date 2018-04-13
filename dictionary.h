#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int c2i(char c);
char c2c(int i);

struct Node {
	// Your data structure goes here
	Node();
    Node* n[26];
    bool flag[26];

};

class Dictionary
{
public:
	Dictionary();
	Dictionary(string file);
	void addWord(string word);
	bool isWord(string word);
	bool isPrefix(string word);
	int wordCount();

private:
	Node* root;
	int numWords;
	void init();
	// Any private methods you need/want
};

#endif // DICTIONARY_H_INCLUDED

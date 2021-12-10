#pragma once
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <map>
using namespace std;

// defining the class trie
class trie
{
public:
	// constructor
	trie()
	{
		// create the root node with null children and counters in zero
		root = new node();
	}

	// destructor
	~trie()
	{
		// destroying root node recursively (see destructor of node)
		if (root){
			delete root;
		root = NULL;
		}
	}

	// insert a word char by char into the trie
	// return true if the word was inserted successfully
	bool insert(const char* w)
	{
		// len of the word
		int len = strlen(w);
		if (len == 0)
			return false; // if its empty then there's nothing to do

		// start from root node
		node* p = root;
		for (int i = 0; i < len; i++)
		{
			// get the index of the char betwen 0 and 25
			int index = getIndex(w[i]);

			// if char not found in the expected range, then the word is not valid
			if (index == -1)
			{
				cout << "Invalid character " << w[i] << " in word: " << w << ". Word ignored!"<< endl;
				return false;
			}
			// if the child node does not exist, then create it with default values
			if (p->children[index] == NULL)
				p->children[index] = new node();

			// we have a new node in this branch
			p->keyLength++;

			// taking the corresponding child node
			p = p->children[index];

			// if it is the last char, then it is the end of the word (increase count)
			if (i == len - 1){
				p->count++;
			}
		}
		return true;
	}

	// search a word, char by char in the trie
	int search(const char* w)
	{
		// length of the string
		int len = strlen(w);

		// starting from root node
		node* p = root;

		// testing char by char
		for (int i = 0; i < len; i++)
		{
			// tasking the index of the i-th character
			int index = getIndex(w[i]);
			// if the char is not valid, then return zero (not found)
			if (index == -1){
				return 0;
			}
			// if there is nothing in the index position, then word not found
			if (p->children[index] == NULL){
				return 0;
			}
			// going one level deeper in the trie
			p = p->children[index];

		}
		// returning the number of words of type "word" that were already inserted in the trie
		return p->count;

	}

	// deleting one instance of the word w
	bool erase(const char* w)
	{
		// taking the length of the word
		int len = strlen(w);

		// if the length is zero, there is nothing to do
		if (len == 0){
			return 0;
		}

		// starting from root node
		node* p = root;

		// vector of pointers of the path between root node and last character of the word
		vector<node*> v;

		// traversing all the string chars
		for (int i = 0; i < len; i++)
		{
			// getting the index betwen 0 and 25
			int index = getIndex(w[i]);

			// if index is not in the alphabet
			if (index == -1){
				return false;
			}
			// including the node into the vector path
			v.push_back(p);

			// if the corresponding child node does not exist
			if (p->children[index] == NULL){
				return false;
			}
			// moving one level deeper in the trie, while moving one char deeper in the string
			p = p->children[index];
		}

		// if the counter in the last character of the string is zero, then word not found
		if (p->count == 0){
			return false;
		}

		// if there is at least 1 word identical to w in the trie, then decrease the counter by 1
		if (p->count > 0){
			p->count--;
		}
		// testing the path, node by node
		for (int i = len - 1; i > 0; i--)
		{
			// taking the index of the character, between 0 and 25
			int index = getIndex(w[i]);

			// taking the pointer to the corresponding node in the trie
			p = v[i];

			// of the brach rooted at index is empty
			//Two conditions, and the word must not exist more then once
			//this will fully delete the word from the trie, and there will no longer be
			//any instances of this word
			if (p->children[index]->keyLength == 0 && p->children[index]->count == 0){
				// we remove the branch
				delete p->children[index];

				// setting the pointer into NULL
				p->children[index] = NULL;

				// reducing the parent branch size
				p->keyLength--;
			}
		}

		// succcess
		return true;
	}

	void print(const char* filename){

		FILE* f = fopen(filename, "wt");
		fprintf(f, "graph {\n");
		for (int i=0; i<26; i++)
		if (root->children[i]){
			recursive_print(f, i+'A', root->children[i], 1, i);
	}

		fprintf(f, "}\n");
		fclose(f);
	}

private:

	// node of the trie
	class node
	{
	public:
		// public attribute: 27 children nodes
		node* children[27];

		// zero if it is not terminal, positive if it is terminal
		int count;

		// number of nodes in this branch
		int keyLength;

		// default constructor
		node()
		{
			// setting all children in NULL
			for (int i = 0; i < 26; i++)
				children[i] = NULL;

			// counters in zero
			count = 0;
			keyLength = 0;
		}

		// destructor
		~node()
		{
			// destroy each child recuersively
			for (int i = 0; i < 26; i++)
				if (children[i])
					delete children[i];

		}
	};

	// root pointer
	node* root;

	// return an index bettween -1 and 25
	//-1 means invalid
	int getIndex(char x)
	{
		int index = -1;
		if (x >= 'a' && x <= 'z')
			index = x - 'a';
		else if (x >= 'A' && x <= 'Z')
			index = x - 'A';
		return index;
	}

	void recursive_print(FILE* f, char a, node* p, int level, int j){
		for (int i = 0; i < 26; i++) {

		if(level == 1 && p->children[i] != NULL){
		    fprintf(f, "%s-- %c%d%d;\n", "trie", a, level , j);
		}

		if (p->children[i])
        {
			fprintf(f, "%c%d%d-- %c%d%d;\n", a, level , j, i + 'A', level + 1, j);

			fprintf(f, "%c%d%d [label=%c];\n", a, level,j, a);
			fprintf(f, "%c%d%d [label=%c];\n", i + 'A', level + 1, j, i + 'A');

            if (p->children[i]->keyLength == 0){
                fprintf(f, "%c%d%d [shape=box, color=red];\n", i + 'A', level + 1,j);

            }

			recursive_print(f, i + 'A', p->children[i], level + 1, j);
		}

	}
	}

};

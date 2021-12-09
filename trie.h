#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// defining the class trie
class trie
{
public:
	// constructor
	trie();

	// destructor
	~trie();

	// insert a word char by char into the trie
	// return true if the word was inserted successfully
	bool insert(const char* word);

	// search a word, char by char in the trie
	int search(const char* word);

	// deleting one instance of the word
	bool erase(const char* word);
	
	//prints output file for DOT file
	void print(const char* filename);


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
		node();

		// destructor
		~node();
	};

	// root pointer
	node* root;

	// return an index between -1 and 25
	int getIndex(char x);
	
	//recursive print function for DOT file
	void recursive_print(FILE* f, char a, node* p, int level, int j);

};
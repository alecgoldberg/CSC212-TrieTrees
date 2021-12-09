#include <string>
#include <fstream>
#include <cstring>
#include "trie.h"

// global variable trie
// Initializes the class we are using and created the variable so we can use it
trie tree;

// display the menu and return the user option
int menu()
{
	int option = 0;
	do
	{
		cout << "  1. Insert a new word" << endl;
		cout << "  2. Delete word (only 1 instance)" << endl;
		cout << "  3. Search word" << endl;
		cout << "  4. Quit" << endl;
		cout << "  Select an option -->";
		cin >> option;
		if (option == 1 || option == 2 || option == 3 || option == 4)
			break;
		cout << "Invalid option " << option << endl << endl;
	} while (true);
	return option;
}

// insert a user-defined word into the trie
void insertWord()
{
	// reading word
	string word;
	cout << "Enter a word: ";
	cin >> word;

	// inserting
	bool ret = tree.insert(word.c_str());
	if (ret)
		cout << "The word '" << word << "' was inserted in our trie" << endl;
	else
		cout << "The word '" << word << "' is not valid, and it was not inserted" << endl;
}

// delete a word from the trie
void deleteWord()
{
	// reading the word
	string word;
	cout << "Enter word: ";
	cin >> word;

	// calling erase
	bool erased = tree.erase(word.c_str());
	if (erased){
		cout << "The word '" << word << "' was erased from our trie" << endl;
	}
	else{
		cout << "The word '" << word << "' was not found in our trie" << endl;
	}

}

// search for a word in the trie and print the numer of instances of the word in the trie
void searchWord()
{
	// reading a word
	string word;
	cout << "Search a word: ";
	cin >> word;

	// searching
	int ret = tree.search(word.c_str());
	if (ret == 0){


		cout << "The word '" << word << "' was not found in our trie" << endl;
	}
	else{
		cout << "The word '" << word << "' has been inserted " << ret << " times in our trie " << endl;
	}
}

// main function
int main()
{

	// opening filename of words
	string filename;
	cout << "Enter filename: ";
	cin >> filename;

	ifstream file;
	file.open(filename);
	if (!file.is_open()){
		cout << "Error opening " << filename << endl;
		return 0;
	}

	// reading word by word
	string word;
	while (file >> word){
		cout << "Inserting " + word << endl;
		tree.insert(word.c_str());
	}

	// menu options
	do{
		int option = menu();
		if (option == 1){
				insertWord();
		}

		else if (option == 2){
				deleteWord();
		}
		else if (option == 3){
				searchWord();
		}

		else
			break;
	} while (1);
	
	tree.print("output.txt");


	return 0;

}
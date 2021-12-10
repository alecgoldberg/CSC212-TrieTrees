#include <string>
#include <fstream>
#include "trie.h"
#include <cstring>
// global variable trie
trie tree;

// display the menu and return the user option
int menu()
{
	int opc = 0;
	do
	{
		cout << "  1. Insert a new word" << endl;
		cout << "  2. Delete word (only 1 instance)" << endl;
		cout << "  3. Search word" << endl;
		cout << "  4. Quit" << endl;
		cout << "  Select an option -->";
		cin >> opc;
		if (opc == 1 || opc == 2 || opc == 3 || opc == 4){
			break;
		}
		cout << "Invalid option " << opc << endl << endl;
	} while (true);
	return opc;
}

// insert a user-defined word into the trie
void insertWord()
{
	// reading word
	string word;
	cout << "Enter a word -->";
	cin >> word;

	// inserting
	bool ret = tree.insert(word.c_str());
	if (ret){
		cout << "The word '" << word << "' was inserted in our trie" << endl;
	}
	else{
		cout << "The word '" << word << "' is not valid, and it was not inserted" << endl;
	}
}

// delete a word from the trie
void deleteWord()
{
	// reading the word
	string word;
	cout << "Enter the word to be deleted -->";
	cin >> word;

	// calling erase
	bool erased = tree.erase(word.c_str());
	if (erased){
		cout << "The word '" << word << "' was deleted from our trie" << endl;
	}
	else{
		cout << "The word '" << word << "' was not found in our trie" << endl;
	}
}

// search for a word in the trie and print the number of instances of the word in the trie
void searchWord()
{
	// reading a word input
	string word;
	cout << "Enter the word to be searched -->";
	cin >> word;

	// seraching for a word
	int ret = tree.search(word.c_str());
	if (ret == 0){
		cout << "The word '" << word << "' was not found in our trie" << endl;
	}
	else{
		cout << "The word '" << word << "' has been inserted " << ret << " times in our trie " << endl;
	}
}

int main()
{

	// opening filename of words
	string filename;
	cout << "Introduce filename--> ";
	cin >> filename;

	ifstream file;
	file.open(filename);
	if (!file.is_open()){
		cout << "Error opening " << filename << endl;
		return 0;
	}

	// reading input word by word
	string word;
	while (file >> word){
		cout << "Inserting " + word << endl;
		tree.insert(word.c_str());
	}

	// menu options
	do{
		int opc = menu();
		if (opc == 1){
			insertWord();
		}

		else if (opc == 2){
			deleteWord();
		}

		else if (opc == 3){
			searchWord();
		}

		else
			break;
	} while (1);

	tree.print("output.txt");

	return 0;


}

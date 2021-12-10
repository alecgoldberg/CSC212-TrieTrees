# CSC212-TrieTrees
University of Rhode Island CSC212 Final Project on Trie Trees
Tries, also known as prefix trees, are a special data structure that can be used to efficiently store and search strings. They are used to represent the “retrieval” of data hence the name “trie”. This data structure is a tree and therefore consists of an array of node pointers, each node having a maximum of 26 children. These 26 pointers represent the 26 letters of the English alphabet. Beginning with the child of the root node, a path can be made where each character in the string becomes the child of the character inserted before it. Tries have a time complexity of O(n) and are efficient because they allow for easy traversion through the branches. Some common applications of this data structure are predictive text, autocorrect, genome analysis, and many more.


# About Us
Group Members: 
-Alec Goldberg
-Bella Johnson
-Jake Villaincourt
-Gianna Nardini

# About our Project

Our project is an implementation of a Trie Tree. It can be compiled using to term "g++ main.cpp trie.h" in the terminal. 
The program takes in a .txt file a inserts the words in the file into the trie. A menu is provided to the user that allows 
them to manipulate the data; the user can insert a word, search a word, or erase a word. When the user selects to quit, the
program will end and produce an output file with code to be used for a DOT file visualization, this file will be named 
"output.txt".


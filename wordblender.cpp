#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include "wordblender.h"


unordered_map<string, int>dictionary;

//create a function that fills out a hashtable with words as keys and numbers that serve as index in table
void createhash(unordered_map<string, int>&dictionary) {
	//create chars for keys
	char a = 'a';
	char b = 'a';
	char c = 'a';
	char d = 'a';

	string wordd = "";
	int assigned = 0;

	//loop through columns to assign a number to each string 
	for (int y = 0; y < 456976; y++) {
		//word is been filled
		wordd.push_back(a);
		wordd.push_back(b);
		wordd.push_back(c);
		wordd.push_back(d);
		dictionary.insert({ wordd, assigned });
		//cout << wordd << "   " << assigned << endl;
		//increase variable
		if (d < 'z') {
			d++;
		}
		else if (c < 'z') {
			if (d == 'z') {
				d = 'a';
			}
			c++;
		}
		else if (b < 'z') {
			if (c == 'z') {
				c = 'a';
				d = 'a';
			}
			b++;
		}
		else if (a < 'z') {
			if (b == 'z') {
				b = 'a';
				c = 'a';
				d = 'a';
			}
			a++;
		}
		else {
			break;
		}
		wordd.clear();
		assigned++;
	}
	
}
// Constructs a Wordblender that creates blend words 
	// from those provided in the file. The file is promised
	// to have the following format:
	// 
	// word1
	// word2
	// ...
	// wordN
	//
	// where word1 < word2 < ... < wordN
	//
	// Must run in O(nk) time, where:
			// n is the number of words in the file
			// k equals max_word_count 
WordBlender::WordBlender(string filename, int max_word_count) {
	const int w = max_word_count;
	//create a table here
	//# of rows equal to the number given w using pointer given
	table = new string*[w];
	//create the columns for each row with a loop the size of w and as many columns as 26^4 = 456976
	for (int i = 0; i < w; i++) {
		table[i] = new string[456976];
	}
	

	//create an unordered map that stores the string and an assigned index 
	createhash(dictionary);
	vector<string> D;
	ifstream myfile;
	string line;
	//vector to store all words

	myfile.open(filename);
	if (!myfile.is_open())
	{
		cout << "File not open" << endl;
	}
	while (!myfile.eof()) {
		getline(myfile, line);
		if (line != "") {
			//add the word to the table!
			//create a string to save the word in the table
			string savew = "";
			savew = line.substr(0, 2);
			savew += line.substr(line.size() - 2, 2);
			//get the index number from dictionary
			int index = dictionary[savew];
			//save word in table
			table[1][index] = line;
			D.push_back(line);
		}
	}

	string wordx = "";
	//loop for each row
	for (int h = 2; h < w; h++) {
		//loop dictionary words
		for(int u=0; u < D.size(); u++) {
			wordx = D[u].substr(D[u].size() - 2);  //position
			//get index for the word +aa
			wordx += "aa";
			int indexx = dictionary[wordx];

			//third loop through all the possibilities in the table
			for (int k = 0; k < 677; k++) {
				int nindex = indexx + k;
				

				if (table[h - 1][nindex] != "" && D[u]!= table[h-1][nindex]) {
					string neww = D[u];
					neww += table[h - 1][nindex].substr(2);  //testing one parameter position
					string shortn = neww.substr(0, 2);
					shortn += neww.substr(neww.size() - 2, 2);
					nindex = dictionary[shortn];
					table[h][nindex] = neww;  //save word in table
					//cout << neww << endl;
				}

			}
		}
	}
}


// Returns a blend word that:
// -Starts and ends with the given words
// -Otherwise consists entirely of words found in filename
// -Consists of word_count total words.
//
// If no such blend word exists, returns "". 
// 
// Must run in O(1) time. 
string WordBlender::blend(string first_word, string last_word, int word_count) {
	if (word_count == 2) {
		//if its only 2 words merge those if compatible
		//get the end of first word
		string first = first_word.substr(first_word.size() - 2, 2);
		//get start of second word
		string last = last_word.substr(0, 2);
		//compare them
		if (first == last) {
			//if match return them merged
			string matched = first_word.substr(0,first_word.size() - 2);
			matched += last_word;
			return matched;
		}
		//else return ""
		else {
			return"";
		}
	}
	else {
		//if its only 2 words merge those if compatible
		//get the end of first word
		string lookup = first_word.substr(first_word.size() - 2, 2);
		//get start of second word
		lookup+= last_word.substr(0, 2);
		//get index number
		int indexN = dictionary[lookup];
		//check if word is there
		if (table[word_count-2][indexN] != "") {
			string finalword = first_word;
			//cout << table[word_count - 2][indexN] << endl;
			finalword += table[word_count-2][indexN].substr(2, table[word_count-2][indexN].size() - 2);
			finalword += last_word.substr(2, last_word.size() - 2);
			return finalword;
		}
		else {
			return"";
		}

		

	}

}


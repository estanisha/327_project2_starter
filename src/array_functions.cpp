/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
//	TODO add necessary includes here
//============================================================================
#include "array_functions.h"
#include "constants.h"
#include "utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur
using namespace std;
using namespace constants;

struct wordCount {
	string word = "";
	int count = 0;
};
//TODO add a global array of entry structs (global to this file)
struct wordCount arrayOfWords[MAX_WORDS];

//TODO add variable to keep track of next available slot in array
int nex = 0;

//TODO define all functions in header file

//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!

//zero out array that tracks words and their occurrences
void clearArray() {
	nex = 0;
	for (int i = 0; i < nex; i++) {
		arrayOfWords[i].word = "";
		arrayOfWords[i].count = 0;
	}
}

//how many unique words are in array
int getArraySize() {
	return nex;
}

//get data at a particular location
std::string getArrayWordAt(int i) {
	return arrayOfWords[i].word;
}
int getArrayWord_NumbOccur_At(int i) {
	return arrayOfWords[i].count;
}

/*Keep track of how many times each token seen*/ //might need to swap w processLine
void processToken(std::string &token) {
	bool used = false;
	if (strip_unwanted_chars(token)) {

		for (int i = 0; i < nex; i++) {
			string temps = arrayOfWords[i].word;
			string ttoken = token;

			toUpper(temps);
			toUpper(ttoken);

			if (temps == ttoken) {
				arrayOfWords[i].count++;
				used = true;
			}
		}
		if (!used) {
			arrayOfWords[nex].word = token;
			arrayOfWords[nex].count = 1;
			nex++;
		}
	}
	return;
}

/*take 1 line and extract all the tokens from it
 feed each token to processToken for recording*/
void processLine(std::string &myString) {
	stringstream ss(myString);
	string tempToken;

	while (getline(ss, tempToken, CHAR_TO_SEARCH_FOR)) {
		processToken(tempToken);
	}
}

/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/ //TODO finish method!!
bool processFile(std::fstream &myfstream) {
	if (!myfstream.is_open()) {
		return false;
	}

//	fstream myfile;
//	myfile.open(myfstream.c_str(), ios::out);

	string line;
	while (!myfstream.eof()) {
		getline(myfstream, line);
		processLine(line);
	}

//	myfile.closeFile();
	return true;
}

/*if you are debugging the file must be in the project parent directory
 in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream &myfile, const std::string &myFileName,
		std::ios_base::openmode mode) {
	myfile.open(myFileName.c_str(), mode);
	return myfile.is_open();
}

/*iff myfile is open then close it*/
void closeFile(std::fstream &myfile) {
	if (myfile.is_open()) {
		myfile.close();
	}

	return;
}

/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename) {
	if (nex == 0) {
		return FAIL_NO_ARRAY_DATA;
	}
	ofstream myfile;
	myfile.open(outputfilename.c_str(), ios::out);

	if (!myfile.is_open()) {
		return FAIL_FILE_DID_NOT_OPEN;
	}

	for (int i = 0; i < nex; i++) {
		myfile << arrayOfWords[i].word;
		myfile << " ";
		myfile << arrayOfWords[i].count;
		myfile << "\n";
	}

	myfile.close();

	return SUCCESS;
}

/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 */
void sortArray(constants::sortOrder so) {
	string tempA;
	string tempB;

	switch (so) {
	// There are more cases that are not covered here
	case sortOrder::ASCENDING:

		// goes through every possible pairing and compares and swaps
		for (int i = 0; i < nex - 1; i++) {
			for (int j = 0; j < nex - 1 - i; j++) {
				tempA = (arrayOfWords[j].word);
				tempB = arrayOfWords[j + 1].word;
				toUpper(tempA);
				toUpper(tempB);

				if (tempA > tempB) {
					wordCount temp = arrayOfWords[j];
					arrayOfWords[j] = arrayOfWords[j + 1];
					arrayOfWords[j + 1] = temp;
				}
			}
		}

		// test if it works
		for (int i = 0; i < nex; i++) {
			std::cout << arrayOfWords[i].word;
			std::cout << "\n";
		}
		break;
	}

}

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
void clearArray(){
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



/*Keep track of how many times each token seen*///might need to swap w processLine
void processToken(std::string &token) {
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

	/*fstream myfile;
	myfile.open(myfstream.c_str(),ios::out);

	while (myfile.eof()) {
		processLine("");
	}

	myfile.close();*/
	return true;
}

/*if you are debugging the file must be in the project parent directory
  in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode) {
	myfile.open(myFileName.c_str(), mode);
	return myfile.is_open();
}

/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile) {
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
	fstream myfile;
	myfile.open(outputfilename.c_str(),ios::out);

	if (!myfile.is_open()) {
		return FAIL_FILE_DID_NOT_OPEN;
	}

	while (myfile.eof()) {
		processFile(myfile);
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
	return;
}

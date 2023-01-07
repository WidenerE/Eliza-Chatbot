#include "Eliza.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>

//Constructor that takes in a file name
//Populates keyword and response vectors from file
Eliza::Eliza(string fileName)
{
	string inputLine;

	//Flags to control which type of input is read
	bool readResponse = false;
	bool readKeyword = false;

	//Temporary vectors
	vector<string> constructKeywordSet;
	vector<string> constructResponseSet;

	fstream inStream(fileName, ios::in);

	//Read file line by line
	while(getline(inStream, inputLine))
	{
		//Read responses
		if(inputLine == ":")
		{
			readResponse = true;
			readKeyword = false;
		}
		//Read keywords
		else if(inputLine == "#")
		{
			readKeyword = true;
			readResponse = false;
		}
		//Continue reading previous category
		else
		{
			if(readKeyword)
			{	//Finish the current response set and add it to the vector
				if(!constructResponseSet.empty())
				{			
					responses.push_back(constructResponseSet);
					constructResponseSet.clear();
				}
				
				//Begin constructing keyword set
				constructKeywordSet.push_back(inputLine);
			}
			else if(readResponse)
			{
				//Begin constructing response set
				constructResponseSet.push_back(inputLine);
			
				//Finish the current keyword set and add it to the vector
				if(!constructKeywordSet.empty())
				{
					keywords.push_back(constructKeywordSet);
					constructKeywordSet.clear();
				}
			}
		}
	}

	responses.push_back(constructResponseSet);
}

//Accesses and returns keyword vector
std::vector<vector<string>> Eliza::getKeywords()
{
	return keywords;
}

//Accesses and returns response vector
std::vector<vector<string>> Eliza::getResponses()
{
	return responses;
}

//Checks to see if word is noise
bool Eliza::isNoise(string word)
{
	return (noise.find(word) != noise.end());
	
}

//Uses an iterator to see if the given word is a keyword
//If no keyword is found to match, returns -1
//else returns the index of the first matching keyword
int Eliza::searchKeyword(string word)
{
	for(int i = 0; i < keywords.size(); i++)
	{
		auto iterator = find(keywords[i].begin(), keywords[i].end(), word);
	
		if(iterator != keywords[i].end())
			return i;
	}

	return -1;
}

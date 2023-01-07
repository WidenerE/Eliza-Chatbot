#ifndef Eliza_H
#define Eliza_H

#include <vector>
#include <set>
#include <string>

using namespace std;

class Eliza
{
	public:
		//Constructor that populates keyword and response vectors from a file
		Eliza(string);

		//Retrieves keywords
		vector<vector<string>> getKeywords();
		//Retrieves responses
		vector<vector<string>> getResponses();

		//Helps remove undesirble words from user input
		bool isNoise(string word);
		//Searches keyword vector for the given string
		int searchKeyword(string word);

	private:
		//Stores keywords grouped by category
		vector<vector<string>> keywords;
		//Stores responses grouped by category
		vector<vector<string>> responses;

		//Defines noise words
		set<string> noise = {
			    	 "this",
    				 "that",
     				 "take",
    				 "want",
    				 "which",
    				 "then",
    				 "than",
    				 "will",
     			       	 "with",
     				 "have",
    				 "after",
    				 "such",
    				 "when",
    				 "some",
    				 "them",
    				 "could",
    				 "make",
    				 "through",
    				 "from",
    				 "were",
    				 "also",
    				 "into",
    				 "they",
    				 "their",
    				 "there"
    				 
		};


};

#endif

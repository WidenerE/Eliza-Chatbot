#include "Eliza.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <bits/stdc++.h>

int main()
{	//File name
	string fileName = "dialogue.txt";
	//Keyboard input
	string input;

	//Tokenizes useer input word by word
	string word;
	//Retrieved response from external file 
	string response;
	//input after the keyword mirrored back to the user in some responses
	string mirrorInput;
	//Stores punctuation from responses that mirror input for concatenation
	string punctuation;

	//Create an Eliza object and run the constructor
	//The constructor reads in keywords and responses from the external file
	Eliza eliza(fileName);

	//Local copy of responses stored in eliza object
	vector<vector<string>> responses = eliza.getResponses();

	//seed for the random number generator
	srand(time(NULL));

	//Index of category of response
	int responseType;
	//Index of each individual response
	int responseIndex;

	//Flag to determine if a keyword was used
	bool keywordFound;

	cout << "The doctor is in." << endl << endl << "What's on your mind?" << endl << " - ";

	//Main program loop
	//Grabs a line of user input from keyword, tokenizies it, and looks for keywords
	//Prints to the screen an appropriate response
	while(getline(cin, input))
	{
		//Reduce string to lowercase
		transform(input.begin(), input.end(), input.begin(), ::tolower);

		//Create string stream to process each word
		stringstream ss(input);

		keywordFound = true;

		//Loop through each individual word
		while(ss >> word)
		{
			//End program if user types bye
			if(word == "bye")
				return 0;

			//First check to make sure the word is not "noise"
			if(!eliza.isNoise(word))
			{
				//Search through keyword list for the word
				//returns -1 if not found
				responseType = eliza.searchKeyword(word);
			
				if(responseType > 0)
				{
					//Choose a random response from the list based on keyword category
					responseIndex = rand() % responses[responseType].size();
					response = responses[responseType][responseIndex];

					//If there is an * in the response, splice user input after keyword and concatenate it
					if(response.at(response.length() - 2) != '*')
					{
						cout << endl << response << endl;
					}
					else
					{
						getline(ss, mirrorInput);

						punctuation = response.at(response.length() - 1);
					
						cout << endl << response.substr(0, response.length() - 3) << mirrorInput << punctuation << endl;
					}
					//If a keyword is found, stop searching for one
					keywordFound = true;
					break;
				}
				else
					keywordFound = false;
			}

		}

		//If a keyword was not found, pull a default response
		if(!keywordFound)
		{
			 responseIndex = rand() % responses[0].size();

                         cout << endl << responses[0][responseIndex] << endl;
		}

		cout << " - ";
	}
}

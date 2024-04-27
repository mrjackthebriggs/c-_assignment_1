
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "functions.h"

/*
source.cpp is for handling the algorithms behind the tasks in main.cpp
*/

using namespace std;
using namespace diclib;

/*
 Definitions for the Word object constructors.
*/
diclib::Word::Word(){}

diclib::Word::Word(string name, string type, string definition)
{
    this->name = name;
    this->type = type;
    this->definition = definition;
}


/*
    Uses a liniar search and points system to determine the closest fitting word
    If word is not found will return the closest word to it, can be used for word insertion.
    Takes a search word and a reference to a vector with Word objects, returns the words
    position in the vector as an int.
    Written by Jack Briggs on 19/03/23
*/
int findPos(string wordIn, vector<diclib::Word> &dictionary)
{
    int bestWordMatchPos{0};
    int bestWordMatch{1};
   
    for(int i = 0; i < dictionary.size(); i++)
    {
        int wordMatchPoints{0};

        for(int j = 0; j < wordIn.size() && j < dictionary[i].name.size(); j++)
        {
            if(wordIn[j] == dictionary[i].name[j])
            {
                wordMatchPoints++;
            }
            else
            {
                break;
            }
        }

        if(wordMatchPoints > bestWordMatch)
        {
            bestWordMatch = wordMatchPoints;
            bestWordMatchPos = i;
        }
    }

    return bestWordMatchPos;
}


/* for making all input lowercase.
   Takes a string pottentially in uppercase and returns a string completely in lower case.
   Written by Jack Briggs on 19/03/23 */
string diclib::makeLowerCase(string wordtoConvert)
{
    for(int i = 0; i < wordtoConvert.size(); i++)
    {
        if(wordtoConvert[i] >= 65 && wordtoConvert[i] <= 90)
        {
            wordtoConvert[i] += 32;
        }
    }

    return wordtoConvert;
}


/* Made to decode the word type syntax and return the propper output for printing
   takes the string from the dictionary file and returns a string with the full name of what it is.

   The else at the bottom allows this method to have a second use, if an invalid word type is input durring the addWord()
   process, it will return an empty string, for determining if the input word type is valid or not

   Witten by Jack Briggs on 19/03/23 */
string diclib::decodeType(string wordType)
{
    if(wordType == "n")
    {
        return (string)"noun";
    }
    else if(wordType == "v")
    {
        return (string)"verb";
    }
    else if(wordType == "adv")
    {
        return (string)"adverb";
    }
    else if(wordType == "adj")
    {
        return (string)"adjective";
    }
    else if(wordType == "prep")
    {
        return (string)"preposition";
    }
    else if(wordType == "misc")
    {
        return (string)"miscellaneous";
    }
    else if(wordType == "pn")
    {
        return (string)"proper noun";
    }
    else
    {
        return (string)"";
    }

}

/*TASK 1: Loads in the dictionary file and reads line by line, if "<word>" is read,
    Reads the next 3 lines, will skip any remaining lines untill "</word>" is read
    Takes a file path string and a reference to the vector<Word> dictionary.
    Returns the number of words found as an integer
    Written by Jack Briggs on 15/03/23*/
int diclib::loadDictionary(string dictPath, vector<Word> &dictionary)
{
    ifstream dictFile(dictPath);
    string lineBuffer;
    int wordsFound = 0;
    
    // Clears dictionary, for when loading a new dictionary into the program
    dictionary.clear();

    if(dictFile.is_open())
    {
        while (!dictFile.eof())
        {     
            getline(dictFile, lineBuffer);

            // if line starts with "<word>" create a new word object and read following values
            if (lineBuffer.substr(0,6) == "<word>")
            {
                Word newWord{};

                getline(dictFile,newWord.name);
                getline(dictFile,newWord.definition);
                getline(dictFile,newWord.type);

                // ignore each line after untill "</word>" is read
                while(lineBuffer.substr(0,7) != "</word>")
                {
                    getline(dictFile, lineBuffer);

                    // Just in case end of file is reached
                    if(dictFile.eof())
                    {
                        break;
                    }
                }
                // when detected, add to dictionary
                dictionary.push_back(newWord);

                wordsFound++;
            }
        }
        dictFile.close();
    }

    return wordsFound;
}


/*TASK 2: finds a word (searchWord) in a Word vector (called dictionary). 
    Uses findPos, to find the position of the Word object in the dictionary vector.
    Takes a string with the search word and a reference to a Word vector (dictionary) to search in.
    returns the words position as an int, if no word is faound, returns -1.
    Written by Jack Briggs on 19/03/23 */
int diclib::findWord(string searchWord, vector<Word> &dictionary)
{
    int searchWordPos = findPos(searchWord, dictionary);

    if(0 == dictionary[searchWordPos].name.compare(searchWord))
    {
        return searchWordPos;
    }
    else
    {
        return -1;
    }
}


/*
TASK 3: Finds words in a Word vector object (dictionary) with more than 3 z's
Takes a reference to a Word vector, returns a Word vector of words it found.
Written by Jack Briggs on 19/03/23
*/
vector<string> diclib::zzzWords(vector<diclib::Word> &dictionary)
{
    vector<string> zzzWords{};

    for(Word word : dictionary)
    {
        int zzzCounter{};
        for(char a : word.name)
        {
            if(a == 'z')
            {
                zzzCounter++;
            }
        }

        if(zzzCounter > 3)
        {
            zzzWords.push_back(word.name);
        }
    }

    return zzzWords;
}


/*TASK 4: Adds a word to a pre-existing Word vector (dictionary) and saves it to a new file
Takes a Word object, reference to a Word vector and the potential files name.
returns the number of words written to the file as an int.
Written by Jack Briggs on 21/03/23 */
int diclib::addWord(Word word, vector<diclib::Word> &dictionary, string savePath)
{
    // For finding where the word would be if it was in the dictionary (Keeps it organised)
    int wordPos = findPos(word.name, dictionary) + 1;

    dictionary.insert(dictionary.begin() + wordPos,word);

    // Put that in a new file, babee
    ofstream dictFile(savePath, ios::app);
    int wordCount{};

    for(int i = 0; i < dictionary.size(); i++)
    {
        dictFile << "<word>" << endl;
        dictFile << dictionary[i].name << endl;
        dictFile << dictionary[i].definition << endl;
        dictFile << dictionary[i].type << endl;
        dictFile << "</word>" << endl;
        wordCount++;
    }

    return wordCount;
}
//Functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>

using namespace std;

namespace diclib
{
    /*
    Word holds 3 properties for the word itslef, its type and its definition
    Written by Jack Briggs on 04/03/23
    */
    struct Word
    {
        string name;
        string type;
        string definition;
        Word();
        Word(string name, string type, string definition);
    };

    //Prototypes for definitions in functions.cpp
    string makeLowerCase(string wordtoConvert);

    string decodeType(string type);

    int loadDictionary(string dictPath, vector<Word> &dictionary);

    int findWord(string word, vector<Word> &dictionary);

    vector<string> zzzWords(vector<Word> &dictionary);

    int addWord(Word word, vector<Word> &dictionary, string savePath);
}
#endif
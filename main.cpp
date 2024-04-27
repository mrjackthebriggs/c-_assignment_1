
#include <iostream>
#include <string>
#include <vector>
#include "functions.h"
#include <limits>

/*
main.cpp is used for the main loop and display of the app, this will handle user inputs and what is prin ted to console
*/

using namespace std;

const string DEFAULT_DICTIONARY = "dictionary_2023S1.txt"; 

int main()
{
    int inputChoice;
    vector<diclib::Word> dictionary;
      
    //Displays a menu of 4 tasks
    cout << "|             Welcome to Dictionary Manager Xtreme            |" << endl;

    //Loops menu while inputChoice has a value between 1-4
    do
    {
        cout << "\nPlease pick a task by inputing its coresponding number:" << endl;
        cout << "1) Load a custom or default dictionary" << endl;
        cout << "2) Find a word in the loaded dictionary" << endl;
        cout << "3) Find words with more than 3 z's in the loaded dictionary" << endl;
        cout << "4) Add a word to the loaded dictionary" << endl;
        cout << "0) to exit\n" << endl; 

        cin >> inputChoice;

        // stole this from : https://stackoverflow.com/a/10553849
        // removes the newline from the buffer of the previous cin, allows the use of getline()
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');

        
        if(inputChoice == 0)
        {
            cout << "0 : Exit Program" << endl;
            cout << "Thank you for using:\n" << endl;
            cout << "|      Dictionary Manager Xtreme      |\n\n" << endl;
        }

        else if(inputChoice == 1)
        {
            cout << "1 : Load Dictionary Selected" << endl;
            cout << "Please input a dictionary file path (with file type at the end), put in \"default\" to select the default dictionary file" << endl;
            
            std::string dictSel;
            int wordsFound;

            getline(cin,dictSel);

            if(dictSel == "default")
            {
                dictSel = DEFAULT_DICTIONARY;
            }
            
            wordsFound = diclib::loadDictionary(dictSel, dictionary);
            cout << wordsFound << " Words loaded into the dictionary" << endl;
        }

        else if(inputChoice == 2)
        { 
            cout << "2 : Word Search Selected" << endl;
            // Check if dictionary is loaded
            if(dictionary.size() != 0)
            {
                string searchWord; 
                cout << "please input a word to search for: " << endl;
                getline(cin, searchWord);

                // finds position of searched for word using findWord in source.cpp
                int returnedWordPosition = diclib::findWord(diclib::makeLowerCase(searchWord),dictionary);

                if (returnedWordPosition == -1)
                {
                    cout << "\nWord not found!\n";
                }
                else
                {
                    cout << endl;
                    cout <<"Word Found! " << endl;
                    cout << dictionary[returnedWordPosition].name << endl;
                    cout << "[" << diclib::decodeType(dictionary[returnedWordPosition].type) << "]"<< endl;
                    cout << dictionary[returnedWordPosition].definition << endl;
                } 
            }
            else
            {
                cout << "No dictionary loaded, please load a dictionary with option 1" << endl;
            }

            
        }

        else if(inputChoice == 3)
        {    
            cout << "3 : ZZZ Word Search Selected" << endl;
            // Check if dictionary is loaded
            if(dictionary.size() != 0)
            {
                vector<string> zzzWords{};

                zzzWords = diclib::zzzWords(dictionary);

                if(zzzWords.size() != 0)
                {
                    cout << zzzWords.size() <<" ZZZ words found: " << endl;
                    for(string zzzWord : zzzWords)
                    {
                        cout << "\t> " << zzzWord << endl;
                    }
                }

                
            }
            else
            {
                cout << "No dictionary loaded, please load a dictionary with option 1" << endl;
            }
        }

        else if(inputChoice == 4)
        {
            cout << "4 : Add Word to Dictionary Selected" << endl;
            // Check if dictionary is loaded
            if(dictionary.size() != 0)
            {
                string newName{};
                bool overWrite{};
                cout << "Please input the word you would like to add: " << endl;
                getline(cin, newName);

                // Check if new word already exists, else returns to top of loop
                int namePos = diclib::findWord(diclib::makeLowerCase(newName), dictionary);

                if(namePos != -1)
                {
                    cout << "error: word exists, elevated privileges required to edit existing words" << endl; 
                    continue;                
                }
               
                // checking if input word type is valid, if a blank string is returned then it is an invalid type
                string typeInp{};
                cout << "\nWhat type of word is it? Input: " << endl;
                cout << "\"n\" for a noun" << endl;
                cout << "\"v\" for a verb" << endl;
                cout << "\"adv\" for an adverb" << endl;
                cout << "\"adj\" for an adjective" << endl;
                cout << "\"prep\" for a preposition" << endl;
                cout << "\"misc\" for miscellaneous" << endl;
                cout << "\"pn\" for a proper noun" << endl;
                
                getline(cin, typeInp);

                string typeRet = diclib::decodeType(typeInp);

                if(typeRet == "")
                {
                    cout << "\ninvalid word type, please try again" << endl;
                    continue;
                }

                // All checks are done, get definition of the word and where the new dictionary file is to be saved

                string defInp{};
                cout << "\nWhat is the definition of this word?:" << endl;
                getline(cin,defInp);

                string savePath{};
                cout << "\nWhat would you like to name the new dictionary file (with file type at the end)?:" << endl;
                getline(cin,savePath);

                // Now we have all our info, make the word object using a constructor and give it to addWord()
                diclib::Word newWord{newName, typeInp, defInp};

                int wordCount = diclib::addWord(newWord, dictionary, savePath);

                cout << wordCount << " words successfully written to " << savePath << endl;
            }
            else
            {
                cout << "No dictionary loaded, please load a dictionary with option 1" << endl;
            }
        }

        else if(inputChoice >= 5 || inputChoice < 0)
            cout << "Please input a value between 0 - 4\n" << endl;
            continue;                
        
    }
    while(inputChoice != 0);

    return 0;
}
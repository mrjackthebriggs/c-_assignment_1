# C++ Dictionary (Assignment 1)
This was submitted as the first assignment for a university unit: Object-oriented C++. This assignment scored a perfect mark, 30/30. This sets up everything for assignment 2. This project was redone in rust, which is another one of my public repos

## The brief for this assignment was:

Write a program that when executed will display a menu of tasks it can perform. The program will then prompt the user to enter a number corresponding to a set task to perform. Each task should be implemented in a separate function and once complete the menu should be displayed again so that the user can choose another task to be performed. The tasks are described as follows:

### Task 01
Load and Parse a dictionary file. First ask the user to either enter the file name or use the ‘default’ file, that being dictionary_2023S1.txt, provided with this assignment (See Appendix at the end of this document for file layout). Your program will load the information for each word (name, type and definition) from the file into a new instance of a Word struct (details of this struct provided after description of tasks) and add this instance to a STL vector of Words called Dictionary.

General Functionality of Task 02 onwards
Each task to be implemented as a function that receives the Dictionary STL vector as input. If no dictionary is loaded the task should just print ‘No dictionary loaded’ and return to the menu, otherwise the functionality should be as follows:

### Task 02
Prompt the user to enter a word. If that exact word is in the dictionary, print the word’s name, followed on the line directly below by the word type using the scheme in Table 1, and on the line below the type print the word’s definition.

If the word is not in the dictionary print ‘word not found.’

Table 1: Print the word type using this scheme.
Word type:      |   To be printed to the console:
Noun            |   [noun]
Verb            |   [verb]
Adverb          |   [adverb]
Adjective       |   [adjective]
Preposition     |   [preposition]
Miscellaneous   |   [miscellaneous]
Proper Noun     |   [proper noun]
Noun and Verb   |   [noun and verb]

### Task 03
Find (and print to the screen) all words that contain more than three ‘z’ characters in them.

### Task 04
Add a word to the dictionary. Allow the user to enter the name, type and definition of a word. If the word is already in the dictionary, the program should print ‘error: word exists, elevated privileges required to edit existing words’. If the word is not in the dictionary, and providing a valid ‘type’ is entered – create a corresponding Word struct instance and add it to the Dictionary STL vector.

Following the successful addition of the word, save the Dictionary to a new file (file name specified by the user), in the same format as the original dictionary file (so that it can be read using Task 01).

Program architecture for Assignment 1
    • Create a 'Word' struct to hold each word, with fields: 
        ◦ name (string) The word in the dictionary
        ◦ type (string)
        ◦ definition (string)
    • The main function should declare an STL Vector of Word instances.
    • Each task should be performed in a function outside of the main function.

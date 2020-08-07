/*
Written by: David Liu
Inception: 8/6/2020
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

#include "hangman.h"

typedef std::string str;

// creates a duplicate phrase with all the letters hidden
void EmptyPhraseMaker(const str& phrase, str& dynPhrase)
{
    for (int i = 0; i < phrase.size(); i++)
    {
        if (isalpha(phrase[i]))
            dynPhrase += "*";
        else
            dynPhrase += phrase[i];
    }
}

// checks if a letter exists in a phrase and reveals them accordingly
bool checkPhrase(const str& phrase, str& answer, const str& letter)
{
    bool checkFlag = false;
    for (int i = 0; i < phrase.size(); i++)
    {
        if (tolower(letter[0]) == tolower(phrase[i]))
        {
            answer[i] = phrase[i];
            checkFlag = true;
        }
    }
    return checkFlag;
}

// prints out the values of a set containing used letters
std::string printUsed(const std::set<char>& letters)
{
    std::string s;
    for (std::set<char>::iterator s_itr = letters.begin(); s_itr != letters.end(); s_itr++)
        s += *s_itr;

    return s;
}



int main(int argc, char** argv)
{
    /* ARGUMENT PARSING */
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " [phrase]" << std::endl;
        return -1;
    }

    str p = argv[1];
    str answer;
    EmptyPhraseMaker(p, answer);

    /* TURN LOOP */
    int turn = 0, mistakes = 0;
    str token;
    std::set<char> used;
    std::cout << "Turn " << turn << "\n" << answer << "\nMistakes: 0\n" << "Used:" << std::endl;
    
    while (true)
    {   
        turn++;
        std::cout << ">>> ";
        std::cin >> token;

        if (token == "quit") 
        {
            break;
        }
        // check if token is a letter guess
        else if ( token.size() == 1 && isalpha(token[0]) )
        {   
            // check if letter has already been used
            if ( !used.insert(toupper(token[0])).second )
            {
                std::cout << "You've already used that letter! Pick another one!" << std::endl;
                turn--; continue;            
            }
            // check if letter exists in the answer
            else if ( !checkPhrase(p, answer, token) ) 
                mistakes++;
        }
        // query is invalid, redo the turn
        else
        {   
            std::cout << "Unknown query '" << token << "'" << std::endl;
            turn--;
        }

        std::cout << "\nTurn " << turn << "\n" << answer << std::endl;
        std::cout << "Mistakes: " << mistakes << std::endl;
        std::cout << "Used: " << printUsed(used) << std::endl;

        // check if the answer has been guessed
        if (answer == p)
        {
            std::cout << "You did it!" << std::endl;
            break;
        }
    }

    return 0;
}
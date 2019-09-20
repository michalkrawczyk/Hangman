//
// Created by MK on 17.09.2019.
//

#ifndef HANGMAN_CONFIGURATION_H
#define HANGMAN_CONFIGURATION_H

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#ifdef DEBUG
    #include <iostream>
#endif



namespace dictionary
{
    class Configuration;
    std::string getPath();
}



class dictionary::Configuration {
    unsigned int _min_length , _max_length;
    std::vector<std::wstring> _word_list;

public:
    Configuration();
    void loadWords(const std::string &path = dictionary::getPath());
    //Todo:Rethink Constructor and loadWords

    unsigned int getMinWordLength() const;
    unsigned int getMaxWordLength() const;
    const std::vector<std::wstring> &getWordList() const;
};


#endif //HANGMAN_CONFIGURATION_H

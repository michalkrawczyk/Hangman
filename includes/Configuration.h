//
// Created by MK on 17.09.2019.
//

#ifndef HANGMAN_CONFIGURATION_H
#define HANGMAN_CONFIGURATION_H

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#ifdef _DEBUG
    #include <iostream>
#endif



namespace dictionary
{
    class Configuration;
    std::string getPath();
}



class dictionary::Configuration {
    unsigned int m_min_length , m_max_length;
    std::vector<std::wstring> m_word_list;

public:
    explicit Configuration(const std::string &path = dictionary::getPath());
    void loadWords(const std::string &path = dictionary::getPath());

    unsigned int getMinWordLength() const;
    unsigned int getMaxWordLength() const;
    const std::vector<std::wstring>& rGetWordList() const;
};


#endif //HANGMAN_CONFIGURATION_H

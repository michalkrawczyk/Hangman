//
// Created by MK on 17.09.2019.
//

#include "Configuration.h"


std::string dictionary::getPath()
{
    static const std::string path("../data/Dictionary");
    return path;
}

dictionary::Configuration::Configuration():
    _min_length(0),
    _max_length(0)
{
    loadWords(dictionary::getPath());
}

void dictionary::Configuration::loadWords(const std::string &path) {

    std::wifstream file(path.c_str());


    if (!_word_list.empty())
    {
        _word_list.clear();
    }

    #ifdef DEBUG
    std::cout<<"Reading Configuration File (" << path << ") - ";
    std::cout<<"File open:"<<file.is_open()<<", good:"<<file.good()<<std::endl;
    #endif

    if(file.is_open() && file.good())
    {
        std::wstring word;
        std::getline(file,word);

        while(!file.eof())
        {
            std::getline(file, word);

            if (_min_length == 0)
            {
                _min_length = word.length();
            }
            else
            {
                _min_length = std::min(_min_length, word.length());
            }

            _max_length = std::max(_max_length, word.length());

            _word_list.push_back(word);
        }

        if (_min_length == 0 || _max_length == 0)
        {
            throw std::runtime_error("Error while reading file - Check Format");
        }
    }
    else
    {
        throw std::runtime_error("Unable to open Configuration file");
    }

    #ifdef DEBUG
        std::cout<<"Done"<<std::endl;
    #endif

}


unsigned int dictionary::Configuration::getMinWordLength() const
{
    return _min_length;
}

unsigned int dictionary::Configuration::getMaxWordLength() const
{
    return _max_length;
}

const std::vector<std::wstring> &dictionary::Configuration::getWordList() const
{
    return _word_list;
}

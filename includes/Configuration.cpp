//
// Created by MK on 17.09.2019.
//

#include "Configuration.h"


std::string dictionary::getPath()
{
    static const std::string path("../data/Dictionary");
    return path;
}

dictionary::Configuration::Configuration(const std::string &path):
    m_min_length(0u),
    m_max_length(0u)
{
    loadWords(path);
}

void dictionary::Configuration::loadWords(const std::string &path) {

    std::wifstream file(path.c_str());

    if (!m_word_list.empty())
        m_word_list.clear();

    #ifdef _DEBUG
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

            if (m_min_length == 0)
                m_min_length = word.length();
            else
                m_min_length = std::min(m_min_length, word.length());

            m_max_length = std::max(m_max_length, word.length());

            m_word_list.push_back(word);
        }

        if (m_min_length == 0 || m_max_length == 0)
            throw std::runtime_error("Error while reading file - Check Format");
    }
    else
        throw std::runtime_error("Unable to open Configuration file");

    #ifdef _DEBUG
        std::cout<<"Done"<<std::endl;
    #endif

}


unsigned int dictionary::Configuration::getMinWordLength() const
{
    return m_min_length;
}

unsigned int dictionary::Configuration::getMaxWordLength() const
{
    return m_max_length;
}

const std::vector<std::wstring> &dictionary::Configuration::rGetWordList() const
{
    return m_word_list;
}

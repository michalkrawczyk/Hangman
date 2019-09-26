//
// Created by MK on 18.09.2019.
//

#ifndef HANGMAN_ARENA_H
#define HANGMAN_ARENA_H

#include <string>
#include <iostream>
#include <vector>


class Arena {
    void mInititalizeBoard();

public:
    explicit Arena();

    class Field {
        wchar_t m_desired_letter, m_actual_letter;

    public:
        explicit Field(const wchar_t &desired_letter = L' ',
                       const wchar_t &inital_letter = L' ');

        wchar_t getDesiredLetter() const;
        wchar_t getActualLetter() const;

        void setFieldValue();

        bool isFullfiled();
    };

    typedef std::vector<std::vector<Arena::Field>> ArenaFields;
    ArenaFields board;

    void printArena();

};



#endif //HANGMAN_ARENA_H

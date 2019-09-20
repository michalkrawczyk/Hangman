//
// Created by MK on 18.09.2019.
//

#ifndef HANGMAN_ARENA_H
#define HANGMAN_ARENA_H

#include <string>
#include <iostream>
#include <vector>


class Arena {
    void inititalizeBoard();

public:
    explicit Arena();

    class Field {
        wchar_t _desired_letter, _actual_letter;

    public:
        explicit Field(const wchar_t &desired_letter = L' ',const wchar_t &inital_letter = L' ');

        wchar_t get_desired_letter() const;
        wchar_t get_actual_letter() const;

        void setFieldValue();

        bool isFullfiled();
    };

    typedef std::vector<std::vector<Arena::Field>> ArenaFields;
    ArenaFields board;

    void printArena();

};



#endif //HANGMAN_ARENA_H

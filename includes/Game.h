//
// Created by MK on 19.09.2019.
//

#ifndef HANGMAN_GAME_H
#define HANGMAN_GAME_H

#include <string>
#include <algorithm>
#include <chrono>
#include <random>
#include <memory>


#include "..\includes\Arena.h"
#include "..\includes\Configuration.h"
#include "..\sources\Utils.h"

enum class DIFFICULTY: unsigned int
        {Undefined, Easy, Medium, Hard};

namespace game_params
{
    void selectRange(const dictionary::Configuration &config,
                     unsigned int &min,
                     unsigned int &max);
    DIFFICULTY selectDifficulty();
}

class Game;

class GameCreator{
    std::wstring _word;
    Arena _arena;
    std::wstring drawWord(const std::vector<std::wstring> &words);
    DIFFICULTY _difficulty;

public:
    std::unique_ptr<Game> createGame();
    GameCreator &generateArena(const DIFFICULTY &difficulty);
    GameCreator &drawMatchingWord(const std::vector<std::wstring> &collection,
                                        const unsigned int &min_length,
                                        const unsigned int &max_length);

};

// -----------------------------------------------------------------------------------------

class Game {


    Arena _arena;
    std::vector<wchar_t> _used_letters;
    std::wstring _final_word;
    std::wstring _actual_word;
    DIFFICULTY _difficulty;

    bool gameLost();

    bool checkLetter(const wchar_t &letter);
    bool usedLetter(const wchar_t &letter);

    void printGameStatus();
    void fillArena();


public:
    explicit Game(const Arena &arena, const std::wstring &word, const DIFFICULTY &difficulty);

    bool gameWon();
    bool gameEnd();
    std::chrono::duration<double> playGame();

    DIFFICULTY get_difficulty() const;

};


#endif //HANGMAN_GAME_H

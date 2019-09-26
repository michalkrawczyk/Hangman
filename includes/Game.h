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
    std::wstring m_word;
    Arena m_arena;
    DIFFICULTY m_difficulty;

    std::wstring mDrawWord(const std::vector<std::wstring> &word_list);

public:
    std::unique_ptr<Game> pCreateGame();
    GameCreator& rGenerateArena(const DIFFICULTY &difficulty);
    GameCreator& rDrawMatchingWord(const std::vector<std::wstring> &word_list,
                                   const unsigned int &min_length,
                                   const unsigned int &max_length);

};

// -----------------------------------------------------------------------------------------

class Game {


    Arena m_arena;
    std::vector<wchar_t> m_used_letters;
    std::wstring m_final_word;
    std::wstring m_actual_word;
    DIFFICULTY m_difficulty;

    bool mIsGameLost();

    bool mCheckLetter(const wchar_t &letter);
    bool mIsLetterUsed(const wchar_t &letter);

    void mPrintGameStatus();
    void mFillArena();


public:
    explicit Game(const Arena &arena,
                  const std::wstring &word,
                  const DIFFICULTY &difficulty);

    bool isGameWon();
    bool hasGameEnd();
    std::chrono::duration<double> playGame();

    DIFFICULTY getDifficulty() const;

};


#endif //HANGMAN_GAME_H

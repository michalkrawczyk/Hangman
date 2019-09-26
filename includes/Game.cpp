//
// Created by MK on 19.09.2019.
//

#include "Game.h"


void game_params::selectRange(const dictionary::Configuration &config,
                              unsigned int &min,
                              unsigned int &max)
{
    std::cout << "Choose Minimum Word Length" << std::endl;
    std::cout << " Min:"<<config.getMinWordLength() << std::endl;
    std::cout << " Max:"<<config.getMaxWordLength() << std::endl;

    do{
        std::cout << "Min Length:";
        uintInsert(min);
    } while (min < config.getMinWordLength() || min > config.getMaxWordLength());

    std::cout << "Choose Max Word Length" << std::endl;
    std::cout << " Min:" << min << std::endl;
    std::cout << " Max:" << config.getMaxWordLength() << std::endl;

    do{
        std::cout << "Max Length:";
        uintInsert(max);
    } while (max < min || max > config.getMaxWordLength());
}


DIFFICULTY game_params::selectDifficulty()
{
    std::cout << "Select Difficulty" << std::endl;
    std::cout << " 1.Easy" << std::endl;
    std::cout << " 2.Medium" << std::endl;
    std::cout << " 3.Hard" << std::endl;

    unsigned int choice;
    DIFFICULTY difficulty;

    do{
        std::cout << std::endl;
        std::cout << "Difficulty:";

        uintInsert(choice);
        difficulty = static_cast<DIFFICULTY>(choice);

        switch(difficulty)
        {
            case DIFFICULTY::Easy:
            {
                std::cout << "Level: Easy" << std::endl;
                break;
            }

            case DIFFICULTY::Medium:
            {
                std::cout << "Level: Medium" << std::endl;
                break;
            }
            case DIFFICULTY::Hard:
            {
                std::cout << "Level: Hard" << std::endl;
                break;
            }
            default:
            {
                std::cout << "Incorrect Difficulty" << std::endl;
                difficulty = DIFFICULTY::Undefined;
                break;
            }
        }
    }while (difficulty == DIFFICULTY::Undefined );

    return difficulty;
}


/* -----------------------------------------------------------------------------------------
 *  GameBuilder Functions - Begin */

std::unique_ptr<Game> GameCreator::pCreateGame() {
    return std::unique_ptr<Game>(new Game(m_arena, m_word, m_difficulty));
}

GameCreator &GameCreator::rGenerateArena(const DIFFICULTY &difficulty) {
    m_arena = Arena();
    m_difficulty = difficulty;

    if (m_difficulty == DIFFICULTY::Undefined)
        throw std::runtime_error("Undefined difficulty encountered while creating game");

    if (m_difficulty > DIFFICULTY::Easy)
    {
        for(auto &it : m_arena.board)
            it[0].setFieldValue();

        if(m_difficulty == DIFFICULTY::Hard)
            for(auto &it : m_arena.board[0])
                it.setFieldValue();
    }

    return *this;
}

GameCreator &GameCreator::rDrawMatchingWord(const std::vector<std::wstring> &word_list,
                                            const unsigned int &min_length,
                                            const unsigned int &max_length)
{
    auto match = [&min_length, &max_length](const std::wstring word){
        return (word.length() >= min_length) && (word.length() <= max_length);
    };

    std::vector <std::wstring> matching_words;
    std::copy_if(word_list.begin(),
            word_list.end(),
            std::back_inserter(matching_words),
            match);

    m_word = mDrawWord(matching_words);

    return *this;
}

std::wstring GameCreator::mDrawWord(const std::vector<std::wstring> &word_list) {
    if (!word_list.empty())
    {
        std::random_device device;
        std::mt19937 rng( device() );
        std::uniform_int_distribution <std::mt19937::result_type> dist(0, word_list.size()-1);

        return word_list[dist(rng)];
    }
    throw std::runtime_error("Unable to draw word - No matching words");
}


/*  GameBuilder Functions - END
 * -----------------------------------------------------------------------------------------
 *  Game Functions - Begin */

bool Game::mIsGameLost() {
    for (auto &row : m_arena.board)
        for(auto &col_value : row)
            if (!col_value.isFullfiled() )
                return false;

    return true;
}


bool Game::mCheckLetter(const wchar_t &letter) {
    bool result = false;

    for (auto i =0; i < m_final_word.length(); i++)
        if (m_final_word[i] == letter)
        {
            m_actual_word[i] = letter;

            result = true;
        }

    m_used_letters.emplace_back(letter);

    return result;
}

bool Game::mIsLetterUsed(const wchar_t &letter) {
    auto compare = [&letter](const wchar_t &t) {return t == letter;};

    return std::find_if(m_used_letters.begin(),
            m_used_letters.end(),
            compare) != m_used_letters.end();
}


void Game::mPrintGameStatus() {
    m_arena.printArena();

    std::cout << "Used Letters: ";
    std::for_each(m_used_letters.begin(),
            m_used_letters.end(),
            [](const wchar_t &x){std::wcout<<x<<";";});
    std::cout << std::endl;

    std::wcout << "Word:" << m_actual_word << std::endl;

}

void Game::mFillArena() {
    for (auto &row : m_arena.board)
        for (auto &col : row)
            if(!col.isFullfiled())
            {
                col.setFieldValue();
                return;
            }
}

Game::Game(const Arena &arena,
           const std::wstring &word,
           const DIFFICULTY &difficulty):
m_arena(arena),
m_final_word(word),
m_actual_word(word),
m_difficulty(difficulty)
{
    auto isLetter = [](const wchar_t &x){ return x != ' ';};
    std::replace_if(m_actual_word.begin(), m_actual_word.end(), isLetter, '.');
}

bool Game::isGameWon() {
    return m_actual_word == m_final_word;
}

bool Game::hasGameEnd() {
    return isGameWon() ^ mIsGameLost();
}

std::chrono::duration<double> Game::playGame() {

    auto start = std::chrono::system_clock::now();

    while (!hasGameEnd())
    {
        clearScreen();
        mPrintGameStatus();

        wchar_t letter;

        do{
            std::wcout << "Letter:";
            std::wcin >> letter;
        } while(mIsLetterUsed(letter));

        std::wcout << std::endl;

        if (!mCheckLetter(letter))
            mFillArena();

    }

    mPrintGameStatus();
    std::wcout << "\nThe Word was: " << m_final_word << std::endl;

    if (isGameWon())
        std::cout << "Congratulations . You have won" << std::endl;
    else
        std::cout << "You Lost - Maybe next time" << std::endl;

    auto end = std::chrono::system_clock::now();

    return end - start;
}

DIFFICULTY Game::getDifficulty() const {
    return m_difficulty;
}










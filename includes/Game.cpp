//
// Created by MK on 19.09.2019.
//

#include "Game.h"


void game_params::selectRange(const dictionary::Configuration &config,
                 unsigned int &min,
                 unsigned int &max)
{
    std::cout<<"Choose Minimum Word Length"<<std::endl;
    std::cout<<" Min:"<<config.getMinWordLength()<<std::endl;
    std::cout<<" Max:"<<config.getMaxWordLength()<<std::endl;

    do{
        std::cout<<"Min Length:";
        uintInsert(min);
    }while (min < config.getMinWordLength() || min > config.getMaxWordLength());

    std::cout<<"Choose Max Word Length"<<std::endl;
    std::cout<<" Min:"<<min<<std::endl;
    std::cout<<" Max:"<<config.getMaxWordLength()<<std::endl;

    do{
        std::cout<<"Max Length:";
        uintInsert(max);
    }while (max < min || max > config.getMaxWordLength());
}


DIFFICULTY game_params::selectDifficulty()
{
    std::cout<<"Select Difficulty"<< std::endl;
    std::cout<<" 1.Easy" << std::endl;
    std::cout<<" 2.Medium" << std::endl;
    std::cout<<" 3.Hard" << std::endl;

    unsigned int choice;
    DIFFICULTY difficulty;

    do{
        std::cout<<"Difficulty:";

        uintInsert(choice);
        difficulty = static_cast<DIFFICULTY>(choice);

        switch(difficulty)
        {
            case DIFFICULTY::Easy:
            {
                std::cout<<"Level: Easy"<<std::endl;
                break;
            }

            case DIFFICULTY::Medium:
            {
                std::cout<<"Level: Medium"<<std::endl;
                break;
            }
            case DIFFICULTY::Hard:
            {
                std::cout<<"Level: Hard"<<std::endl;
                break;
            }
            default:
            {
                std::cout<<"Incorrect Difficulty"<<std::endl;
                difficulty = DIFFICULTY::Undefined;
                break;
            }
        }
    }while (difficulty == DIFFICULTY::Undefined );

    return difficulty;
}


/* -----------------------------------------------------------------------------------------
 *  GameBuilder Functions - Begin */

std::unique_ptr<Game> GameCreator::createGame() {
    return std::unique_ptr<Game>(new Game(_arena, _word, _difficulty));
}

GameCreator &GameCreator::generateArena(const DIFFICULTY &difficulty) {
    _arena = Arena();
    _difficulty = difficulty;

    if (_difficulty == DIFFICULTY::Undefined)
    {
        throw std::runtime_error("Undefined difficulty encountered while creating game");
    }

    if (_difficulty > DIFFICULTY::Easy)
    {
        for(auto &it:_arena.board)
        {
            it[0].setFieldValue();
        }

        if(_difficulty == DIFFICULTY::Hard)
        {
            for(auto &it:_arena.board[0])
            {
                it.setFieldValue();
            }
        }
    }

    return *this;
}

GameCreator &GameCreator::drawMatchingWord(const std::vector<std::wstring> &collection,
                              const unsigned int &min_length,
                              const unsigned int &max_length)
{
    auto match = [&min_length,&max_length](const std::wstring word){
        return (word.length() >= min_length) && (word.length() <= max_length);
    };

    std::vector <std::wstring> matching_words;
    std::copy_if(collection.begin(), collection.end(), std::back_inserter(matching_words), match);

    _word = drawWord(matching_words);

    return *this;
}

std::wstring GameCreator::drawWord(const std::vector<std::wstring> &words) {
    if (!words.empty())
    {
        std::random_device rd;
        std::mt19937 rng( rd() );
        std::uniform_int_distribution <std::mt19937::result_type> dist(0, words.size());

        return words[dist(rng)];
    }
    throw std::runtime_error("Unable to draw word - No matching words");
}


/*  GameBuilder Functions - END
 * -----------------------------------------------------------------------------------------
 *  Game Functions - Begin */

bool Game::gameLost() {
    for (auto &row :_arena.board)
    {
        for(auto &col_value :row)
        {
            if (!col_value.isFullfiled() )
            {
                return false;
            }
        }
    }

    return true;
}


bool Game::checkLetter(const wchar_t &letter) {
    bool result = false;

    for (auto i =0; i <_final_word.length() ;i++)
    {
        if (_final_word[i] == letter)
        {
            _actual_word[i]=letter;

            result = true;
        }
    }

    _used_letters.emplace_back(letter);

    return result;
}

bool Game::usedLetter(const wchar_t &letter) {
    auto compare = [&letter](const wchar_t &t) {return t == letter;};

    return std::find_if(_used_letters.begin(), _used_letters.end(), compare) != _used_letters.end();
}


void Game::printGameStatus() {
    //TODO :Add Clear Screen Function , which is not system("cls")
    _arena.printArena();

    std::cout<<"Used Letters: ";
    std::for_each(_used_letters.begin(), _used_letters.end(), [](const wchar_t &x){std::wcout<<x<<";";});
    std::cout<<std::endl;

    std::wcout<<"Word:"<<_actual_word<<std::endl;

}

void Game::fillArena() {
    for (auto &row : _arena.board)
    {
        for (auto &col : row)
        {
            if(!col.isFullfiled())
            {
                col.setFieldValue();
                return;
            }
        }
    }
}

Game::Game(const Arena &arena, const std::wstring &word, const DIFFICULTY &difficulty):
_arena(arena),
_final_word(word),
_actual_word(word),
_difficulty(difficulty)

{
    auto isLetter = [](const wchar_t &x){ return x != ' ';};
    std::replace_if(_actual_word.begin(), _actual_word.end(), isLetter, '.');
}

bool Game::gameWon() {
    return _actual_word == _final_word;
}

bool Game::gameEnd() {
    return gameWon() ^ gameLost();
}

std::chrono::duration<double> Game::playGame() {

    auto start = std::chrono::system_clock::now();

    while (!gameEnd())
    {
        printGameStatus();
        wchar_t letter;

        do{
            std::wcout<<"Letter:";
            std::wcin>>letter;
        }while(usedLetter(letter));

        std::wcout<<std::endl;

        if (!checkLetter(letter))
        {
            fillArena();
        }

    }

    printGameStatus();
    std::wcout<<"\nThe Word was: "<<_final_word<<std::endl;

    if (gameWon())
    {
        std::cout<<"Congratulations . You have won"<<std::endl;
    }
    else
    {

        std::cout<<"You Lost - Maybe next time"<<std::endl;
    }

    auto end = std::chrono::system_clock::now();

    return end - start;
}

DIFFICULTY Game::get_difficulty() const {
    return _difficulty;
}










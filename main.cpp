#include <iostream>
#include <memory>

#ifdef LANGUAGE
    #include <locale>
#endif

#include "includes/Configuration.h"
#include "includes/Game.h"

namespace main_menu{
    enum CHOICE{None, Play, Statistics, Exit};
    void printMenu();
    CHOICE makeChoice();
}

namespace statistics_menu{
    void printMenu();
    enum CHOICE{None, Exit, Back};
    CHOICE makeChoice();
}





//#define LANGUAGE "pl-PL"
//Todo:: Add boost locale



int main() {
    try
    {
    #ifdef LANGUAGE
        std::locale::global(std::locale(LANGUAGE));
        std::wcout << "Used Language:" << std::locale("").name().c_str();
    #endif
        dictionary::Configuration config;

        main_menu::printMenu();
        main_menu::CHOICE choice(main_menu::CHOICE::None);

        while(choice == main_menu::CHOICE::None)
        {
            choice = main_menu::makeChoice();

            switch (choice)
            {
                case main_menu::CHOICE::Play:{

                    unsigned int min, max;
                    game_params::selectRange(config, min, max);

                    std::unique_ptr<Game> game = GameCreator()
                            .generateArena(game_params::selectDifficulty())
                            .drawMatchingWord(config.getWordList(), min, max)
                            .createGame();

                    std::chrono::duration<double> duration = game->playGame();
                    //Todo: Add Records
                    if (game->gameWon())
                    {
                        std::cout<<"Time:"<<duration.count()<<" s"<<std::endl;
                    }


                    choice = main_menu::CHOICE::None;
                    main_menu::printMenu();
                    break;
                }

                case main_menu::CHOICE::Statistics: {
                    //TODO:Statistics

                    //choice = main_menu::CHOICE::None;
                    //main_menu::printMenu();
                    break;
                }

                case main_menu::CHOICE::Exit:
                {
                    break;
                }

                default:
                {
                    choice = main_menu::CHOICE::None;
                    break;
                }
            }
        }

    }
    catch (const std::exception &e)
    {
        std::cout<<e.what();
    }
    return 0;
}

void main_menu::printMenu()
{
    std::cout<<std::endl;
    std::cout<<"Choose an option:"<<std::endl;
    std::cout<<"    1. Play"<<std::endl;
    std::cout<<"    2. Statistics"<<std::endl;
    std::cout<<"    3. Exit"<<std::endl;
}

main_menu::CHOICE main_menu::makeChoice() {

    unsigned int choice;

    std::cout<<"Option:";

    uintInsert(choice);

    if (choice != CHOICE::Exit
    && choice != CHOICE::Play
    && choice != CHOICE::Statistics)
    {
        std::cout<<"Wrong Option"<<std::endl;
        choice = CHOICE::None;
    }

    return static_cast <CHOICE> (choice);
}



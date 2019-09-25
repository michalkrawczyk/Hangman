#include <iostream>
#include <memory>

#ifdef LANGUAGE
    #include <locale>
#endif

#include "includes/Configuration.h"
#include "includes/Game.h"
#include "includes/Statistics.h"
#include "sources/Menu.h"



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

        Statistics statistics;
        statistics.readFromFile("../data/Statistics");

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
                    clearScreen();

                    std::unique_ptr<Game> game = GameCreator()
                            .generateArena(game_params::selectDifficulty())
                            .drawMatchingWord(config.getWordList(), min, max)
                            .createGame();

                    statistics.recordGame(game->get_difficulty())
                       .writeToFile("../data/Statistics");

                    std::chrono::duration<double> duration = game->playGame();

                    if (game->gameWon())
                    {
                        std::cout<<"Time:"<<duration.count()<<" s"<<std::endl;
                    }

                    statistics.saveResult(game->get_difficulty(), game->gameWon())
                       .newRecord(game->get_difficulty(), duration, game->gameWon())
                       .writeToFile("../data/Statistics");

                    clearScreen();
                    choice = main_menu::CHOICE::None;
                    main_menu::printMenu();
                    break;
                }

                case main_menu::CHOICE::Statistics: {
                    statistics.printStatistics(game_params::selectDifficulty());

                    statistics_menu::printMenu();
                    auto stats_choice(statistics_menu::CHOICE::None);

                    while(stats_choice == statistics_menu::CHOICE::None)
                        stats_choice = statistics_menu::makeChoice();

                    if (stats_choice == statistics_menu::CHOICE::Back)
                    {
                        clearScreen();
                        choice = main_menu::CHOICE::None;
                        main_menu::printMenu();
                    }

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


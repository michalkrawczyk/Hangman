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
        auto choice(main_menu::CHOICE::None);

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
                            .rGenerateArena(game_params::selectDifficulty())
                            .rDrawMatchingWord(config.rGetWordList(), min, max)
                            .pCreateGame();

                    statistics.rRecordGame(game->getDifficulty())
                       .writeToFile("../data/Statistics");

                    std::chrono::duration<double> duration = game->playGame();

                    if (game->isGameWon())
                    {
                        std::cout<<"Time:"<<duration.count()<<" s"<<std::endl;
                    }

                    statistics.rSaveResult(game->getDifficulty(), game->isGameWon())
                            .rIsNewRecord(game->getDifficulty(), duration, game->isGameWon())
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
                    break;

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


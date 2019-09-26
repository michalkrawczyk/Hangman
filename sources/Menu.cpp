//
// Created by MK on 25.09.2019.
//

#include "Menu.h"

void main_menu::printMenu()
{
    std::cout << std::endl;
    std::cout << "Choose an option:" << std::endl;
    std::cout << "    1. Play" << std::endl;
    std::cout << "    2. Statistics" << std::endl;
    std::cout << "    3. Exit" << std::endl;
}

main_menu::CHOICE main_menu::makeChoice() {

    unsigned int choice;

    std::cout << "Option:";

    uintInsert(choice);

    if (choice != CHOICE::Exit
        && choice != CHOICE::Play
        && choice != CHOICE::Statistics)
    {
        std::cout << "Wrong Option" << std::endl;
        choice = CHOICE::None;
    }

    return static_cast <CHOICE> (choice);
}


void statistics_menu::printMenu() {
    std::cout << std::endl;
    std::cout << "Choose an option:" << std::endl;
    std::cout << "    1. Go back to Main Manu" << std::endl;
    std::cout << "    2. Exit" << std::endl;
}

statistics_menu::CHOICE statistics_menu::makeChoice() {
    unsigned int choice;

    std::cout << "Option:";

    uintInsert(choice);

    if (choice != CHOICE::Exit
        && choice != CHOICE::Back)
    {
        std::cout << "Wrong Option" << std::endl;
        choice = CHOICE::None;
    }

    return static_cast<CHOICE>(choice);
}
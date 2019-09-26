//
// Created by MK on 19.09.2019.
//

#include "Utils.h"

void uintInsert(unsigned int &number)
{
    if(!(std::cin >> number))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void clearScreen()
{
    #ifdef _WIN32
        //system("cls"); //Looking for alternatives
        for(auto i = 0; i < 10; i++)
            std::cout << std::endl;
    #else
        printf("\e[1;1H\e[2J");
    #endif
}
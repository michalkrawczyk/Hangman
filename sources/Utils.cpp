//
// Created by MK on 19.09.2019.
//

#include "Utils.h"

void uintInsert(unsigned int &number)
{
    if(!(std::cin>>number))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
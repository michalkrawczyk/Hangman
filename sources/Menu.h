//
// Created by MK on 25.09.2019.
//

#ifndef HANGMAN_MENU_H
#define HANGMAN_MENU_H

#include <iostream>

#include "../sources/Utils.h"


namespace main_menu{
    enum CHOICE{None, Play, Statistics, Exit};
    void printMenu();
    CHOICE makeChoice();
}

namespace statistics_menu{
    void printMenu();
    enum CHOICE{None, Back, Exit};
    CHOICE makeChoice();
}


#endif //HANGMAN_MENU_H

//
// Created by Student235325 on 20.09.2019.
//

#ifndef HANGMAN_STATISTICS_H
#define HANGMAN_STATISTICS_H

#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../includes/Game.h"

struct LevelStats
{
    DIFFICULTY level;
    std::chrono::duration<double> best_time;
    unsigned int games_played;
    unsigned int games_won;

};

std::ostream &operator<<(std::ostream &os, const LevelStats &stats);


class Statistics {
    LevelStats _easy;
    LevelStats _medium;
    LevelStats _hard;

public:
    Statistics();
    bool readFromFile(const std::string &path);
    Statistics &recordGame(const DIFFICULTY &difficulty);
    Statistics &saveResult(const DIFFICULTY &difficulty, const bool &win);
    Statistics &newRecord(const DIFFICULTY &difficulty,
                            std::chrono::duration <double> &time,
                            const bool &win);
    void writeToFile(const std::string &path);
    void printStatistics(const DIFFICULTY &difficulty);

};


#endif //HANGMAN_STATISTICS_H

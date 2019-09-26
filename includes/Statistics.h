//
// Created by MK on 20.09.2019.
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
    LevelStats m_easy;
    LevelStats m_medium;
    LevelStats m_hard;

public:
    Statistics();

    Statistics& rRecordGame(const DIFFICULTY &difficulty);
    Statistics& rSaveResult(const DIFFICULTY &difficulty, const bool &win);
    Statistics& rIsNewRecord(const DIFFICULTY &difficulty,
                             const std::chrono::duration<double> &time,
                             const bool &has_won);

    bool readFromFile(const std::string &path);

    void writeToFile(const std::string &path);
    void printStatistics(const DIFFICULTY &difficulty);

};


#endif //HANGMAN_STATISTICS_H

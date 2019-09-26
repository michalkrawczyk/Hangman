//
// Created by MK on 20.09.2019.
//

#include "Statistics.h"

std::ostream &operator<<(std::ostream &os, const LevelStats &stats) {
    os << static_cast<unsigned int>(stats.level) << " " << "Best_Time= " << stats.best_time.count()<<std::endl;
    os << static_cast<unsigned int>(stats.level) << " " << "Games_Played= " << stats.games_played<<std::endl;
    os << static_cast<unsigned int>(stats.level) << " " << "Games_Won= " << stats.games_won<<std::endl;

    return os;
}

/* -----------------------------------------------------------------------------------------
 *  Statistics Functions - Begin */

Statistics::Statistics():
    m_easy(LevelStats{DIFFICULTY::Easy,
                     std::chrono::duration<double>(-1),
                     0u,
                     0u}),
    m_medium(LevelStats{DIFFICULTY::Medium,
                       std::chrono::duration<double>(-1),
                       0u,
                       0u}),
    m_hard(LevelStats{DIFFICULTY::Hard,
                     std::chrono::duration<double>(-1),
                     0u,
                     0u})
{

}



Statistics &Statistics::rRecordGame(const DIFFICULTY &difficulty) {
    LevelStats *pLevels [3] = {&m_easy, &m_medium, &m_hard};
    bool defined_level(false);

    for (auto &it : pLevels)
    {
        if(it->level == difficulty)
        {
            it->games_played++;
            defined_level = true;
        }
    }

    if (!defined_level)
        std::runtime_error("Statistics encountered undefined difficulty level on recording");

    return *this;
}

Statistics &Statistics::rIsNewRecord(const DIFFICULTY &difficulty,
                                     const std::chrono::duration<double> &time,
                                     const bool &has_won) {
    if(!has_won)
        return *this;

    LevelStats *pLevels [3] = {&m_easy, &m_medium, &m_hard};
    bool defined_level(false);

    for (auto &it : pLevels)
    {
        if(it->level == difficulty)
        {
            defined_level = true;

            if((it->best_time > time) || (it->best_time <= std::chrono::duration <double>(-1)) )
            {
                std::cout << "Congratulations! You have set the new record: " << time.count();
                it->best_time = time;
            }
        }
    }

    if (!defined_level)
        std::runtime_error("Statistics encountered undefined difficulty level on checking best time");

    return *this;
}

void Statistics::writeToFile(const std::string &path) {
    std::ofstream file(path);
    file << m_easy << m_medium << m_hard;
    file.close();
}

Statistics &Statistics::rSaveResult(const DIFFICULTY &difficulty, const bool &win) {
    if(!win)
        return *this;

    LevelStats *pLevels [3] = {&m_easy, &m_medium, &m_hard};
    bool defined_level(false);

    for (auto it : pLevels)
    {
        if (it->level == difficulty)
        {
            it->games_won++;
            defined_level = true;
        }
    }

    if (!defined_level)
        std::runtime_error("Statistics encountered undefined difficulty level on checking result");

    return *this;
}

bool Statistics::readFromFile(const std::string &path) {
    std::ifstream file(path);
    LevelStats *pLevels [3]={&m_easy,&m_medium,&m_hard};

    if (file.good() && file.is_open())
    {
        while(!file.eof())
        {
            std::string line;
            std::getline(file, line);
            std::stringstream ss(line);

            unsigned int numLevel;
            ss >> numLevel;

            for(auto &it : pLevels)
            {
                if (it->level == static_cast<DIFFICULTY>(numLevel))
                {
                    std::string name;
                    ss >> name;

                    if (name.find("Best_Time") != std::string::npos)
                    {
                        double time;
                        ss >> time;
                        it->best_time = std::chrono::duration<double>(time);
                    }
                    else if (name.find("Games_Played") != std::string::npos)
                    {
                        unsigned int numGames;
                        ss >> numGames;
                        it->games_played = numGames;
                    }
                    else if (name.find("Games_Won") != std::string::npos)
                    {
                        unsigned int numGames;
                        ss >> numGames;
                        it->games_won = numGames;
                    }

                    break;
                }
            }
        }

        return true;
    }
    else
        std::cout<<"Unable to open file with Statistics"<<std::endl;

    return false;
}

void Statistics::printStatistics(const DIFFICULTY &difficulty) {
    LevelStats *pLevels [3]={&m_easy,&m_medium,&m_hard};
    bool defined_level(false);

    for(auto &it : pLevels)
    {
        if (it->level == difficulty)
        {
            std::cout << *it;
            defined_level = true;
        }
    }

    if (!defined_level)
        std::runtime_error("Statistics encountered undefined difficulty level while printing statistics");
}



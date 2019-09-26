//
// Created by MK on 18.09.2019.
//

#include "Arena.h"

/* -----------------------------------------------------------------------------------------
 *  Arena Functions - Begin */

Arena::Arena()
{
    mInititalizeBoard();
}

void Arena::mInititalizeBoard()
{
    wchar_t board_template[6][5] = {
            {'_', '_', '_', '_', ' '},
            {'|', '/', ' ', '|', ' '},
            {'|', ' ', '\\', 'O', '/'},
            {'|', ' ', ' ', '|', ' '},
            {'|', ' ', '/', ' ', '\\'},
            {'|', ' ', ' ', ' ', ' '},
    };

    board.resize(6, std::vector<Field>(5));

    for (auto row = 0; row < board.size(); row++)
        for(auto column = 0; column < board[0].size(); column++)
        {
            wchar_t temp(' ');
            if (board_template[row][column] != ' ')
                temp = '.';
            board[row][column] = Field(board_template[row][column], temp);
        }

}

void Arena::printArena()
{
    for (auto &row:board)
    {
        for(auto &column:row)
            std::wcout<< column.getActualLetter();

        std::cout<<std::endl;
    }
}


/*  Arena Functions - END
 * -----------------------------------------------------------------------------------------
 *  Field Functions - Begin */

Arena::Field::Field(const wchar_t &desired_letter,
                    const wchar_t &inital_letter):
m_actual_letter(inital_letter),
m_desired_letter(desired_letter)
{}

wchar_t Arena::Field::getDesiredLetter() const
{
    return m_desired_letter;
}

wchar_t Arena::Field::getActualLetter() const
{
    return m_actual_letter;
}

void Arena::Field::setFieldValue()
{
    m_actual_letter = m_desired_letter;
}

bool Arena::Field::isFullfiled()
{
    return m_actual_letter == m_desired_letter;
}

//  Field Functions - END

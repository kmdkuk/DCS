/*
  Author:      Kamada Kouki
 Student ID:   b1015047
 Class:        J
 Created:      December 15, 2017
 Language:     C
*/

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif

#ifndef COOPERATION
#define COOPERATION 1
#endif

#ifndef DECEPTION
#define DECEPTION 0
#endif

void p2tit242tat(int previousPlayerStrategy, int previousPartnerStrategy, int *currentPlayerStrategy, int deceptionFlag, int *deceptionCount)
{
    if (*deceptionCount > 0)
    {
        *currentPlayerStrategy = DECEPTION;
        (*deceptionCount)--;
    }
    if (deceptionFlag == DECEPTION && previousPartnerStrategy == DECEPTION)
    {
        *currentPlayerStrategy = DECEPTION;
        *deceptionCount = 1;
    }
    else if (*currentPlayerStrategy != DECEPTION)
    {
        *currentPlayerStrategy = COOPERATION;
        if (deceptionFlag == COOPERATION && previousPartnerStrategy == COOPERATION)
        {
            double probability = 0.5;
            if ((double)rand() / RAND_MAX < probability)
            {
                *currentPlayerStrategy = DECEPTION;
            }
        }
    }

    return;
}

int player1DeceptionFlag = COOPERATION;
int deceptionCount2 = 0;
void Player2(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer2Strategy)
{
    p2tit242tat(previousPlayer1Strategy, previousPlayer2Strategy, currentPlayer2Strategy, player1DeceptionFlag, &deceptionCount2);
    player1DeceptionFlag = previousPlayer1Strategy;
    return;
}
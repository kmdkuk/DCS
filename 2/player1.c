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

/*
    function:void p1tit242tat(int previousPlayerStrategy, int previousPartnerStrategy, int *currentPlayerStrategy, int deceptionFlag, int *deceptionCount)
    desctription:2回裏切られたら2回裏切り返す．
*/

void p1tit242tat(int previousPlayerStrategy, int previousPartnerStrategy, int *currentPlayerStrategy, int deceptionFlag, int *deceptionCount)
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
            double probability = 0.3;
            if ((double)rand() / RAND_MAX < probability)
            {
                *currentPlayerStrategy = DECEPTION;
            }
        }
    }

    return;
}

int player2DeceptionFlag = COOPERATION;
int deceptionCount1 = 0;
void Player1(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer1Strategy)
{
    p1tit242tat(previousPlayer1Strategy, previousPlayer2Strategy, currentPlayer1Strategy, player2DeceptionFlag, &deceptionCount1);
    player2DeceptionFlag = previousPlayer2Strategy;
    return;
}
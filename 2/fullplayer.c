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

void Player1(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer1Strategy)
{
    return;
}
void Player2(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer2Strategy)
{
    return;
}

void tit4tat(int previousPlayerStrategy, int previousPartnerStrategy, int *currentPlayerStrategy)
{
    if (previousPlayerStrategy == -1 && previousPartnerStrategy == -1)
    {
        *currentPlayerStrategy = COOPERATION;
    }
    else
    {
        *currentPlayerStrategy = previousPartnerStrategy;
    }
    return;
}

void rtit4tat(int previousPlayerStrategy, int previousPartnerStrategy, int *currentPlayerStrategy)
{
    if (previousPlayerStrategy == -1 && previousPartnerStrategy == -1)
    {
        *currentPlayerStrategy = DECEPTION;
    }
    else
    {
        *currentPlayerStrategy = previousPartnerStrategy;
    }
    return;
}

void tit42tat(int previousPlayerStrategy, int previousPartnerStrategy, int *currentPlayerStrategy)
{

    return;
}

void friedman(int previousPlayerStrategy, int previousPartnerStrategy, int *currentPlayerStrategy)
{
    *currentPlayerStrategy = COOPERATION;
    if (previousPlayerStrategy == -1 && previousPartnerStrategy == -1)
    {
        return;
    }
    else
    {
        if (previousPlayerStrategy == DECEPTION || previousPartnerStrategy == DECEPTION)
        {
            *currentPlayerStrategy = DECEPTION;
        }
    }
    return;
}

void joss(int previousPlayerStrategy, int previousPartnerStrategy, int *currentPlayerStrategy)
{
    double probability = 0.9;
    if (previousPlayerStrategy == -1 && previousPartnerStrategy == -1)
    {
        *currentPlayerStrategy = COOPERATION;
    }
    else
    {
        if (previousPartnerStrategy == COOPERATION)
        {
            if ((double)rand() / RAND_MAX < probability)
            {
                *currentPlayerStrategy = COOPERATION;
            }
            else
            {
                *currentPlayerStrategy = DECEPTION;
            }
        }
        else
        {
            *currentPlayerStrategy = DECEPTION;
        }
    }
    return;
}

void random(int previousPlayerStrategy, int previousPartnerStrategy, int *currentPlayerStrategy)
{
    double probability = 0.5;
    if ((double)rand() / RAND_MAX < probability)
    {
        *currentPlayerStrategy = COOPERATION;
    }
    else
    {
        *currentPlayerStrategy = DECEPTION;
    }
    return;
}

void allD(int previousPlayerStrategy, int previousPartnerStrategy, int *currentPlayerStrategy)
{
    *currentPlayerStrategy = DECEPTION;
    return;
}

void allC(int previousPlayerStrategy, int previousPartnerStrategy, int *currentPlayerStrategy)
{
    *currentPlayerStrategy = COOPERATION;
    return;
}

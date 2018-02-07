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

int count;
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

void tit42tat(int previousPlayerStrategy, int previousPartnerStrategy, int *currentPlayerStrategy, int deceptionFlag)
{
    if (deceptionFlag == DECEPTION && previousPartnerStrategy == DECEPTION)
    {
        *currentPlayerStrategy = DECEPTION;
    }
    else
    {
        *currentPlayerStrategy = COOPERATION;
    }
    return;
}

void tit242tat(int previousPlayerStrategy, int previousPartnerStrategy, int *currentPlayerStrategy, int deceptionFlag, int *deceptionCount)
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

void friedman(int previousPlayerStrategy, int previousPartnerStrategy, int *currentPlayerStrategy, int flag)
{
    *currentPlayerStrategy = COOPERATION;
    if (previousPlayerStrategy == -1 && previousPartnerStrategy == -1)
    {
        return;
    }
    else
    {
        if (flag == DECEPTION)
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

void randomStr(int previousPlayerStrategy, int previousPartnerStrategy, int *currentPlayerStrategy)
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

void printStrategy(int strategy)
{
    if (strategy == DECEPTION)
    {
        printf("裏切り");
        return;
    }
    else if (strategy == COOPERATION)
    {
        printf("強調");
        return;
    }
    printf("なんかミスってる");
    return;
}

int player1DeceptionFlag = COOPERATION;
int player2DeceptionFlag = COOPERATION;
int deceptionCount1 = 0;
int deceptionCount2 = 0;
void Player1(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer1Strategy)
{
    tit242tat(previousPlayer1Strategy, previousPlayer2Strategy, currentPlayer1Strategy, player2DeceptionFlag, &deceptionCount1);
    player2DeceptionFlag = previousPlayer2Strategy;
    return;
}
void Player2(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer2Strategy)
{
    if (previousPlayer1Strategy == DECEPTION || player1DeceptionFlag == DECEPTION)
    {
        //player1DeceptionFlag = DECEPTION;//friedmanのフラグ用
    }
    allD(previousPlayer2Strategy, previousPlayer1Strategy, currentPlayer2Strategy);//, player1DeceptionFlag);//, &deceptionCount2);
    //player1DeceptionFlag = previousPlayer1Strategy; //tit42tatのフラグ用
    return;
}

/*
 * 必要なライブラリのロード
 * (stdio.hおよびstdlib.h)
 */
#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

/* predatorの数値表現 */
#ifndef VALUE_OF_PREDATOR
#define VALUE_OF_PREDATOR 1
#endif

/* preyの数値表現 */
#ifndef VALUE_OF_PREY
#define VALUE_OF_PREY 10
#endif

/* obstacleの数値表現 */
#ifndef VALUE_OF_OBSTACLE
#define VALUE_OF_OBSTACLE -1
#endif

/* free gridの数値表現 */
#ifndef VALUE_OF_FREE
#define VALUE_OF_FREE 0
#endif

/* 格子世界の大きさ */
#ifndef WORLD_SIZE
#define WORLD_SIZE 8
#endif

typedef enum 
{
  NONE,
  OPEN,
  CLOSED,
} STATUS;

typedef struct 
{
  int x;
  int y;
} predator_position;

typedef struct __predatorAstar
{
  predator_position pos;
  STATUS status;
  int cost;
  int heuristic;
  struct __predatorAstar *parent;
} predatorAstar;

int predatorGetScore(predatorAstar it)
{
  return it.cost + it.heuristic;
}

int predatorGetDistance(predator_position from, predator_position to)
{
  int result = 0;
  result = abs(from.x - to.x) + abs(from.y - to.y);
  return result;
}

void predatorOpen(predatorAstar *toopen, predatorAstar *parent, predator_position to)
{
  toopen->status = OPEN;
  toopen->parent = parent;
  toopen->cost = parent->cost + 1;
  toopen->heuristic = predatorGetDistance(toopen->pos, to);
}

predator_position *predatorSearch(int world[WORLD_SIZE][WORLD_SIZE], predator_position from, predator_position to)
{
  predatorAstar worldAstar[WORLD_SIZE][WORLD_SIZE];
  predator_position here;
  for(int i = 0;i < WORLD_SIZE;i++)
  {
    for(int j = 0;j < WORLD_SIZE;j++)
    {
      worldAstar[i][j].status = NONE;
      worldAstar[i][j].pos.x = i;
      worldAstar[i][j].pos.y = j;
    }
  }

  worldAstar[from.x][from.y].status = OPEN;
  worldAstar[from.x][from.y].parent = NULL;
  worldAstar[from.x][from.y].cost = 0;
  worldAstar[from.x][from.y].heuristic = predatorGetDistance(from, to);
  predatorAstar *parent = &worldAstar[from.x][from.y];
  //printf("root %d:%d\n",parent->pos.x,parent->pos.y);
  while(1)
  {
    if(parent->status != OPEN)
      {
        printf("おかしい\n");
        break;
      }
    //hereがオープン先
    //上
    if(parent->pos.y > 0)
    {
      here = parent->pos;
      here.y -= 1;
      if(world[here.x][here.y] != VALUE_OF_OBSTACLE && worldAstar[here.x][here.y].status == NONE) 
      {
        predatorOpen(&worldAstar[here.x][here.y], parent, to);
      }
    }
    //下
    if(parent->pos.y < WORLD_SIZE-1)
    {
      here = parent->pos;
      here.y += 1;
      if(world[here.x][here.y] != VALUE_OF_OBSTACLE && worldAstar[here.x][here.y].status == NONE) 
      {
        predatorOpen(&worldAstar[here.x][here.y], parent, to);
      }
    }
    //左
    if(parent->pos.x > 0)
    {
      here = parent->pos;
      here.x -= 1;
      if(world[here.x][here.y] != VALUE_OF_OBSTACLE && worldAstar[here.x][here.y].status == NONE) 
      {
        predatorOpen(&worldAstar[here.x][here.y], parent, to);
      }
    }
    //右
    if(parent->pos.x < WORLD_SIZE-1)
    {
      here = parent->pos;
      here.x += 1;
      if(world[here.x][here.y] != VALUE_OF_OBSTACLE && worldAstar[here.x][here.y].status == NONE) 
      {
        predatorOpen(&worldAstar[here.x][here.y], parent, to);
      }
    }
    parent->status = CLOSED;

    if(worldAstar[to.x][to.y].status == OPEN)break;

    int min = 9999;
    int min_x;
    int min_y;

    for(int i = 0;i < WORLD_SIZE;i++)
    {
      for(int j = 0;j < WORLD_SIZE;j++)
      {
        if(worldAstar[i][j].status == OPEN)
        {
          //printf("%d,%d\n",i,j);
          int score = predatorGetScore(worldAstar[i][j]);
          if(min > score)
          {
            min = score;
            min_x = i;
            min_y = j;
            //printf("min:%d\n",min);
          }else if(min == score)
          {
            if(worldAstar[min_x][min_y].cost > worldAstar[i][j].cost)
            {
              min_x = i;
              min_y = j;
            }
          }
        }
      }
    }

    parent = &worldAstar[min_x][min_y];
  }

  //printf("抜けた");

  here = to;
  predator_position *root;
  root = (predator_position *)malloc((worldAstar[to.x][to.y].cost+1) * sizeof(predator_position));
  while(1)
  {
    //printf("%d:%d\n",here.x,here.y);
    root[worldAstar[here.x][here.y].cost] = here;
    here = worldAstar[here.x][here.y].parent->pos;
    if(here.x == from.x && here.y == from.y)break;
  }

  return root;
}

void Predator(int world[WORLD_SIZE][WORLD_SIZE], int *action)
{
  predator_position *root;
  predator_position prey;
  predator_position predator;
  for(int i = 0;i < WORLD_SIZE;i++)
  {
    for(int j = 0;j < WORLD_SIZE;j++)
    {
      if(world[i][j] == VALUE_OF_PREY)
      {
        prey.x = i;
        prey.y = j;
      }
      if(world[i][j] == VALUE_OF_PREDATOR)
      {
        predator.x = i;
        predator.y = j;
      }
    }
  }
  printf("prey %d:%d\n", prey.x, prey.y);
  printf("predator %d:%d\n", predator.x, predator.y);
  root = predatorSearch(world, predator, prey);
  printf("root[1]: %d:%d",root[1].x,root[1].y);
  if(predator.y == root[1].y)
  {
    if(predator.x - root[1].x > 0)
    {
      *action = 'u';
    }else
    {
      *action = 'd';
    }
  }
  if(predator.x == root[1].x) 
  {
    if(predator.y - root[1].y > 0)
    {
      *action = 'l';
    }else
    {
      *action = 'r';
    }
  }
  free(root);
}

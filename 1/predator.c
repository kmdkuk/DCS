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

predator_position *predatorSearch(int world[WORLD_SIZE][WORLD_SIZE], predator_position from, predator_position to)
{
  predatorAstar worldAstar[WORLD_SIZE][WORLD_SIZE];
  predator_position here = from;
  for(int i = 0;i < WORLD_SIZE;i++)
  {
    for(int j = 0;j < WORLD_SIZE;j++)
    {
      worldAstar[i][j].status = NONE;
      worldAstar[i][j].pos.x = i;
      worldAstar[i][j].pos.y = j;
    }
  }

  worldAstar[here.x][here.y].status = OPEN;
  worldAstar[here.x][here.y].parent = NULL;
  worldAstar[here.x][here.y].cost = 0;
  worldAstar[here.x][here.y].heuristic = predatorGetDistance(here, to);
  while(1)
  {
    predatorAstar parent = worldAstar[here.x][here.y];
    //上
    if(here.y > 0)
    {
      here = worldAstar[here.x][here.y-1].pos;
      if(world[here.x][here.y] != VALUE_OF_OBSTACLE) 
      {
        worldAstar[here.x][here.y].status = OPEN;
        worldAstar[here.x][here.y].parent = &parent;
        worldAstar[here.x][here.y].cost = parent.cost + 1;
        worldAstar[here.x][here.y].heuristic = predatorGetDistance(here, to);
      }
    }
    //下
    if(here.y < WORLD_SIZE-1)
    {
      here = worldAstar[here.x][here.y+1].pos;
      if(world[here.x][here.y] != VALUE_OF_OBSTACLE) 
      {
        worldAstar[here.x][here.y].status = OPEN;
        worldAstar[here.x][here.y].parent = &parent;
        worldAstar[here.x][here.y].cost = parent.cost + 1;
        worldAstar[here.x][here.y].heuristic = predatorGetDistance(here, to);
      }
    }
    //左
    if(here.x > 0)
    {
      here = worldAstar[here.x-1][here.y].pos;
      if(world[here.x][here.y] != VALUE_OF_OBSTACLE) 
      {
        worldAstar[here.x][here.y].status = OPEN;
        worldAstar[here.x][here.y].parent = &parent;
        worldAstar[here.x][here.y].cost = parent.cost + 1;
        worldAstar[here.x][here.y].heuristic = predatorGetDistance(here, to);
      }
    }
    //右
    if(here.y < WORLD_SIZE-1)
    {
      here = worldAstar[here.x+1][here.y].pos;
      if(world[here.x][here.y] != VALUE_OF_OBSTACLE) 
      {
        worldAstar[here.x][here.y].status = OPEN;
        worldAstar[here.x][here.y].parent = &parent;
        worldAstar[here.x][here.y].cost = parent.cost + 1;
        worldAstar[here.x][here.y].heuristic = predatorGetDistance(here, to);
      }
    }
    worldAstar[here.x][here.y].status = CLOSED;

    int min = 999;
    int min_x;
    int min_y;

    for(int i = 0;i < WORLD_SIZE;i++)
    {
      for(int j = 0;j < WORLD_SIZE;j++)
      {
        if(min > predatorGetScore(worldAstar[i][j]))
        {
          min = predatorGetScore(worldAstar[i][j]);
          min_x = i;
          min_y = j;
        }
        if(worldAstar[i][j].status == OPEN)
        {
          if(i == to.x && j == to.y) break;
        }
      }
    }

    here.x = min_x;
    here.y = min_y;
  }

  here = to;
  predator_position *root;
  root = (predator_position *)malloc(worldAstar[to.x][to.y].cost * sizeof(predator_position));
  while(worldAstar[here.x][here.y].parent != NULL)
  {
    root[worldAstar[here.x][here.y].cost] = here;
    here = worldAstar[here.x][here.y].parent->pos;
  }

  return root;
}

void predator(int world[WORLD_SIZE][WORLD_SIZE], int *action)
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
  root = predatorSearch(world, predator, prey);
  if(predator.x == root[1].x)
  {
    if(predator.y - root[1].y < 0)
    {
      *action = 'u';
      return;
    }else
    {
      *action = 'd';
      return;
    }
  }
  if(predator.y == root[1].y) 
  {
    if(predator.x - root[1].x < 0)
    {
      *action = 'l';
      return;
    }else
    {
      *action = 'r';
      return;
    }
  }
}

int main(void)
{
  return 0;
}
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
} prey_position;

typedef struct __preyAstar
{
  prey_position pos;
  STATUS status;
  int cost;
  int heuristic;
  struct __preyAstar *parent;
} preyAstar;

int preyGetScore(preyAstar it)
{
  return it.cost + it.heuristic;
}

int preyGetDistance(prey_position from, prey_position to)
{
  int result = 0;
  result = abs(from.x - to.x) + abs(from.y - to.y);
  return result;
}

void preyOpen(preyAstar *toopen, preyAstar *parent, prey_position to)
{
  toopen->status = OPEN;
  toopen->parent = parent;
  toopen->cost = parent->cost + 1;
  toopen->heuristic = preyGetDistance(toopen->pos, to);
}

int preySearch(int world[WORLD_SIZE][WORLD_SIZE], prey_position from, prey_position to)
{
  preyAstar worldAstar[WORLD_SIZE][WORLD_SIZE];
  prey_position here;
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
  worldAstar[from.x][from.y].heuristic = preyGetDistance(from, to);
  preyAstar *parent = &worldAstar[from.x][from.y];
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
        preyOpen(&worldAstar[here.x][here.y], parent, to);
      }
    }
    //下
    if(parent->pos.y < WORLD_SIZE-1)
    {
      here = parent->pos;
      here.y += 1;
      if(world[here.x][here.y] != VALUE_OF_OBSTACLE && worldAstar[here.x][here.y].status == NONE) 
      {
        preyOpen(&worldAstar[here.x][here.y], parent, to);
      }
    }
    //左
    if(parent->pos.x > 0)
    {
      here = parent->pos;
      here.x -= 1;
      if(world[here.x][here.y] != VALUE_OF_OBSTACLE && worldAstar[here.x][here.y].status == NONE) 
      {
        preyOpen(&worldAstar[here.x][here.y], parent, to);
      }
    }
    //右
    if(parent->pos.x < WORLD_SIZE-1)
    {
      here = parent->pos;
      here.x += 1;
      if(world[here.x][here.y] != VALUE_OF_OBSTACLE && worldAstar[here.x][here.y].status == NONE) 
      {
        preyOpen(&worldAstar[here.x][here.y], parent, to);
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
          int score = preyGetScore(worldAstar[i][j]);
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

  return worldAstar[to.x][to.y].cost;
}

void Prey(int world[WORLD_SIZE][WORLD_SIZE], int *action)
{
  int root[4];
  for(int i = 0;i < 4;i++)root[i] = 0;
  prey_position prey, prey_tmp;
  prey_position predator;
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
  //上
  if(prey.x > 0 && world[prey.x-1][prey.y] == VALUE_OF_FREE)
  {
    prey_tmp = prey;
    prey_tmp.x -= 1;
    root[0] = preySearch(world, prey_tmp, predator);
  }
  
  //下
  if(prey.x < WORLD_SIZE-1 && world[prey.x+1][prey.y] == VALUE_OF_FREE)
  {
    prey_tmp = prey;
    prey_tmp.x += 1;
    root[1] = preySearch(world, prey_tmp, predator);
  }
  
  //左
  if(prey.y > 0 && world[prey.x][prey.y-1] == VALUE_OF_FREE)
  {
    prey_tmp = prey;
    prey_tmp.y -= 1;
    root[2] = preySearch(world, prey_tmp, predator);
  }
  
  //右
  if(prey.y < WORLD_SIZE-1 && world[prey.x][prey.y+1] == VALUE_OF_FREE)
  {
    prey_tmp = prey;
    prey_tmp.y += 1;
    root[3] = preySearch(world, prey_tmp, predator);
  }

  int max = 0;
  int max_index;
  for(int i = 0;i < 4;i++)
  {
    //printf("root[%d])=%d\n", i, root[i]);
    if(max < root[i])
    {
      max = root[i];
      max_index = i;
    }
  }
  //printf("max:%d\n",max_index);

  switch(max_index)
  {
    case 0:
      *action = 'u';
      break;
    case 1:
      *action = 'd';
      break;
    case 2:
      *action = 'l';
      break;
    case 3:
      *action = 'r';
      break;
  }
}
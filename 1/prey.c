#include "pursuit.c"

void prey(int world[][], int *action)
{
  struct pursuit_position self;
  struct pursuit_position predetor;

  //自分とpredetorの場所記録
  for(int i = 0;i < WORLD_SIZE;i++)
  {
    for(int j = 0;j < WORLD_SIZE;j++)
    {
      if(world[i][j] == VALUE_OF_PREY)
      {
        self.x = i;
        self.y = j;
      }
      if(world[i][j] == VALUE_OF_PREDATOR)
      {
        predetor.x = i;
        predetor.y = j;
      }
    }
  }

}



int preyGetDistance(struct pursuit_position from, struct pursuit_position to)
{
  int result = 0;
  result = abs(from.x - to.x) + abs(from.y - to.y)
  return result;
}

int preySearch(int world[][], struct pursuit_position from, struct pursuit_position to)
{
  struct preyAStar preyAStarWorld[WORLD_SIZE][WORLD_SIZE];
  struct pursuit_position present = from;
  for(int i = 0;i < WORLD_SIZE;i++)
  {
    for(int j = 0;j < WORLD_SIZE;j++)
    {
      preyAStarWorld[i][j].status = NONE
    }
  }

  while(1)
  {
    preyAStarWorld[present.x][present.y].status = OPEN;
    preyAStarWorld[present.x][present.y].cost = 0;
    preyAStarWorld[present.x][present.y].heuristic = preyGetDistance(from, to);

  }
}

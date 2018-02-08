/*
  Author:      Kamada Kouki
 Student ID:   b1015047
 Class:        J
 Created:      February 8, 2018
 Language:     C
*/

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
#define WORLD_SIZE 16
#endif

int predator_map[4][16][16];
int predator_flag = 1;

typedef struct{
  int x;
  int y;
} predator_position;

typedef enum 
{
  NONE,
  OPEN,
  CLOSED,
} STATUS;

typedef struct __predatorAstar
{
  predator_position pos;
  STATUS status;
  int cost;
  int heuristic;
  struct __predatorAstar *parent;
} predatorAstar;

/*
  Function:     predatorGetScore(predatorAstar it)
  Description:  itのA*で使うF値(現在地までの距離とゴールまでの推定値の和)を返す。
*/
int predatorGetScore(predatorAstar it)
{
  return it.cost + it.heuristic;
}

/*
  Function:   predatorGetDistance(predator_position from, predator_position to)
  Description: A*探索に使うヒューリスティック関数としてマンハッタン距離を返す。
*/
int predatorGetDistance(predator_position from, predator_position to)
{
  int result = 0;
  result = abs(from.x - to.x) + abs(from.y - to.y);
  return result;
}

/*
  Function:   predatorOpen(predatorAstar *toopen, predatorAstar *parent, predator_position to)
  Descripion: フィールドのステータスをOPENにするための関数
*/
void predatorOpen(predatorAstar *toopen, predatorAstar *parent, predator_position to)
{
  toopen->status = OPEN;
  toopen->parent = parent;
  toopen->cost = parent->cost + 1;
  toopen->heuristic = predatorGetDistance(toopen->pos, to);
}

/*
  Function:   *predatorSearch(int world[WORLD_SIZE][WORLD_SIZE], predator_position from, predator_position to)
  Description:  A*探索をして、最短距離のルートを入れた配列のポインタを返す。
*/
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
      printf("error\n");
      break;
    }
    //hereがオープン先
    //上
    if(parent->pos.y > 0)
    {
      here = parent->pos;
      here.y -= 1;
      if(world[here.x][here.y] != VALUE_OF_OBSTACLE  && worldAstar[here.x][here.y].status == NONE) 
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
    //printf("koko%d:%d\n",here.x,here.y);
    root[worldAstar[here.x][here.y].cost] = here;
    here = worldAstar[here.x][here.y].parent->pos;
    if(here.x == from.x && here.y == from.y)
    {
        //printf("抜けます\n");
        //printf("root[0]:%d\n",sizeof(root[0]));
        break;
    }
  }

  return root;
}

int predator_isUnknown(int world[16][16], predator_position self, int dir)
{
    if(dir == 'u')
    {
        if(self.x<2 || world[self.x-1][self.y] == -1)return 0;
        for(int x = self.x;x>0;x--)
        {
            if(world[x][self.y] == -10) return 1;
        }
    }else if(dir == 'r')
    {
        if(self.y>14 || world[self.x][self.y+1] == -1)return 0;
        for(int y = self.y;y<16;y++)
        {
            if(world[self.x][y] == -10) return 1;
        }
    }else if(dir == 'd')
    {
        if(self.x>14 || world[self.x+1][self.y] == -1)return 0;
        for(int x = self.x;x<16;x++)
        {
            if(world[x][self.y] == -10) return 1;
        }
    }else if(dir == 'l')
    {
        if(self.y<2 || world[self.x][self.y-1] == -1)return 0;
        for(int y = self.y;y>0;y--)
        {
            if(world[self.x][y] == -10) return 1;
        }
    }
    return 0;
}

int predator_isVisible(predator_position it)
{
    if(it.x == -10 && it.y == -10) return 0;
    return 1;
}

int predator_isContact(predator_position predator, predator_position prey)
{
    if(predator.x == prey.x-1 ||
       predator.x == prey.x+1 ||
       predator.y == prey.y-1 ||
       predator.y == prey.y+1 )
       {
           return 1;
       }
    return 0;
}

int predator_isOtherExist(int self_id, predator_position prey, int dir)
{
    switch(dir)
    {
        case 'u':
            if(predator_map[self_id][prey.x-1][prey.y]>0 && predator_map[self_id][prey.x-1][prey.y] != self_id+1)return 1;
            return 0;
            break;
        case 'r':
            if(predator_map[self_id][prey.x][prey.y+1]>0 && predator_map[self_id][prey.x][prey.y+1] != self_id+1)return 1;
            return 0;
            break;
        case 'd':
            if(predator_map[self_id][prey.x+1][prey.y]>0 && predator_map[self_id][prey.x+1][prey.y] != self_id+1)return 1;
            return 0;
            break;
        case 'l':
            if(predator_map[self_id][prey.x][prey.y-1]>0 && predator_map[self_id][prey.x][prey.y-1] != self_id+1)return 1;
            return 0;
            break;
    }
}

int predator_isExist(int self_id, predator_position prey, int dir)
{
    switch(dir)
    {
        case 'u':
            if(predator_map[self_id][prey.x-1][prey.y]>0)return 1;
            return 0;
            break;
        case 'r':
            if(predator_map[self_id][prey.x][prey.y+1]>0)return 1;
            return 0;
            break;
        case 'd':
            if(predator_map[self_id][prey.x+1][prey.y]>0)return 1;
            return 0;
            break;
        case 'l':
            if(predator_map[self_id][prey.x][prey.y-1]>0)return 1;
            return 0;
            break;
    }
}

int predator_strategy(int self_id)
{
    predator_position predator1;
    predator_position predator2;
    predator_position predator3;
    predator_position predator4;
    predator_position prey;

    predator1.x = -10;
    predator1.y = -10;
    predator2.x = -10;
    predator2.y = -10;
    predator3.x = -10;
    predator3.y = -10;
    predator4.x = -10;
    predator4.y = -10;
    prey.x = -10;
    prey.y = -10;
    
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            switch(predator_map[self_id][i][j])
            {
                case 1:
                    predator1.x = i;
                    predator1.y = j;
                    break;
                case 2:
                    predator2.x = i;
                    predator2.y = j;
                    break;
                case 3:
                    predator3.x = i;
                    predator3.y = j;
                    break;
                case 4:
                    predator4.x = i;
                    predator4.y = j;
                    break;
                case 10:
                    prey.x = i;
                    prey.y = j;
                    break;
            }
            if(self_id==0)printf("%d,", predator_map[self_id][i][j]);
        }
        if(self_id==0)printf("\n");
    }
    predator_position self;
    switch(self_id)
    {
        case 0:
            self = predator1;
            break;
        case 1:
            self = predator2;
            break;
        case 2:
            self = predator3;
            break;
        case 3:
            self = predator4;
            break;
    }
    if(!predator_isVisible(prey))
    {
        //もし非捕食者が見えてなかったときの行動
        if(predator_isUnknown(predator_map[self_id],self,'u'))
        {
            return 'u';
        }else if(predator_isUnknown(predator_map[self_id],self,'r'))
        {
            return 'r';
        }else if(predator_isUnknown(predator_map[self_id],self,'d'))
        {
            return 'd';
        }else if(predator_isUnknown(predator_map[self_id],self,'l'))
        {
            return 'l';
        }
    }else
    {
        //捕食者が見えてるとき他の捕食者がどこに行くか計算し，自分の行く目標を立てる
        //predatorSearch(predator_map[id],from,to)で最短ルートの配列が帰ってくる．
        //配列の長さで最短ルートの長さなのかな
        int distance[4][4];//distance[id][dir]dir=> 0:u 1:r 2:d 3:l
        predator_position u_prey;
        int u_able = 0;
        int d_able = 0;
        int l_able = 0;
        int r_able = 0;
        if(prey.x > 0 && predator_map[self_id][prey.x-1][prey.y] > -1 && !predator_isOtherExist(self_id,prey,'u'))
        {
            u_able = 1;
            u_prey = prey;
            u_prey.x -= 1;
            if(self.x == u_prey.x && self.y == u_prey.y)
            {
                return 's';
            }
        }
        predator_position d_prey;
        if(prey.x < 16 && predator_map[self_id][prey.x+1][prey.y] > -1 && !predator_isOtherExist(self_id,prey,'d'))
        {
            d_able = 1;
            d_prey = prey;
            d_prey.x += 1;
            if(self.x == d_prey.x && self.y == d_prey.y)
            {
                return 's';
            }
        }
        predator_position l_prey;
        if(prey.y > 0 && predator_map[self_id][prey.x][prey.y-1] > -1 && !predator_isOtherExist(self_id,prey,'l'))
        {
            l_able = 1;
            l_prey = prey;
            l_prey.y -= 1;
            if(self.x == l_prey.x && self.y == l_prey.y)
            {
                return 's';
            }
        }
        predator_position r_prey;
        if(prey.y < 16 && predator_map[self_id][prey.x][prey.y+1] > -1 && !predator_isOtherExist(self_id,prey,'r'))
        {
            r_able = 1;
            r_prey = prey;
            r_prey.y += 1;
            if(self.x == r_prey.x && self.y == r_prey.y)
            {
                return 's';
            }
        }
        predator_position u_next;
        predator_position r_next;
        predator_position d_next;
        predator_position l_next;
        int temp_map[16][16];
        //printf("temp_map:id:%d\n",self_id);
        for(int i=0;i<16;i++)
        {
            for(int j=0;j<16;j++)
            {
                if(predator_map[self_id][i][j] > 0 && predator_map[self_id][i][j] != 10)
                {
                    if(predator_map[self_id][i][j] == self_id+1)
                    {
                        temp_map[i][j] = 1;
                    }else
                    {
                        temp_map[i][j] = -1;
                    }
                }else if(predator_map[self_id][i][j] == -10)
                {
                    temp_map[i][j] = -1;
                }else
                {
                    temp_map[i][j] = predator_map[self_id][i][j];
                }
                //printf("%d,",temp_map[i][j]);
            }
            //printf("\n");
        }
        if(u_able == 1)
        {
            //printf("u_search\n");
            predator_position *u_root = predatorSearch(temp_map, self, u_prey);
            distance[self_id][0] = sizeof(u_root)/sizeof(u_root[0]);
            u_next = u_root[1];
            free(u_root);

        }else
        {
            distance[self_id][0] = 99;
        }
        if(r_able == 1)
        {
            //printf("r_search\n");
            predator_position *r_root = predatorSearch(temp_map, self, r_prey);
            distance[self_id][1] = sizeof(r_root)/sizeof(r_root[0]);
            r_next = r_root[1];
            free(r_root);
        }else
        {
            distance[self_id][1] = 99;
        }
        if(d_able == 1)
        {
            //printf("d_search\n");
            predator_position *d_root = predatorSearch(temp_map, self, d_prey);
            distance[self_id][2] = sizeof(d_root)/sizeof(d_root[0]);
            d_next = d_root[1];
            free(d_root);
        }else
        {
            distance[self_id][2] = 99;
        }
        if(l_able == 1)
        {
            //printf("l_search\n");
            predator_position *l_root = predatorSearch(temp_map, self, l_prey);
            distance[self_id][3] = sizeof(l_root)/sizeof(l_root[0]);
            l_next = l_root[1];
            free(l_root);
        }else
        {
            distance[self_id][3] = 99;
        }

        int p_id[4][3];
        predator_position p_pos[4][3];
        p_pos[0][0]=predator2;
        p_id[0][0] = 1;
        p_pos[0][1]=predator3;
        p_id[0][1] = 2;
        p_pos[0][2]=predator4;
        p_id[0][2] = 3;
        
        p_pos[1][0]=predator1;
        p_id[1][0] = 0;
        p_pos[1][1]=predator3;
        p_id[1][1] = 2;
        p_pos[1][2]=predator4;
        p_id[1][2] = 3;
        
        p_pos[2][0]=predator1;
        p_id[2][0] = 1;
        p_pos[2][1]=predator2;
        p_id[2][1] = 1;
        p_pos[2][2]=predator4;
        p_id[2][2] = 1;

        p_pos[3][0]=predator1;
        p_id[3][0] = 1;
        p_pos[3][1]=predator2;
        p_id[3][1] = 1;
        p_pos[3][2]=predator3;
        p_id[3][2] = 1;

        for(int id=0;id>3;id++)
        {
            if(predator_isVisible(p_pos[self_id][id]) && predator_isContact(p_pos[self_id][id],prey))
            {
                if(u_able == 1)
                {
                    predator_position *u_tmp;
                    u_tmp = predatorSearch(predator_map[p_id[self_id][id]], p_pos[self_id][id], u_prey);
                    distance[p_id[self_id][id]][0] = sizeof(u_tmp)/sizeof(u_tmp[0]);
                    free(u_tmp);
                }else
                {
                    distance[p_id[self_id][id]][0] = 99;
                }
                if(r_able == 1)
                {
                    predator_position *r_tmp;
                    r_tmp = predatorSearch(predator_map[p_id[self_id][id]], p_pos[self_id][id], r_prey);
                    distance[p_id[self_id][id]][1] = sizeof(r_tmp)/sizeof(r_tmp[0]);
                    free(r_tmp);
                }else
                {
                    distance[p_id[self_id][id]][1] = 99;
                }
                if(d_able == 1)
                {
                    predator_position *d_tmp;
                    d_tmp = predatorSearch(predator_map[p_id[self_id][id]], p_pos[self_id][id], d_prey);
                    distance[p_id[self_id][id]][2] = sizeof(d_tmp)/sizeof(d_tmp[0]);
                    free(d_tmp);
                }else
                {
                    distance[p_id[self_id][id]][2] = 99;
                }
                if(l_able == 1)
                {
                    predator_position *l_tmp;
                    l_tmp = predatorSearch(predator_map[p_id[self_id][id]], p_pos[self_id][id], l_prey);
                    distance[p_id[self_id][id]][3] = sizeof(l_tmp)/sizeof(l_tmp[0]);
                    free(l_tmp);
                }else
                {
                    distance[p_id[self_id][id]][3] = 99;
                }
            }
        }

       //distance使ってどこに行くか決める．
        int rank[4][4];//[dir][rank]
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                rank[i][j] = -1;
            }
        }
        for(int dir=0;dir<4;dir++)
        {
            for(int unit=0;unit<4;unit++)
            {
                for(int r=0;r<4;r++)
                {
                    if(rank[dir][r] == -1)
                    {
                        rank[dir][r] = unit;
                        break;
                    }
                    if(distance[unit][dir] < distance[rank[dir][r]][dir])
                    {
                        for(int i=3;i>r;i--)
                        {
                            if(rank[dir][r] == -1)break;
                            int tmp = rank[dir][i+1];
                            rank[dir][i+1] = rank[dir][i];
                            rank[dir][i] = tmp;
                        }
                        rank[dir][r] = unit;
                    }
                }
            }
        }

        int decide[4];
        for(int dir=0;dir<4;dir++)
        {
            //埋まっている方向はスキップ
            int char_dir;
            switch(dir)
            {
                case 0:
                    char_dir = 'u';
                    break;
                case 1:
                    char_dir = 'r';
                    break;
                case 2:
                    char_dir = 'd';
                    break;
                case 3:
                    char_dir = 'l';
                    break;
            }
            if(predator_isExist(self_id,prey,char_dir))
            {
                continue;
            }
            for(int r=0;r<4;r++)
            {
                decide[dir] = rank[dir][r];
                int flag = 0;
                for(int i=0;i<4;i++)
                {
                    if(dir == i)continue;
                    if(decide[dir] == decide[i])
                    {
                        flag = 1;
                    }
                }
                if(flag)break;
            }
        }
        for(int i=0;i<4;i++)
        {
            if(decide[i]==self_id)
            {
                switch(i)
                {
                    case 0:
                        if(self.y == u_next.y)
                        {
                            if(self.x - u_next.x > 0)
                            {
                                return 'u';
                            }else
                            {
                                return 'd';
                            }
                        }
                        if(self.x == u_next.x) 
                        {
                            if(self.y - u_next.y > 0)
                            {
                               return 'l';
                            }else
                            {
                                return 'r';
                            }
                        }
                        break;
                    case 1:
                        if(self.y == r_next.y)
                        {
                            if(self.x - r_next.x > 0)
                            {
                                return 'u';
                            }else
                            {
                                return 'd';
                            }
                        }
                        if(self.x == r_next.x) 
                        {
                            if(self.y - r_next.y > 0)
                            {
                                return 'l';
                            }else
                            {
                                return 'r';
                            }
                        }
                        break;
                    case 2:
                        if(self.y == d_next.y)
                        {
                            if(self.x - d_next.x > 0)
                            {
                                return 'u';
                            }else
                            {
                                return 'd';
                            }
                        }
                        if(self.x == d_next.x) 
                        {
                            if(self.y - d_next.y > 0)
                            {
                                return 'l';
                            }else
                            {
                                return 'r';
                            }
                        }
                        break;
                    case 3:
                        if(self.y == l_next.y)
                        {
                            if(self.x - l_next.x > 0)
                            {
                                return 'u';
                            }else
                            {
                                return 'd';
                            }
                        }
                        if(self.x == l_next.x) 
                        {
                            if(self.y - l_next.y > 0)
                            {
                                return 'l';
                            }else
                            {
                                return 'r';
                            }
                        }
                        break;
                }
            }
        }
        //まだ４人の所在がつかめないとき
        //一番近いところに行く
        //埋まってないうちの
        int min = 99;
        int min_i = 0;
        for(int i=0;i<4;i++)
        {
            //埋まっている方向はスキップ
            int char_dir;
            switch(i)
            {
                case 0:
                    char_dir = 'u';
                    break;
                case 1:
                    char_dir = 'r';
                    break;
                case 2:
                    char_dir = 'd';
                    break;
                case 3:
                    char_dir = 'l';
                    break;
            }
            if(predator_isExist(self_id,prey,char_dir))
            {
                continue;
            }
            if(distance[self_id][i]<min)
            {
                min = distance[self_id][i];
                min_i = i;
            }
        }
        switch(min_i)
        {
            case 0:
                if(self.y == u_next.y)
                {
                    if(self.x - u_next.x > 0)
                    {
                        return 'u';
                    }else
                    {
                        return 'd';
                    }
                }
                if(self.x == u_next.x) 
                {
                    if(self.y - u_next.y > 0)
                    {
                        return 'l';
                    }else
                    {
                        return 'r';
                    }
                }
                break;
            case 1:
                if(self.y == r_next.y)
                {
                    if(self.x - r_next.x > 0)
                    {
                        return 'u';
                    }else
                    {
                        return 'd';
                    }
                }
                if(self.x == r_next.x) 
                {
                    if(self.y - r_next.y > 0)
                    {
                        return 'l';
                    }else
                    {
                        return 'r';
                    }
                }
                break;
            case 2:
                if(self.y == d_next.y)
                {
                    if(self.x - d_next.x > 0)
                    {
                        return 'u';
                    }else
                    {
                        return 'd';
                    }
                }
                if(self.x == d_next.x) 
                {
                    if(self.y - d_next.y > 0)
                    {
                        return 'l';
                    }else
                    {
                        return 'r';
                    }
                }
                break;
            case 3:
                if(self.y == l_next.y)
                {
                    if(self.x - l_next.x > 0)
                    {
                        return 'u';
                    }else
                    {
                        return 'd';
                    }
                }
                if(self.x == l_next.x) 
                {
                    if(self.y - l_next.y > 0)
                    {
                        return 'l';
                    }else
                    {
                        return 'r';
                    }
                }
                break;
        }
    }

}

void Predator1(int world[16][16], int* action)
{
    *action = predator_strategy(0);
    return;
}

void Predator2(int world[16][16], int* action)
{
    *action = predator_strategy(1);
    return;
}

void Predator3(int world[16][16], int* action)
{
    *action = predator_strategy(2);
    return;
}

void Predator4(int world[16][16], int* action)
{
    *action = predator_strategy(3);
    return;
}

void Predator(int world1[16][16], int world2[16][16], int world3[16][16], int world4[16][16], 
                int* action1, int* action2, int* action3, int* action4)
{
    if(predator_flag == 1)
    {
        //printf("初期化");
        for(int id=0;id<4;id++)
        {
            for(int i=0;i<16;i++)
            {
                for(int j=0;j<16;j++)
                {
                    predator_map[id][i][j] = -10;
                }
            }
        }
        predator_flag = 0;
    }

    int world[4][16][16];
    /*
    world[0] = world1;
    printf("%d\n",world[0][0][0]);
    world[1] = world2;
    world[2] = world3;
    world[3] = world4;
    */
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            world[0][i][j] = world1[i][j];
            world[1][i][j] = world2[i][j];
            world[2][i][j] = world3[i][j];
            world[3][i][j] = world4[i][j];
        }
    }
    //printf("%d\n",world[0][0][0]);

    int exists[4][4];
    int prey_exists[4];

    //ここで通信
    for(int id=0;id<4;id++)
    {        
        for(int i=0;i<4;i++)
        {
            exists[id][i] = 0;
        }
        prey_exists[id] = 0;

        //自分の状況をそれぞれmapに落とし込む
         //見える範囲の状況
        for(int i=0;i<16;i++)
        {
            for(int j=0;j<16;j++)
            {
                switch(world[id][i][j])
                {
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                        exists[id][world[id][i][j]-1] = 1;
                        break;
                    case 10:
                        prey_exists[id] = 1;
                        break;
                    default:
                        break;
                }

                //自分のマップにデータ落とし込む
                if(world[id][i][j] != -10)
                {
                    predator_map[id][i][j] = world[id][i][j];
                }
                //if(id == 3)printf("%d,", predator_map[id][i][j]);
            }
            //if(id == 3)printf("\n");
        }
    }

    for(int id=0;id<4;id++)
    {
        for(int e=0;e<4;e++)
        {
            if(id == e) continue;
            if(exists[id][e] == 0) continue;
            //printf("%dと%dが通信\n",id,e);
            for(int i=0;i<16;i++)
            {
                for(int j=0;j<16;j++)
                {
                    if(predator_map[id][i][j] == id+1)
                    {
                        predator_map[e][i][j] = predator_map[id][i][j];
                    }else if(predator_map[id][i][j] == 10)
                    {
                        if(prey_exists[id] == 1)
                        {
                            predator_map[e][i][j] = predator_map[id][i][j];
                        }else
                        {
                            predator_map[id][i][j] = predator_map[e][i][j];
                        }
                    }else if(predator_map[e][i][j] != -10)
                    {
                        predator_map[id][i][j] = predator_map[e][i][j];
                    }
                }
            }
        }
    }

    Predator1(world1, action1);
    Predator2(world2, action2);
    Predator3(world3, action3);
    Predator4(world4, action4);
    return;
}

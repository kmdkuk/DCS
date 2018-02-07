int predator_map[4][16][16];
int predator_flag = 1;

typedef struct{
  int x;
  int y;
} predator_position;

int isWall(int world[16][16], predator_position self, int dir)
{
    if(dir == 'u')
    {
        for(int x = self.x;x>0;x--)
        {
            if(world[x][self.y] == -10) return 1;
        }
    }else if(dir == 'r')
    {
        for(int y = self.y;y<16;y++)
        {
            if(world[self.x][y] == -10) return 1;
        }
    }else if(dir == 'd')
    {
        for(int x = self.x;x<16;x++)
        {
            if(world[x][self.y] == -10) return 1;
        }
    }else if(dir == 'l')
    {
        for(int y = self.y;y>0;y--)
        {
            if(world[self.x][y] == -10) return 1;
        }
    }
    return 0;
}

void Predator1(int world[16][16], int* action)
{
    predator_position predator1;
    predator_position predator2;
    predator_position predator3;
    predator_position predator4;
    predator_position prey;

    int self_id = 0;

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
            printf("%d,", predator_map[self_id][i][j]);
        }
        printf("\n");
    }
    predator_position self = predator1;
    if(prey.x == -10 && prey.y == -10)
    {
        //もし非捕食者が見えてなかったときの行動
        if(isWall(predator_map[self_id],self,'u'))
        {
            *action='u';
        }else if(isWall(predator_map[self_id],self,'r'))
        {
            *action='r';
        }else if(isWall(predator_map[self_id],self,'d'))
        {
            *action='d';
        }else if(isWall(predator_map[self_id],self,'l'))
        {
            *action='l';
        }
    }
    //捕食者が見えてるとき他の捕食者がどこに行くか計算し，自分の行く目標を立てる
    return;
}

void Predator2(int world[16][16], int* action)
{
    predator_position predator1;
    predator_position predator2;
    predator_position predator3;
    predator_position predator4;
    predator_position prey;

    int self_id = 1;

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
            //printf("%d,", predator_map[self_id][i][j]);
        }
        //printf("\n");
    }
    predator_position self = predator2;
    if(prey.x == -10 && prey.y == -10)
    {
        //もし非捕食者が見えてなかったときの行動
        if(isWall(predator_map[self_id],self,'u'))
        {
            *action='u';
        }else if(isWall(predator_map[self_id],self,'r'))
        {
            *action='r';
        }else if(isWall(predator_map[self_id],self,'d'))
        {
            *action='d';
        }else if(isWall(predator_map[self_id],self,'l'))
        {
            *action='l';
        }
    }
    //捕食者が見えてるとき他の捕食者がどこに行くか計算し，自分の行く目標を立てる
    return;
}

void Predator3(int world[16][16], int* action)
{
    predator_position predator1;
    predator_position predator2;
    predator_position predator3;
    predator_position predator4;
    predator_position prey;

    int self_id = 2;

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
        }
    }
    predator_position self = predator3;
    if(prey.x == -10 && prey.y == -10)
    {
        //もし非捕食者が見えてなかったときの行動
        if(isWall(predator_map[self_id],self,'u'))
        {
            *action='u';
        }else if(isWall(predator_map[self_id],self,'r'))
        {
            *action='r';
        }else if(isWall(predator_map[self_id],self,'d'))
        {
            *action='d';
        }else if(isWall(predator_map[self_id],self,'l'))
        {
            *action='l';
        }
    }
    //捕食者が見えてるとき他の捕食者がどこに行くか計算し，自分の行く目標を立てる
    return;
}

void Predator4(int world[16][16], int* action)
{
    predator_position predator1;
    predator_position predator2;
    predator_position predator3;
    predator_position predator4;
    predator_position prey;

    int self_id = 3;

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
        }
    }
    predator_position self = predator4;
    if(prey.x == -10 && prey.y == -10)
    {
        //もし非捕食者が見えてなかったときの行動
        if(isWall(predator_map[self_id],self,'u'))
        {
            *action='u';
        }else if(isWall(predator_map[self_id],self,'r'))
        {
            *action='r';
        }else if(isWall(predator_map[self_id],self,'d'))
        {
            *action='d';
        }else if(isWall(predator_map[self_id],self,'l'))
        {
            *action='l';
        }
    }
    //捕食者が見えてるとき他の捕食者がどこに行くか計算し，自分の行く目標を立てる
    return;
}

void Predator(int world1[16][16], int world2[16][16], int world3[16][16], int world4[16][16], 
                int* action1, int* action2, int* action3, int* action4)
{
    if(predator_flag == 1)
    {
        printf("初期化");
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

    //ここで通信
    for(int id=0;id<4;id++)
    {        
        for(int i=0;i<4;i++)
        {
            exists[id][i] = 0;
        }

        //自分の状況をそれぞれmapに落とし込む
         //見える範囲の状況
        for(int i=0;i<16;i++)
        {
            for(int j=0;j<16;j++)
            {
                //printf("%d,", world[id][i][j]);
                switch(world[id][i][j])
                {
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                        exists[id][world[id][i][j]-1] = 1;
                        break;
                    case 10:
                        break;
                    default:
                        break;
                }

                //自分のマップにデータ落とし込む
                if(world[id][i][j] != -10)
                {
                    predator_map[id][i][j] = world[id][i][j];
                }

            }
            //printf("\n");
        }
    }

    for(int id=0;id<4;id++)
    {
        for(int e=0;e<4;e++)
        {
            if(id == e) continue;
            if(exists[id][e] == 0) continue;
            printf("%dと%dが通信\n",id,e);
            for(int i=0;i<16;i++)
            {
                for(int j=0;j<16;j++)
                {
                    if(predator_map[e][i][j] != -10)
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

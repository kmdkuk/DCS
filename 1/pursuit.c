/*
 * 2 Players Pursuit Game ´ÉÍý¥×¥í¥°¥é¥à
 * version 1.2 SP2
 *
 * by E. Osawa and E. Yoshikawa, Sept 2002.
 * 
 * last revision by E. Osawa Oct. 2002
 *
 * (ÊÑ¹¹ÍúÎò)
 * 2002.10.1            ¾ã³²Êª,¼«Í³³Ê»Ò,Êá¿©¼Ô,³ÍÊª¤òÉ½¤¹Äê¿ô¤ÎÆ³Æþ
 *
 * 2000.12.26(1.2.1)    ¥³¥á¥ó¥ÈÄÉ²Ã
 *                      thread¥­¥ã¥ó¥»¥ë»þ¤Îsegmentation fault¤Î²ò¾Ã
 * 2000.12.25(1.2)      watch dog timer¤òÄÉ²Ã¡¥
 *                      Prey¤äPredator¤Î¼Â¹Ô»þ´Ö¤¬1ÉÃ¤«´Æ»ë¤¹¤ë¡¥
 * 2000.12.20(1.1 SP2): ¥ª¥×¥·¥ç¥ó¤Ë´Ø¤¹¤ë¥¨¥é¡¼½èÍý¤ò¶¯²½¡£
 *                      Éé¤ÎÃÍ¤ò»ØÄê¤¹¤ë¤ÈÌµ¸Â¥ë¡¼¥×¤Ë´Ù¤ë¸½¾Ý¤ä¡¢
 *                      ¥ª¥×¥·¥ç¥ó¤Î¤ß¤¬»ØÄê¤µ¤ì¤Æ¤â¥¨¥é¡¼¤ò½Ð¤µ¤Ê¤¤¸½¾Ý¡¢
 *                      Ì¤ÄêµÁ¤Î¥ª¥×¥·¥ç¥ó¤ËÂÐ¤·¤Æ¥¨¥é¡¼¤ò½Ð¤µ¤Ê¤¤¸½¾Ý¤Ê¤É¤ò
 *                      ²þÁ±
 *
 * 2000.12.20(1.1 SP1): Prey¤äPredator¤Î·×»»ÀêÍ­»þ´Ö¤Ë¤è¤Ã¤Æ¡¢É½¼¨¤Î¹¹¿·¤¬
 *                      ¤Á¤é¤Ä¤¯¸½¾Ý¤ò²þÁ±
 *                      ¥Ç¥Õ¥©¥ë¥È¤Î³Ê»ÒÀ¤³¦¥Õ¥¡¥¤¥ë¤ò"battlefield.txt"¤«¤é
 *                      "battlefield.dat"¤ËÊÑ¹¹
 * 
 * 2000.12.20(1.1)    : É½¼¨¤ÎºÝ¤Ë¤¤¤ì¤ë¥¦¥§¥¤¥È(¤Î¥Ç¥Õ¥©¥ë¥È)¤ò0.5ÉÃ¤ËÄ´À°
 *                      ¥²¡¼¥à¥¹¥Æ¥Ã¥×¿ô(¤Î¥Ç¥Õ¥©¥ë¥È)¤ò30¤ËÊÑ¹¹
 *                      ¥²¡¼¥à¥¹¥Æ¥Ã¥×¿ô¤ò"-s 30",¥¦¥§¥¤¥È¤ÎÂç¤­¤µ¤ò
 *                      "-t 500000",¤Þ¤¿¡¢½é´ü¥Ç¡¼¥¿¤¬³ÊÇ¼¤µ¤ì¤Æ¤¤¤ë
 *                      "-w battlefield2.txt"¤Î¤è¤¦¤Ë¡¢¼Â¹Ô¥Õ¥¡¥¤¥ë¤ËÂÐ¤¹¤ë
 *                      ¥ª¥×¥·¥ç¥ó¤È¤·¤Æruntime¤ËÆÉ¤ß¹þ¤á¤ë¤è¤¦¤ËÊÑ¹¹
 *                      Predator¤ÈPrey¤Î¾¡ÇÔ¤Ë´Ø¤¹¤ë¥á¥Ã¥»¡¼¥¸É½¼¨¤òÄÉ²Ã
 * 
 * 2000.12.19(1.0 SP2): ¹½Â¤ÂÎÌ¾¤òposition¢ªpursuit_position¤ØÊÑ¹¹
 *                      Prey¤ª¤è¤ÓPredator¤ØÅÏ¤¹³Ê»ÒÀ¤³¦¤ÎÇÛÎó¤ò,
 *                      ¤½¤Î¤â¤Î¤Î»²¾ÈÅÏ¤·¢ª¥³¥Ô¡¼¤Î»²¾ÈÅÏ¤·¤ËÊÑ¹¹
 *                      (Predator¤äPrey¤¬³Ê»ÒÀ¤³¦¤ò½ñ¤­´¹¤¨¤ë¤³¤È¤òËÉ¤°¤¿¤á)
 *                      Prey¤¬¡Ö3²ó¤Î¤¦¤Á¤Ë2²ó¤À¤±Æ°¤±¤ë¡×¤È¤¤¤¦»ÅÍÍ¤Î²ò¼á¤ò
 *                      ÊÑ¹¹¡¢¡ÖÆ°¤±¤ë³ÎÎ¨66¡ó¡×¤È¤¤¤¦³ÎÎ¨Åª¤ÊµóÆ°¤«¤é
 *                     ¡Ö2²óÆ°¤¤¤Æ1²óµÙ¤à¡×¤È¤¤¤¦³ÎÄêÅª¤ÊµóÆ°¤Ø
 *
 * 2000.12.15(1.0 SP1): »ÅÍÍ¤Ë¹çÃ×¤·¤Æ¤¤¤Ê¤¤ÅÀ¤ò²þÁ±
 *                      (ÇÛÎó¤Î½Ä¤È²£¤¬µÕÅ¾¤·¤Æ¤¤¤¿¤Î¤ò½¤Àµ)
 */


#define VERSION_1_2 1

/*
 * É¬Í×¤Ê¥é¥¤¥Ö¥é¥ê¤Î¥í¡¼¥É
 * (stdio.h¤ª¤è¤Óstdlib.h)
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

#ifdef VERSION_1_2
#ifndef PTHREAD_H
#include <pthread.h>
#endif /* PTHREAD_H */
#endif /* VERSION_1_2 */

/* predator¤Î¿ôÃÍÉ½¸½ */
#ifndef VALUE_OF_PREDATOR
#define VALUE_OF_PREDATOR 1
#endif

/* prey¤Î¿ôÃÍÉ½¸½ */
#ifndef VALUE_OF_PREY
#define VALUE_OF_PREY 10
#endif

/* obstacle¤Î¿ôÃÍÉ½¸½ */
#ifndef VALUE_OF_OBSTACLE
#define VALUE_OF_OBSTACLE -1
#endif

/* free grid¤Î¿ôÃÍÉ½¸½ */
#ifndef VALUE_OF_FREE
#define VALUE_OF_FREE 0
#endif

/* ³Ê»ÒÀ¤³¦¤ÎÂç¤­¤µ */
#ifndef WORLD_SIZE
#define WORLD_SIZE 8
#endif
 
/* ·«¤êÊÖ¤·¥¹¥Æ¥Ã¥×¿ô(¥Ç¥Õ¥©¥ë¥ÈÃÍ) */
#ifndef GAME_NUM
#define GAME_NUM 30
#endif

/* VALID(ÂÅÅö¤Ç¤¢¤ë) */
#ifndef VALID
#define VALID 1
#endif

/* INVALID(ÂÅÅö¤Ç¤Ê¤¤) */
#ifndef INVALID
#define INVALID 0
#endif

/* ³Ê»ÒÀ¤³¦¥Õ¥¡¥¤¥ëÌ¾¤ÎºÇÂçÊ¸»ú¿ô */
#ifndef WORLD_FILE_NAME_LENGTH
#define WORLD_FILE_NAME_LENGTH 256
#endif

/* É½¼¨¤Î¥¦¥§¥¤¥È(¥Ç¥Õ¥©¥ë¥ÈÃÍ) */
#ifdef VERSION_1_2
#ifndef DISPLAY_WAIT
#define DISPLAY_WAIT 0
#endif
#else /* VERSION_1_2 */
#ifndef DISPLAY_WAIT
#define DISPLAY_WAIT 500000
#endif
#endif /* VERSION_1_2 */

/*
 *Predator¤ª¤è¤ÓPrey¤Î°ÌÃÖ¤òÉ½¤¹¹½Â¤ÂÎ
 */
typedef struct{
  int x;
  int y;
} pursuit_position;


#ifdef VERSION_1_2

/* 
 * watch dog timerÍÑ¤Î¹½ÂÎ
 */
typedef struct{
  pthread_mutex_t mutex; /* ÇÓÂ¾À©¸æÍÑ */
  int count;             /* watch dog timer */
  int state;             /* watch dog state */
}watchdog_t;

static watchdog_t wdtimer =
{
  PTHREAD_MUTEX_INITIALIZER,
  0,
  0
};

#define WATCHDOG_COUNT_INIT  1
#define WATCHDOG_INTERVAL 1000000 /* usec */

#define WATCHDOG_RUN           1 /* WD status */
#define WATCHDOG_STOP          0 /* WD status */

pthread_t wd_tid;     /* Watch dog ¥¹¥ì¥Ã¥É¤Îthread ID */
pthread_t player_tid; /* Prey/Predator ¥¹¥ì¥Ã¥É¤Îthread ID */

#endif /* VERSION_1_2 */


/*
 * ½é´ü¾õÂÖ¥Ç¡¼¥¿¥Õ¥¡¥¤¥ë¤ÎÆÉ¤ß¹þ¤ß
 * int battleFieldArray[WORLD_SIZE][WORLD_SIZE]
 *      : ³Ê»ÒÀ¤³¦¤òÉ½¤¹WORLD_SIZE*WORLD_SIZE¤ÎÀ°¿ô·¿2¼¡¸µÇÛÎó
 * char *fileName: ³Ê»ÒÀ¤³¦¥Õ¥¡¥¤¥ëÌ¾¤¬³ÊÇ¼¤µ¤ì¤¿Ê¸»úÎó
 * ÊÖ¤êÃÍ:Àµ¾ï½ªÎ»¤Ê¤é0,°Û¾ï½ªÎ»¤Ê¤é1
 */
int ReadInitConf(int battleFieldArray[WORLD_SIZE][WORLD_SIZE], char *fileName){
  FILE *fp;
  int i, j;

  fp = fopen(fileName, "r");
  if (fp == NULL){
    /* ¥Õ¥¡¥¤¥ë¥ª¡¼¥×¥ó¥¨¥é¡¼ */
    return(1);
  }
  else{
    for (i = 0; i < WORLD_SIZE; i++){
      for (j = 0; j < WORLD_SIZE; j++){

	if (EOF == fscanf(fp,"%d", &battleFieldArray[i][j])){
	  /* ¥Õ¥¡¥¤¥ë¤ÎÄ¹¤µ¤¬ÁÛÄê¤·¤Æ¤¤¤¿¤è¤ê¤âÃ»¤¤¥¨¥é¡¼ */
	  return(1);
	}

      }
    }

    fclose(fp);
    return(0);
  }
}

/*
 * ³Ê»ÒÀ¤³¦¤òÉ½¼¨¤¹¤ë´Ø¿ô
 * int battleFieldArray[WORLD_SIZE][WORLD_SIZE]
 *      : ³Ê»ÒÀ¤³¦¤òÉ½¤¹WORLD_SIZE*WORLD_SIZE¤ÎÀ°¿ô·¿2¼¡¸µÇÛÎó
 * int clockNum: ¸½ºß¤Î¥¯¥í¥Ã¥¯¿ô
 * ÊÖ¤êÃÍ:Àµ¾ï½ªÎ»¤Ê¤é0,°Û¾ï½ªÎ»¤Ê¤é1
 */
int PrintWorld(int battleFieldArray[WORLD_SIZE][WORLD_SIZE], int clockNum){
  int i, j;

  printf("clock %d\n", clockNum);
  for (i = 0; i < WORLD_SIZE; i++){
    for (j = 0; j < WORLD_SIZE; j++){

      switch(battleFieldArray[i][j]){
      case VALUE_OF_OBSTACLE: /* ¾ã³²Êª */
	printf ("#");
	break;
      case VALUE_OF_FREE: /* ¼«Í³³Ê»Ò */
	printf(".");
	break;
      case VALUE_OF_PREDATOR: /* Predator */
	printf("@");
	break;
      case VALUE_OF_PREY: /* Prey */
	printf("*");
	break;
      default: /* ¤³¤³¤Ë¤ÏËÜÍèÅþÃ£¤·¤Ê¤¤¤Ï¤º */
	fprintf(stderr, "%d\n",battleFieldArray[i][j]);
	fprintf(stderr, "Execution Error!! \n");
	return(1);
	break;
      }
    }
    printf("\n");
  }
  printf("\n");
  return(0);
}

/*
 * Predator¤Î°ÌÃÖºÂÉ¸¤ò¼èÆÀ¤¹¤ë
 * int battleFieldArray[WORLD_SIZE][WORLD_SIZE]
 *      : ³Ê»ÒÀ¤³¦¤òÉ½¤¹WORLD_SIZE*WORLD_SIZE¤ÎÀ°¿ô·¿2¼¡¸µÇÛÎó
 * ÊÖ¤êÃÍ:Predator¤Î°ÌÃÖºÂÉ¸¤òÉ½¤¹pursuit_position¹½Â¤ÂÎ
 */
pursuit_position getPredatorPosition
(int battleFieldArray[WORLD_SIZE][WORLD_SIZE]){
  
  int i,j;
  pursuit_position returnPosition;

  /*
   * battleFieldArray¤Î¤Ê¤«¤Ç¡¢ÃÍ¤¬VALUE_OF_PREDATOR¤Ë¤Ê¤Ã¤Æ¤¤¤ë¤È¤³¤í¤ò
   * Ãµ¤·¤Æ¡¢¤½¤ÎºÂÉ¸¤òreturnPosition¤ËÂåÆþ¤·¤Æreturn¤¹¤ë
   */
  for (i=0; i<WORLD_SIZE; i++){
    for (j=0; j<WORLD_SIZE; j++){
      if (battleFieldArray[i][j] == VALUE_OF_PREDATOR){
	returnPosition.x=j;
	returnPosition.y=i;
	return returnPosition;
      }
    }
  }

  /*
   * ¤³¤³¤Þ¤Ç½èÍý¤¬Íè¤ë¤È¤¤¤¦¤³¤È¤Ï°Û¾ï»öÂÖ¤Ê¤Î¤Ç¡¢position¤È¤·¤Æ
   * (-1,-1)¤òÊÖ¤¹
   */
  returnPosition.x=-1;
  returnPosition.y=-1;
  return returnPosition;
}

/*
 * Prey¤Î°ÌÃÖºÂÉ¸¤ò¼èÆÀ¤¹¤ë
 * int battleFieldArray[WORLD_SIZE][WORLD_SIZE]
 *      : ³Ê»ÒÀ¤³¦¤òÉ½¤¹WORLD_SIZE*WORLD_SIZE¤ÎÀ°¿ô·¿2¼¡¸µÇÛÎó
 * ÊÖ¤êÃÍ:Prey¤Î°ÌÃÖºÂÉ¸¤òÉ½¤¹pursuit_position¹½Â¤ÂÎ
 */
pursuit_position getPreyPosition
(int battleFieldArray[WORLD_SIZE][WORLD_SIZE]){
  
  int i,j;
  pursuit_position returnPosition;
  /*
   * battleFieldArray¤Î¤Ê¤«¤Ç¡¢ÃÍ¤¬VALUE_OF_PREY¤Ë¤Ê¤Ã¤Æ¤¤¤ë¤È¤³¤í¤ò
   * Ãµ¤·¤Æ¡¢¤½¤ÎºÂÉ¸¤òreturnPosition¤ËÂåÆþ¤·¤Æreturn¤¹¤ë
   */
  for (i=0; i<WORLD_SIZE; i++){
    for (j=0; j<WORLD_SIZE; j++){
      if (battleFieldArray[i][j] == VALUE_OF_PREY){
	returnPosition.x=j;
	returnPosition.y=i;
	return returnPosition;
      }
    }
  }

  /*
   * ¤³¤³¤Þ¤Ç½èÍý¤¬Íè¤ë¤È¤¤¤¦¤³¤È¤Ï°Û¾ï»öÂÖ¤Ê¤Î¤Ç¡¢position¤È¤·¤Æ
   * (-1,-1)¤òÊÖ¤¹
   */
  returnPosition.x=-1;
  returnPosition.y=-1;
  return returnPosition;

}

/*
 * »ØÄê¤µ¤ì¤¿action¤Ë½¾¤Ã¤Æ¡¢ºÂÉ¸¤ò¹¹¿·¤¹¤ë
 * pursuit_position currentPosition: 
 * Predator¤Þ¤¿¤ÏPrey¤Î°ÌÃÖºÂÉ¸¤òÉ½¤¹pursuit_position¹½Â¤ÂÎ
 * int action: ¼¡¤Î¹ÔÆ°¤òÉ½¤¹Ê¸»ú(¤òint·¿¤ÇÉ½¤·¤¿¤â¤Î)
 * 'u','d','l','r','s'¤Î¤É¤ì¤«
 * ÊÖ¤êÃÍ:¹¹¿·¤µ¤ì¤¿°ÌÃÖºÂÉ¸¤òÉ½¤¹position¹½Â¤ÂÎ
 */
pursuit_position movePP(pursuit_position currentPosition, int action){
  switch(action){
  case 'u': /* ¾å¤Ë°ÜÆ° */
    currentPosition.y=currentPosition.y-1;
    break;
  case 'd': /* ²¼¤Ë°ÜÆ° */
    currentPosition.y=currentPosition.y+1;
    break;
  case 'l': /* º¸¤Ë°ÜÆ° */
    currentPosition.x=currentPosition.x-1;
    break;
  case 'r': /* ±¦¤Ë°ÜÆ° */
    currentPosition.x=currentPosition.x+1;
    break;
  case 's': /* ¤½¤Î¾ì¤ËÎ±¤Þ¤ë */
    break;
  default:  /* »ØÄê³°¤ÎÊ¸»ú¤ò»ØÄê¤·¤¿¾ì¹ç¤Ï's'¤ÈÅù²Á¤È¤ß¤Ê¤¹ */
    break;
  }

  return (currentPosition);

}

/*
 * °ÜÆ°¤·¤¿ºÂÉ¸¤ÎÂÅÅöÀ­¤ò¸¡Æ¤¤¹¤ë
 * pursuit_position currentPosition: 
 * Predator¤Þ¤¿¤ÏPrey¤Î°ÌÃÖºÂÉ¸¤òÉ½¤¹pursuit_position¹½Â¤ÂÎ
 * int battleFieldArray[WORLD_SIZE][WORLD_SIZE]
 *      : ³Ê»ÒÀ¤³¦¤òÉ½¤¹WORLD_SIZE*WORLD_SIZE¤ÎÀ°¿ô·¿2¼¡¸µÇÛÎó
 * ÊÖ¤êÃÍ: ÂÅÅö¤Ê¤é¤ÐVALID(=1),¤½¤¦¤Ç¤Ê¤±¤ì¤ÐINVALID(=0)
 */
int evalPosition(pursuit_position currentPosition, 
		 int battleFieldArray[WORLD_SIZE][WORLD_SIZE]){
  
  /* 
   * ¤³¤³¤ÇÄ´¤Ù¤Æ¤¤¤ë¤Î¤Ï,
   *   1. »ØÄê¤µ¤ì¤¿°ÌÃÖ¤¬¡¢WORLD_SIZE*WORLD_SIZE¤Î³Ê»ÒÀ¤³¦¤«¤é¤Ï¤ß½Ð¤·¤Æ
   *      ¤¤¤Ê¤¤¤«¤É¤¦¤«
   *   2. »ØÄê¤µ¤ì¤¿°ÌÃÖ¤Ë¾ã³²Êª¤¬Â¸ºß¤·¤Æ¤¤¤Ê¤¤¤«¤É¤¦¤«
   */
  if (currentPosition.x >=0 && currentPosition.x < WORLD_SIZE
      && currentPosition.y >= 0 && currentPosition.y < WORLD_SIZE
      && battleFieldArray[currentPosition.y][currentPosition.x] != -1){
    return VALID;
  }
  else{
    return INVALID;
  }

}

/*
 * ³Ê»ÒÀ¤³¦¤ò¹¹¿·¤¹¤ë
 * int battleFieldArray[WORLD_SIZE][WORLD_SIZE]
 *      : ³Ê»ÒÀ¤³¦¤òÉ½¤¹WORLD_SIZE*WORLD_SIZE¤ÎÀ°¿ô·¿2¼¡¸µÇÛÎó
 * int predatorAction: Predator¤Î¹ÔÆ°¤òÉ½¤¹Ê¸»ú(¤òint¤ÇÉ½¤·¤¿¤â¤Î)
 * ('u','d','l','r','s'¤Î¤É¤ì¤«)
 * int preyAction: prey¤Î¹ÔÆ°¤òÉ½¤¹Ê¸»ú(¤òint¤ÇÉ½¤·¤¿¤â¤Î)
 * ('u','d','l','r','s'¤Î¤É¤ì¤«)
 * ÊÖ¤êÃÍ: ³Ê»ÒÀ¤³¦¹¹¿·¤Î·ë²ÌPrey¤¬Êá³Í¤µ¤ì¤ì¤Ð1¡¢¤½¤¦¤Ç¤Ê¤±¤ì¤Ð0
 */
int RenewWorld(int battleFieldArray[WORLD_SIZE][WORLD_SIZE],
	       int predatorAction, int preyAction){

  /* Predator¤ÈPrey¤Î°ÌÃÖºÂÉ¸¤òÉ½¤¹position¹½Â¤ÂÎ */
  pursuit_position predatorPosition, preyPosition;
  pursuit_position newPredatorPosition, newPreyPosition;

  /* Predator¤ÈPrey¤Î¸½ºß°ÌÃÖ¤òÆÀ¤ë */
  predatorPosition = getPredatorPosition(battleFieldArray);
  preyPosition = getPreyPosition(battleFieldArray);

  /* °ÜÆ°¸å¤ÎPredator¤ÈPrey¤ÎºÂÉ¸¤òÆÀ¤ë */
  newPredatorPosition = movePP(predatorPosition, predatorAction);
  newPreyPosition = movePP(preyPosition, preyAction);

  /* battleFieldArray¤«¤é°ìÃ¶Predator¤ÈPrey¤òºï½ü */
  battleFieldArray[predatorPosition.y][predatorPosition.x] = 0;  
  battleFieldArray[preyPosition.y][preyPosition.x] = 0;

  /* ¤â¤·°ÜÆ°¸å¤ÎºÂÉ¸ÃÍ¤¬ÂÅÅö¤Ê¤é¤Ð */
  if (evalPosition(newPredatorPosition,battleFieldArray) == VALID){
    /* ¿·¤·¤¤ºÂÉ¸¤òpredatorPosition¤Ë¥³¥Ô¡¼ */
    predatorPosition.x = newPredatorPosition.x;
    predatorPosition.y = newPredatorPosition.y;    
  }

  /* ¤â¤·°ÜÆ°¸å¤ÎºÂÉ¸ÃÍ¤¬ÂÅÅö¤Ê¤é¤Ð */
  if (evalPosition(newPreyPosition,battleFieldArray) == VALID){
    /* ¿·¤·¤¤ºÂÉ¸¤òpreyPosition¤Ë¥³¥Ô¡¼ */    
    preyPosition.x = newPreyPosition.x;
    preyPosition.y = newPreyPosition.y;
  }

  /*
   * Prey(=VALUE_OF_PREY)¤ÈPredator(=VALUE_OF_PREDATOR)¤òºÆÇÛÃÖ¤¹¤ë 
   * ¤³¤Î½çÈÖ¤Ê¤Î¤Ï¡¢Predator¤¬Prey¤Ë¾å½ñ¤­¤µ¤ì¤ë¤Î¤Ï¤ª¤«¤·¤¤¤¿¤á
   */
  battleFieldArray[preyPosition.y][preyPosition.x] = VALUE_OF_PREY;
  battleFieldArray[predatorPosition.y][predatorPosition.x] = VALUE_OF_PREDATOR;

  /* ½ªÎ»È½Äê */
  if (predatorPosition.x == preyPosition.x 
      && predatorPosition.y == preyPosition.y){
    return(1);
  }
  else{
    return(0);
  }

}

/*
 * ³Ê»ÒÀ¤³¦¤Î¥³¥Ô¡¼¤ò¹Ô¤¦
 * int copy[WORLD_SIZE][WORLD_SIZE]: ¥³¥Ô¡¼Àè
 * int original[WORLD_SIZE][WORLD_SIZE]: ¥³¥Ô¡¼¸µ
 * ÊÖ¤êÃÍ: 0
 */
int copyWorld(int copy[WORLD_SIZE][WORLD_SIZE], 
	      int original[WORLD_SIZE][WORLD_SIZE]){
  int i,j;

  for (i=0; i<WORLD_SIZE; i++){
    for (j=0; j<WORLD_SIZE; j++){
      copy[i][j] = original[i][j];
    }
  }
  return(1);
}

#ifdef VERSION_1_2 
static int copy_array[WORLD_SIZE][WORLD_SIZE];     /* ³Ê»ÒÀ¤³¦(¥³¥Ô¡¼) */

/*
 * Watch dog timer¹½Â¤ÂÎ¤Î½é´üÀßÄê(¥¹¥¿¡¼¥È)
 */
static void setWatchdogTimer(){
  int status;

  /* ÇÓÂ¾À©¸æ»Ï¤Þ¤ê */
  status=pthread_mutex_lock(&(wdtimer.mutex));
  if(status != 0){
    fprintf(stderr,"mutex lock fail!!\n");
    abort();
  }
  
  /* ËÜÂÎ */
  wdtimer.count = WATCHDOG_COUNT_INIT;
  wdtimer.state = WATCHDOG_RUN; /* »þ´Ö¤Î´Æ»ë³«»Ï */

  /* ÇÓÂ¾À©¸æ½ª¤ï¤ê */
  status=pthread_mutex_unlock(&(wdtimer.mutex));
  if(status != 0){
    fprintf(stderr,"mutex unlock fail!!\n");
    abort();
  }
}

/*
 * Watch dog timer¤Î²ò½ü
 * 1ÉÃ¤ÎWaitÍÑ¤Ë¤â»ÈÍÑ
 */
static void resetWatchdogTimer(){
  int status;

  /* ÇÓÂ¾À©¸æ»Ï¤Þ¤ê */
  status=pthread_mutex_lock(&(wdtimer.mutex));
  if(status != 0){
    fprintf(stderr,"mutex lock fail!!\n");
    abort();
  }
  
  /* ËÜÂÎ */
  wdtimer.state = WATCHDOG_STOP; /* »þ´Ö¤Î´Æ»ë½ªÎ» */
  
  /* ÇÓÂ¾À©¸æ½ª¤ï¤ê */
  status=pthread_mutex_unlock(&(wdtimer.mutex));
  if(status != 0){
    fprintf(stderr,"mutex unlock fail!!\n");
    abort();
  }
}

/*
 * Watchdog timer¥¹¥ì¥Ã¥É¤ÎËÜÂÎ¡Ê´Ø¿ô)
 * void *arg:Prey/Predator¥¹¥ì¥Ã¥É¤Îthread ID¤Ø¤Î¥Ý¥¤¥ó¥¿
 */
static void *threadWatchdogTimer(void *arg){
  int status;
  pthread_t *tid = (pthread_t *) arg;
  int wdexit=0;

  setWatchdogTimer(); /* watchdog_t¹½Â¤ÂÎ¤Î½é´ü²½ */

  /* ÇÓÂ¾À©¸æ»Ï¤Þ¤ê */
  while(1){
    status=pthread_mutex_lock(&(wdtimer.mutex));
    if(status != 0){
      fprintf(stderr,"mutex lock fail!!\n");
      abort();
    }
  
    /* ËÜÂÎ */
    if(wdtimer.count == 0){
      if(wdtimer.state == WATCHDOG_RUN){
	/* »þ´ÖÆâ¤Ë½ª¤ï¤é¤Ê¤¤Prey/Predator¥¹¥ì¥Ã¥É¤ò¥­¥ã¥ó¥»¥ë¤¹¤ë */
	status = pthread_cancel(*tid); 
      }
      /* ¤³¤³¤Ï°ì»þ¥³¥á¥ó¥È¥¢¥¦¥È
      if(status != 0){
	fprintf(stderr,"pthread_cancel fail!!\n");
	abort();
      }
      */
      wdexit = 1; /* watchdog thread¤ò½ªÎ»¤¹¤ë¤¿¤á¤Î¥Õ¥é¥° */
    }
    else {
      /* watch dog timer¤Î¥«¥¦¥ó¥¿¤ò1°ú¤¯ */
      if(wdtimer.count>0){
	wdtimer.count--;
      }
      else{
	wdexit = 1; /* watchdog thread¤ò½ªÎ»¤¹¤ë¤¿¤á¤Î¥Õ¥é¥° */
      }
    }

    /* ÇÓÂ¾À©¸æ½ª¤ï¤ê */
    status=pthread_mutex_unlock(&(wdtimer.mutex));
    if(status != 0){
      fprintf(stderr,"mutex unlock fail!!\n");
      abort();
    }
    if(wdexit)
      {	
	/* watchdog thread¤ò½ªÎ»¤¹¤ë */
	pthread_exit(0);
      }
    usleep(WATCHDOG_INTERVAL);
  }
}

/*
 * Prey ¥¹¥ì¥Ã¥É¤ÎËÜÂÎ¡Ê´Ø¿ô)
 * void *arg:³Ê»Ò¶õ´Ö¤Ø¤Î¥Ý¥¤¥ó¥¿¡Êint *)
 */
static void *threadPrey(void *arg)
{
  static int Action;
  int *ca = arg;
  int cancel_type;
  int status;

  /* ÈóÆ±´ü¥­¥ã¥ó¥»¥ë¤ò²ÄÇ½¤Ë¤¹¤ë */
  status = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,
				 &cancel_type);
  if(status != 0){
    fprintf(stderr,"pthread_setcanceltype fail!!\n");
    abort();
  }

  Prey(ca, &Action);  
  resetWatchdogTimer();  /* watchdog timer¤ò½ªÎ»¤¹¤ë */
  pthread_exit(&Action); /* thread½ªÎ»»þ¤ÎÌá¤êÃÍ¤È¤·¤Æ¼¡¤ÎÆ°ºî¤òÊÖ¤¹ */
}

/*
 * Predator ¥¹¥ì¥Ã¥É¤ÎËÜÂÎ¡Ê´Ø¿ô)
 * void *arg:³Ê»Ò¶õ´Ö¤Ø¤Î¥Ý¥¤¥ó¥¿¡Êint *)
 */
static void *threadPredator(void *arg)
{
  static int Action;
  int *ca = arg;
  int cancel_type;
  int status;
  int i,j;

  /* ÈóÆ±´ü¥­¥ã¥ó¥»¥ë¤ò²ÄÇ½¤Ë¤¹¤ë */
  status = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,
				 &cancel_type);
  if(status != 0){
    fprintf(stderr,"pthread_setcanceltype fail!!\n");
    abort();
  }

  /*  usleep(1100*1000);*/
  /* for(;;) */
  Predator(ca, &Action);
  resetWatchdogTimer();  /* watchdog timer¤ò½ªÎ»¤¹¤ë */
  pthread_exit(&Action); /* thread½ªÎ»»þ¤ÎÌá¤êÃÍ¤È¤·¤Æ¼¡¤ÎÆ°ºî¤òÊÖ¤¹ */
}

#endif /* VERSION_1_2 */
/*
 * Pursuit Game¤Îmain´Ø¿ô
 * ÊÖ¤êÃÍ: Àµ¾ï½ªÎ»¤Ê¤é0,°Û¾ï½ªÎ»¤Ê¤é1
 */

int main(int argc, char *argv[]){
  int i;
  int array[WORLD_SIZE][WORLD_SIZE];          /* ³Ê»ÒÀ¤³¦(¥ª¥ê¥¸¥Ê¥ë) */
#ifndef VERSION_1_2
  int copy_array[WORLD_SIZE][WORLD_SIZE];     /* ³Ê»ÒÀ¤³¦(¥³¥Ô¡¼) */
#endif /* VERSION_1_2 */
  int gameStepNum;                            /* ¥²¡¼¥à¤Î¥¹¥Æ¥Ã¥×¿ô */
  int predatorAction, preyAction;             /* Predator¤äPrey¤ÎÆ°¤­¤òÉ½¤¹ */

#ifdef VERSION_1_2
  int status;                                 /* pthread_*´Ø¿ô¤ÎÌá¤êÃÍÍÑ */
  void *tret;                                 /* Prey/Predator¥¹¥ì¥Ã¥É½ªÎ»»þ¤ÎÌá¤êÃÍÍÑ */
#endif /* VERSION_1_2 */

  /* °Ê²¼¤Ï¥ª¥×¥·¥ç¥ó»ØÄê¤Ë¤è¤êÊÑ¹¹¤µ¤ì¤ë²ÄÇ½À­¤Î¤¢¤ëÊÑ¿ô */
  int gameStepNum_Max;                        /* ¥²¡¼¥à¤ÎºÇÂç¥¹¥Æ¥Ã¥×¿ô */
  int displayWait;                            /* É½¼¨¹¹¿·´Ö³Ö(¥Þ¥¤¥¯¥íÉÃ) */
  char worldFileName[WORLD_FILE_NAME_LENGTH]; /* ³Ê»ÒÀ¤³¦¥Õ¥¡¥¤¥ëÌ¾ */

  /* ÊÑ¿ô¤Î¥Ç¥Õ¥©¥ë¥ÈÃÍ¤òÀßÄê¤¹¤ë */
  gameStepNum_Max = GAME_NUM;
  displayWait = DISPLAY_WAIT;
  strcpy(worldFileName, "battlefield.dat");

  /* É¸½àÆþÎÏ¤«¤é¤Î¥Ñ¥é¥á¡¼¥¿½èÍý */
  for (i=1; i<argc; i++){
    /* "-s"(¥¹¥Æ¥Ã¥×¿ô»ØÄê)¥ª¥×¥·¥ç¥ó¤Î½èÍý */
    if (strcmp(argv[i], "-s")==0){              /* "-s"¤¬¤¢¤Ã¤¿¤é */
      if (i+1 < argc){                          /* ¤½¤Î¼¡¤ËÆþÎÏ¤¬¤¢¤ë¤«? */
	if (atoi(argv[i+1]) > 0){               /* ÆþÎÏ¤µ¤ì¤¿ÃÍ¤ÏÂÅÅö? */
	  gameStepNum_Max = atoi(argv[i+1]);    /* Á´¤ÆOK¤Î¤È¤­¤Î½èÍý */
	  i++;
	}
	else{
	  printf("Invalid input value!! Specify one positive number.\n");
	  /* ÃÍ¤¬ÂÅÅö¤Ç¤Ê¤¤¾ì¹ç */
	  return(1);
	}
      }
      else{
	/* ¥ª¥×¥·¥ç¥ó¤Î¼¡¤ËÆþÎÏ¤¬¤Ê¤¤¾ì¹ç */
	printf("Option error!! You must specify number of game step.\n");
	return(1);
      }
    }
    /* "-t"(É½¼¨´Ö³Ö»ØÄê)¥ª¥×¥·¥ç¥ó¤Î½èÍý */
    else if(strcmp(argv[i], "-t")==0){         /* "-t"¤¬¤¢¤Ã¤¿¤é */
      if (i+1 < argc){                         /* ¤½¤Î¼¡¤ËÆþÎÏ¤¬¤¢¤ë¤«? */
	if (atoi(argv[i+1]) >= 0){              /* ÆþÎÏ¤µ¤ì¤¿ÃÍ¤ÏÂÅÅö¤«? */
	  displayWait = atoi(argv[i+1]);       /* Á´¤ÆOK¤Î¤È¤­¤Î½èÍý */
	  i++;
	}
	else{
	  printf("Invalid input value!! Specify one positive number.\n");
	  /* ÃÍ¤¬ÂÅÅö¤Ç¤Ê¤¤¾ì¹ç */
	  return(1);
	}
      }
      else{
	/* ¥ª¥×¥·¥ç¥ó¤Î¼¡¤ËÆþÎÏ¤¬¤Ê¤¤¾ì¹ç */
	printf("Option error!! you must specify interval time of redraw.\n");
	return(1);
      }
    }
    /* "-w"(³Ê»ÒÀ¤³¦¥Õ¥¡¥¤¥ëÌ¾»ØÄê)¥ª¥×¥·¥ç¥ó¤Î½èÍý */
    else if(strcmp(argv[i], "-w")==0){          /* "-w"¤¬¤¢¤Ã¤¿¤é */
      if (i+1 < argc){                          /* ¤½¤Î¼¡¤ËÆþÎÏ¤¬¤¢¤ë¤«? */
	/* Á´¤ÆOK¤Î¤È¤­¤Î½èÍý */
	strncpy(worldFileName, argv[i+1], WORLD_FILE_NAME_LENGTH);
	i++;
      }
      else{
	/* ¥ª¥×¥·¥ç¥ó¤Î¼¡¤ËÆþÎÏ¤¬¤Ê¤¤¾ì¹ç */
	printf("Option error!! You must specify world file name.\n");
	return(1);
      }
    }
    else {
      printf("Invalid option: available options are:\n");
      printf("-s: Specify number of game step. ex: \"-s 10\"\n");
      printf("-t: Specify interval  time of redraw. ex: \"-t 100000\"\n");
      printf("-w: Specify world file name. ex: \"-w battlefield2.dat\"\n");
      return(1);
    }
  }

  /* BattleField¤ÎÆÉ¤ß¹þ¤ß */
  if (ReadInitConf(array,worldFileName) == 1){
    fprintf(stderr,"File read failed!!\n");
    return(1);
  }

  /* É½¼¨¤Î¥¯¥ê¥¢ */
  system("clear");

  /* ½é´ü¾õÂÖ¤ÎÉ½¼¨ */
  PrintWorld(array,0);

#ifdef VERSION_1_2
  /* ÊÂÎó¼Â¹Ô¤¹¤ë¥¹¥ì¥Ã¥É¿ô¤ò¥»¥Ã¥È¤¹¤ë */
  pthread_setconcurrency(3);
#endif /* VERSION_1_2 */

  /* ¥²¡¼¥à¥¹¥¿¡¼¥È */
  for (gameStepNum=1; gameStepNum<= gameStepNum_Max; gameStepNum++){

#ifdef VERSION_1_2 /* »þ´Ö´Æ»ë¥Ð¡¼¥¸¥ç¥ó */
    /* Predator¤Î¹ÔÆ° */
    copyWorld(copy_array,array);

    /* Predator thread¤òºî¤ë */
    status = pthread_create(&player_tid, NULL, threadPredator, (void *)copy_array);
    if(status != 0){
      fprintf(stderr,"pthread_create fail!!: %s\n", strerror(status));
      abort();
    }

    /* watch dog timer thread¤òºî¤ë */
    status = pthread_create(&wd_tid, NULL, threadWatchdogTimer, (void *)&player_tid);
    if(status != 0){
      fprintf(stderr,"pthread_create fail!!: %s\n", strerror(status));
      abort();
    }

    /* Predator thread¤Î½ªÎ»¤òÂÔ¤Ä¡¥½ªÎ»Ìá¤êÃÍ¤Ïtret */
    status = pthread_join(player_tid, &tret);
    if(status != 0){
      fprintf(stderr,"pthread_join fail!!: %s\n", strerror(status));
      abort();
    }

    /* Predator thread¤¬¥­¥ã¥ó¥»¥ë¤µ¤ì¤¿¤«³ÎÇ§ */
    if(tret == (void *)PTHREAD_CANCELED){
      predatorAction = 's';
    }
    else{
      predatorAction = *((int *)tret);
    }

    /* watch dog thread¤Î½ªÎ»¤òÂÔ¤Ä¡¥½ªÎ»Ìá¤êÃÍ¤Ïtret */
    status = pthread_join(wd_tid, &tret);
    if(status != 0){
      fprintf(stderr,"pthread_join fail!!: %s\n", strerror(status));
      abort();
    }

    /* Prey¤Î¹ÔÆ°(2²óÆ°¤¤¤Æ1²óµÙ¤à) */
    if (gameStepNum % 3 != 0){ 
      copyWorld(copy_array,array);

      /* Prey thread¤òºî¤ë */
      status = pthread_create(&player_tid, NULL, threadPrey, (void *)copy_array);
      if(status != 0){
	fprintf(stderr,"pthread_create fail!!: %s\n", strerror(status));
	abort();
      }

      /* watch dog timer thread¤òºî¤ë */
      status = pthread_create(&wd_tid, NULL, threadWatchdogTimer, (void *)&player_tid);
      if(status != 0){
	fprintf(stderr,"pthread_create fail!!: %s\n", strerror(status));
	abort();
      }

      /* Prey thread¤Î½ªÎ»¤òÂÔ¤Ä¡¥½ªÎ»Ìá¤êÃÍ¤Ïtret */
      status = pthread_join(player_tid, &tret);
      if(status != 0){
	fprintf(stderr,"pthread_join fail!!: %s\n", strerror(status));
	abort();
      }

      /* Prey thread¤¬¥­¥ã¥ó¥»¥ë¤µ¤ì¤¿¤«³ÎÇ§ */
      if(tret == (void *)PTHREAD_CANCELED){
	preyAction = 's';
      }
      else{
	preyAction = *((int *)tret);
      }

      /* watch dog thread¤Î½ªÎ»¤òÂÔ¤Ä¡¥½ªÎ»Ìá¤êÃÍ¤Ïtret */
      status = pthread_join(wd_tid, &tret);
      if(status != 0){
	fprintf(stderr,"pthread_join fail!!: %s\n", strerror(status));
	abort();
	
      }
    }
    else{
      preyAction = 's';
      usleep(WATCHDOG_COUNT_INIT*WATCHDOG_INTERVAL);
    }
#else /* VERSION_1_2 */
    /* Predator¤Î¹ÔÆ° */
    copyWorld(copy_array,array);
    Predator(copy_array, &predatorAction);

    /* Prey¤Î¹ÔÆ°(2²óÆ°¤¤¤Æ1²óµÙ¤à) */
    if (gameStepNum % 3 != 0){
      copyWorld(copy_array,array);
      Prey(copy_array,&preyAction);      
    }
    else{
      preyAction = 's';
    }
#endif /* VERSION_1_2 */

    /* É½¼¨¤Î¥¦¥§¥¤¥È */
    usleep(displayWait);

    /*
     * ¤½¤ì¤¾¤ì¤Î¹ÔÆ°¤Ë¹ç¤ï¤»¤Æ³Ê»ÒÀ¤³¦¤ò¹¹¿·
     * RenewWorld¤Îµ¢¤êÃÍ¤¬0¤Ê¤é¤Ð·ÑÂ³
     */
    if (RenewWorld(array,predatorAction, preyAction) == 0){
      system("clear");
      PrintWorld(array, gameStepNum);
    }
    /* ¤½¤¦¤Ç¤Ê¤±¤ì¤Ð(1¤Ê¤é¤Ð)½ªÎ» */
    else{
      system("clear");
      PrintWorld(array, gameStepNum);      
      printf("Game Over!! Winner Predator (%d clock)!!\n",gameStepNum);
      return(0);
    }

  } 

  /* Prey¤¬ºÇ¸å¤Þ¤ÇÆ¨¤²ÀÚ¤Ã¤¿¤È¤­¤Î¥á¥Ã¥»¡¼¥¸½ÐÎÏ */
  printf("Game Over!! Winner Prey!!\n");
  return(0);
}


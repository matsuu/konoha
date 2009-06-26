/* Othello.c (c) Kimio Kuramitsu */

#ifndef OTHELLO_H_
#define OTHELLO_H_

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/* オセロのコマの状態 */

#define SPACE 0
#define BLACK 1
#define WHITE 2
#define MISPLACED 3

/* オセロ板の大きさ */
#ifndef SIZE
#define SIZE  8
#endif

/* 型宣言 */
/* x, y --> placexy */

typedef int placexy_t;

int new_placexy(int x, int y);
int place_getx(placexy_t p);
int place_gety(placexy_t p);

/* プレイヤー関数 */

typedef placexy_t (*f_player)(int board[SIZE][SIZE], int color);

/* コンピュータのプロトタイプ宣言　*/

int start_game(f_player p1, f_player p2);
int board_canPlaceAt(int board[SIZE][SIZE], int x, int y, int color);
void board_print(int board[SIZE][SIZE]);

placexy_t player_human(int board[SIZE][SIZE], int color);
placexy_t player_random(int board[SIZE][SIZE], int color);
placexy_t player_eager(int board[SIZE][SIZE], int color);
placexy_t player_smartrandom(int board[SIZE][SIZE], int color);

#endif /*OTHELLO_H_*/

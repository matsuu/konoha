/* オセロゲーム (C版 プログラミング)
 *  Kimio Kuramitsu (C) All Rights Reserved */

#include"othello.h"

/* コマの表示記号 (画面が黒字なのでエディタとは白黒反転する)
   cygwin の場合は、mark2を使えば、カラー表示になる。 */

#ifdef WITH_COLOR
static
char *mark[] ={"□", "●",　"○", "×"};
#else
static
char *mark[] = {". ", "* ", "O ", "X "};
#endif

/* ---- プログラムはここから ---- */

/* オセロ板の初期化 */

void board_init(int board[SIZE][SIZE])
{
	int x, y;
	for(x = 0; x < SIZE; x++) {
		for(y = 0; y < SIZE; y++) {
			board[x][y] = SPACE;
		}
	}
	board[SIZE/2][SIZE/2] = BLACK;
	board[SIZE/2 - 1][SIZE/2 - 1] = BLACK;
	board[SIZE/2][SIZE/2-1] = WHITE;
	board[SIZE/2-1][SIZE/2] = WHITE;
}

/* オセロ板上のコマ数をカウントする */

int board_count(int board[SIZE][SIZE], int color)
{
	int x, y, count = 0;
	for(x = 0; x < SIZE; x++) {
		for(y = 0; y < SIZE; y++) {
			if(board[x][y] == color) count++;
		}
	}
	return count;
}

/* オセロ板を表示する */

void board_print(int board[SIZE][SIZE])
{
	int x, y;
	printf("  ");
	for(x = 0; x < SIZE; x++) printf("%d ", x);
	printf("\n");
	for(y = 0; y < SIZE; y++) {
		printf("%d ", y);
		for(x = 0; x < SIZE; x++) {
			printf("%s", mark[board[x][y]]);
		}
		if(y == 1) printf("    %s: %d", mark[BLACK], board_count(board, BLACK));
		if(y == 3) printf("    %s: %d", mark[WHITE], board_count(board, WHITE));
		if(y == 6) printf("    %s: %d", mark[SPACE], board_count(board, SPACE));
		printf("\n");
	}
	printf("\n");
}

/* ---- ここからちょっと難しい ---- */

static
int board_find_turnable_inline(int board[SIZE][SIZE], int x, int y, int dx, int dy, int color)
{
	int i, c = 0;
	for(i = 0; i < SIZE; i++) {
		x += dx;
		y += dy;
		if(x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
			return 0;
		}
		if(board[x][y] == SPACE) return 0;
		if(board[x][y] == color) return c;
		c++;
	}
	return 0;
}

/* オセロ板上の(x,y)に色colorコマを置いたとき、
   いくつ相手のコマが取れるかカウントする */

int board_countTurnableStone(int board[SIZE][SIZE], int x, int y, int color)
{
  if(board[x][y] != SPACE) return 0;
  return board_find_turnable_inline(board, x, y, -1, -1, color)
	+ board_find_turnable_inline(board, x, y, -1, 0, color)
        + board_find_turnable_inline(board, x, y, -1, 1, color)
	+ board_find_turnable_inline(board, x, y, 1, -1, color)
        + board_find_turnable_inline(board, x, y, 1, 0, color)
	+ board_find_turnable_inline(board, x, y, 1, 1, color)
        + board_find_turnable_inline(board, x, y, 0, -1, color)
	+ board_find_turnable_inline(board, x, y, 0, 1, color);
}

int board_canPlaceAt(int board[SIZE][SIZE], int x, int y, int color)
{
	if(0 <= x && x < SIZE && 0 <= y && y < SIZE) {
		return (board_countTurnableStone(board, x, y, color) > 0);
	}
	return 0;
}

/* オセロ板上に色colorのコマがおけるか調べる */

static
int board_canPlaceAnywhere(int board[SIZE][SIZE], int color)
{
	int x, y;
	for(y = 0; y < SIZE; y++) {
		for(x = 0; x < SIZE; x++) {
			if(board_countTurnableStone(board, x, y, color) > 0) return 1;
		}
	}
	return 0;
}

/* オセロ板上の(x,y)に色colorのコマを置く */

static
void board_turn_inline(int board[SIZE][SIZE], int x, int y, int dx, int dy, int color)
{
	int i;
	for(i = 0; i < SIZE; i++) {
		x += dx;
		y += dy;
		if(board[x][y] == color) return ;
		board[x][y] = color;
	}
}

static
void board_placeAt(int board[SIZE][SIZE], int x, int y, int color)
{
	int dx, dy;
	for(dx = -1; dx < 2; dx++) {
		for(dy = -1; dy < 2; dy++) {
			if(dx == 0 && dy == 0) continue;
			if(board_find_turnable_inline(board, x, y, dx, dy, color) > 0) {
		    	  board_turn_inline(board, x, y, dx, dy, color);
			}
		}
	}
	board[x][y] = color;
}

/* ---- x,y (2D)を1変数に変換する　---- */

int new_placexy(int x, int y)
{
	return x * SIZE + y;
}

int place_getx(placexy_t p)
{
	return p / SIZE;
}

int place_gety(placexy_t p)
{
	return p % SIZE;
}

/* ---- どこにコマをおくか決めるサブプログラム　---- */

/* 人間がコマ(color)を置く場所を決める */

placexy_t
player_human(int board[SIZE][SIZE], int color)
{
	char xbuf[80], ybuf[80];
	int x, y;
	printf("Where %s puts x y ? ", mark[color]);
	scanf("%s %s", xbuf, ybuf);
	x = atoi(xbuf); y = atoi(ybuf);
	if(board_canPlaceAt(board, x, y, color) == 0) {
		printf(" == You cannot place %s at %d %d\n", mark[color], x, y);
		return player_human(board, color);
	}
	return new_placexy(x, y);
}

/* ---- ここからゲームを制御するプログラム　---- */

/* 人間やコンピュータが間違ったところにコマを置いた
   ときの処理を行う */

static
void board_misplaced(int board[SIZE][SIZE], int x, int y, int color)
{
	board[x][y] = 3;
	board_print(board);
	printf("%s loses because he or she put at %s\n\n", mark[color], mark[3]);
}

/* 引数で与えられたプレイヤーに対し、交互に黒と白のコマを
   置かせる。 プレイヤーは、関数のポインタ渡しで呼ばれている */

int start_game(f_player p1, f_player p2)
{
	int board[SIZE][SIZE], space, space_prev = 60;
	board_init(board);
	while(board_count(board, SPACE) > 0) {
		if(board_canPlaceAnywhere(board, BLACK)) {
			placexy_t p;
			board_print(board);
			p = p1(board, BLACK);
			if(board_canPlaceAt(board, place_getx(p), place_gety(p), BLACK)) {
				board_placeAt(board, place_getx(p), place_gety(p), BLACK);
			}
			else {
				board_misplaced(board, place_getx(p), place_gety(p), BLACK);
				return -(SIZE*SIZE);
			}
		}
		if(board_canPlaceAnywhere(board, WHITE)) {
			placexy_t p;
			board_print(board);
			p = p2(board, WHITE);
			if(board_canPlaceAt(board, place_getx(p), place_gety(p), WHITE)) {
				board_placeAt(board, place_getx(p), place_gety(p), WHITE);
			}
			else {
				board_misplaced(board, place_getx(p), place_gety(p), WHITE);
				return (SIZE*SIZE);
			}
		}
		space = board_count(board, SPACE);
		if(space == space_prev) {
			break;  /* どちらかが全滅した */
		}
		else {
			space_prev = space;
		}
	}
	board_print(board);
	{
		int black_win = board_count(board, BLACK) - board_count(board, WHITE);
		if(black_win > 0) {
			printf("%s won by %d.\n\n", mark[BLACK], black_win);
		}
		else if(black_win == 0) {
			printf("The game ended in a draw.\n\n");
		}
		else {
			printf("%s won by %d.\n\n", mark[WHITE], -black_win);
		}
		return black_win;
	}
}


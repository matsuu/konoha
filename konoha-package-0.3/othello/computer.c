/* オセロゲーム (C版 プログラミング)
 *  Kimio Kuramitsu (C) All Rights Reserved */

#include"othello.h"

/* コンピュータがコマ(color)を置く場所を決める */

placexy_t
player_random(int board[SIZE][SIZE], int color)
{
	srand((unsigned)time(NULL));
	while(1) {
		int x = rand() % SIZE;
		int y = rand() % SIZE;
		if(board_canPlaceAt(board, x, y, color)) {
			return new_placexy(x, y);
		}
	}
}

/* random より、ちょっと賢い 隅を優先的におく */

placexy_t
player_smartrandom(int board[SIZE][SIZE], int color)
{
	int i;
	if(board_canPlaceAt(board, 0, 0, color)) return new_placexy(0, 0);
	if(board_canPlaceAt(board, SIZE-1, 0, color)) return new_placexy(SIZE-1, 0);
	if(board_canPlaceAt(board, 0, SIZE-1, color)) return new_placexy(0, SIZE-1);
	if(board_canPlaceAt(board, SIZE-1, SIZE-1, color)) return new_placexy(SIZE-1, SIZE-1);

	for(i = 1; i < SIZE-1; i++) {
		if(board_canPlaceAt(board, 0, i, color)) return new_placexy(0, i);
		if(board_canPlaceAt(board, SIZE-1, i, color)) return new_placexy(SIZE-1, i);
		if(board_canPlaceAt(board, i, SIZE-1, color)) return new_placexy(i, SIZE-1);
		if(board_canPlaceAt(board, i, 0, color)) return new_placexy(i, 0);
	}
	return player_random(board, color);
}

int board_countTurnableStone(int board[SIZE][SIZE], int x, int y, int color) ;

placexy_t
player_eager(int board[SIZE][SIZE], int color)
{
	int x, y, max = 0, px = 0, py = 0;
	for(x = 0; x < SIZE; x++) {
		for(y = 0; y < SIZE; y++) {
			int c = board_countTurnableStone(board, x, y, color);
			if(c > max) {
				max = c;
				px = x;
				py = y;
			}
		}
	}
	return new_placexy(px, py);
}

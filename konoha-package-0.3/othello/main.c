/* オセロゲーム (C版 プログラミング) 
 *  Kimio Kuramitsu (C) All Rights Reserved */

#include"othello.h"

/* 人間対コンピュータのゲームを実行する */

int 
main(void) 
{
	//start_game(player_human, player_eager);
	start_game(player_eager, player_random);
	return 0;
}

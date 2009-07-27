#!/usr/local/bin/konoha
/*************************
* Othello Game
* Shinpei Nakata (c) 2008
**************************/

SIZE = 8;
BLACK = 0;
WHITE = 1;
SPACE = 2;


class Coord {
	int x;
	int y;
	
	Coord(int a, int b) {
		x = a;
		y = b;
	}
	
}

class Square {
	int color;
	
	Square() {
		color = SPACE;
	}
	
	String getMarkSquare() {
		if (color == BLACK) return "*";
		if (color == WHITE) return "O";
		return "+";
	}
	
	void putBLACK () {
		color = BLACK;
	}
	
	void putWHITE() {
		color = WHITE;
	}
	
	void putSPACE() {
		color = SPACE;
	}
	
	Boolean isWHITE() {
		if(color == WHITE) return true;
		return false;
	}
	
	Boolean isBLACK() {
		if(color == BLACK) return true;
		return false;
	}
	
	Boolean isSPACE() {
		if(color == SPACE) {
			return true;
		}
		return false;
	}
	
}

class Player {
	String name;
	int color;

	Player(String name, int c) {
		name = name;
		color = c;
	}

	Coord think() {
		int x = Int.random(SIZE);
		int y = Int.random(SIZE);
		Coord ret = new Coord(x,y);
		return ret;
	}
}

class OthelloBoard {
	Square[] board;
	
	OthelloBoard() {
		board = new Square[]();

		int i;
		for (i = 0;i < SIZE * SIZE; i++) {
			board.add(new Square());
		}

	}
	
	void turnInlineTurnable(Coord a, int dx, int dy, int col) {
		int p;
		int x, y;
		x = a.x;
		y = a.y;
		int i;

		for (i = 0; i < SIZE; i++) {
			x = x + dx;
			y = y + dy;
			p = calcIndex(x,y);
			if (p < SIZE * SIZE) {
			 if (col == BLACK) {
			 	print 'hi'
			 	board[p].putBLACK();
			 }
			 if (col == WHITE) {
			 	board[p].putWHITE();
			 }
			}
		}
	}
	
	void placeDisc(int x, int y, int col) {
		int index;
		index = calcIndex(x,y);
		if (col == BLACK) board[index].putBLACK();
		else board[index].putWHITE();
	}
	
	void putDisc (Coord a, int col) {
		int v,w;
		for(v = -1; v < 2 ; v++) {
			for (w = -1; w < 2 ; w++) {
				if (countInlineTurnable(a,v,w,col) > 0) {
					turnInlineTurnable(a,v,w,col);
				}
			}
		}
		int p;
		int x, y;
		x = a.x;
		y = a.y;
		p = calcIndex(x,y);
		if (col == BLACK) {board[p].putBLACK();}
		else {board[p].putWHITE();}
	}
	
	int calcIndex (int x, int y) {
		return y * SIZE + x;
	}
	
	void draw() {
		int i
		for (i = 1 ; i <= SIZE ; i++) OUT << i << " ";
		OUT << EOL;
		for(i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				OUT << board[calcIndex(j,i)].getMarkSquare() << " ";
			}
			OUT << i+1;
			OUT << EOL;
		}
		OUT << EOL;
	}
	
	int countInlineTurnable(Coord a, int dx, int dy,int color) {
		int c, p, x, y, i;
		Square s;
		x = a.x;
		y = a.y;
		c = 0;
		for (i = 0 ; i < SIZE ; i++) {
			x = x + dx;
			y = y + dy;	
			if (x < 0) {return 0}
			if (x >= SIZE) {return 0}
			if (y < 0) {return 0;}
			if (y >= SIZE) {return 0;}
			p = calcIndex(x,y);
			s = _board[p];
			if (s.isSPACE()) {return 0;}
			if (color == WHITE) { 
				if (s.isWHITE()) { return c;}
			} else {
				if (s.isBLACK()) { return c;}
			}
			c++;
		}
		return 0;
	}
	
	int countTurnable(Coord a, int color) {
		int res;
		res = countInlineTurnable(a,-1,-1,color);
		res = res + countInlineTurnable(a,-1,0,color);
		res = res + countInlineTurnable(a,-1,1,color);
		res = res + countInlineTurnable(a,1,-1,color);
		res = res + countInlineTurnable(a,1,0,color);
		res = res + countInlineTurnable(a,1,1,color);
		res = res + countInlineTurnable(a,0,-1,color);
		res = res + countInlineTurnable(a,0,1,color);
		return res;
	}
	
	Boolean isPlacable(Coord a, int color) {
		int res = countTurnable(a,color);
		if (res > 0) return true;
		return false;
	}
	
	int countColor(int color) {
		int count;
		int i, j;
		for(i = 0;i < SIZE; i++) {
			for (j = 0; j< SIZE; j++) {
				if (board[calcIndex(i,j)].color == color) count++;
			}
		}
		print count
		return count;
	}
		
	Boolean canPlaceAnywhere(int color) {
		Coord c;
		int i, j;
		for(i = 0 ; i < SIZE ; i++) {
			for(j = 0 ; j < SIZE ; j++ ) {
				c = new Coord(i,j);
				if(isPlacable(c, color)) {return true;}
			}
		}
		return false;	
	}
}



class GameMaster {
	OthelloBoard b;
	
	GameMaster() {
		b = new OthelloBoard();
		b.placeDisc(3,4,BLACK);
		b.placeDisc(4,3,BLACK);
		b.placeDisc(3,3,WHITE);
		b.placeDisc(4,4,WHITE);
	}
	
	void draw() {
		b.draw();
	}
	
	void start(Player p1, Player p2) {
		Coord a;
		int black, white;
		int counter = 0;
		while (b.countColor(SPACE) != 0) {
			a = p1.think();
			while (!b.isPlacable(a, p1.color)) {
				a = p1.think();
			}
			draw();
			b.putDisc(a, p1.color);
			print 'hihihihi'
			draw();
			if (b.canPlaceAnywhere(BLACK) == true) {
				a = p2.think();
				//while (!b.isPlacable(a, p2.color)) {
				//	a = p2.think();
				//}
				
				b.putDisc(a, p2.color);
				draw();
				if (b.canPlaceAnywhere(WHITE) == true) {
					counter++;
				}
			}
		}
		black = b.countColor(BLACK);
		white = b.countColor(WHITE);
		OUT << "black:" << black << " white:" << white << EOL;		
		
	}
}

GameMaster gm = new GameMaster();
Player shinpei = new Player("shinpei", BLACK);
Player taro = new Player("taro", WHITE);

//gm.start(shinpei, taro);


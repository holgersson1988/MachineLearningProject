#pragma once

#define PLAY2	15
#define PLAY1	254

void display();

/*
Checks to see if move at location (a,b) created a win.
*/
bool check(int a, int b);

/*
Puts 'player' piece in column b if valid move. Returns -1 if error,
positive integer otherwise.
*/
int drop(int b, char player);

/*
Returns depth of chosen move 'b'. Returns -1 if move invalid.
*/
int getMoveDepth(int b, char player);

extern char place[6][7];
#ifndef controller
#define controller
#include "drawScreen.h"
#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "drawScreen.h"
#include <time.h>
#include <string.h>

extern int remainingMarkers;
extern int stopTraversal;
char map[HEIGHT/spacing + 1][WIDTH/spacing + 1];
int visited[HEIGHT/spacing + 1][WIDTH/spacing + 1];
char map[HEIGHT / spacing + 1][WIDTH / spacing + 1];
extern int dirs2[4][2];
extern int dirs[4][2];

extern void atMarker();
extern void moveForward();
extern void canMoveForward(int, int);
extern void shuffleDirections();
extern void dfs(int , int);
extern void dfsTraverse(int, int);
extern void placeMarkers(int);
#endif

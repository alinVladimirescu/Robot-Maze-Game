#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "drawScreen.h"
#include <time.h>
#include <string.h>

int remainingMarkers = 0;
int stopTraversal = 0;
char map[HEIGHT/spacing + 1][WIDTH/spacing + 1];
int visited[HEIGHT/spacing + 1][WIDTH/spacing + 1];

int dirs2[4][2] = {
    {-1, 0},  // UP (ny = y - 1)
    {0, -1},  // LEFT (nx = x - 1)
    {1, 0},   // DOWN (ny = y + 1)
    {0, 1}    // RIGHT (nx = x + 1)
};
int dirs[4][2] = {
    {-1, 0},  // UP (ny = y - 1)
    {0, -1},  // LEFT (nx = x - 1)
    {1, 0},   // DOWN (ny = y + 1)
    {0, 1}    // RIGHT (nx = x + 1)
};
void left()
{
    direction = (direction + 1) % 4;
    switch(direction){
        case UP: faceUp(pos.centerX, pos.centerY);break;
        case LEFT: faceLeft(pos.centerX, pos.centerY);break;
        case DOWN: faceDown(pos.centerX, pos.centerY); break;
        case RIGHT: faceRight(pos.centerX, pos.centerY); break;
    }
}
void right()
{
    direction = (direction + 3) % 4;
    switch(direction){
        case UP: faceUp(pos.centerX, pos.centerY);break;
        case LEFT: faceLeft(pos.centerX, pos.centerY);break;
        case DOWN: faceDown(pos.centerX, pos.centerY); break;
        case RIGHT: faceRight(pos.centerX, pos.centerY); break;
    }
}
int atMarker()
{
if (map[(pos.centerY - spacing / 2) / spacing][(pos.centerX - spacing / 2) / spacing] == 'M') 
    return 1;
return 0;

}

void forward() 
{
    if(direction == UP)
    {
        for(int i = 0; i < spacing; i += moveDistance)
        {
            pos.centerY = pos.centerY - moveDistance;  
            
            update();
            sleep(15); 
        }
    }
    else if (direction == DOWN)
    {
        for(int i = 0; i < spacing; i += moveDistance)
        {
            pos.centerY = pos.centerY + moveDistance;
            
            update();
            sleep(15);
        }
    }
    else if (direction == LEFT)
    {
        for(int i = 0; i < spacing; i += moveDistance)
        {
            pos.centerX = pos.centerX - moveDistance;
            
            update();
            sleep(15);
        }
    }
    else if (direction == RIGHT)
    {
        for(int i = 0; i < spacing; i += moveDistance)
        {
            pos.centerX = pos.centerX + moveDistance;
           
            update();
            sleep(15);
        }
    }
    if(atMarker()){
        clearMarker(pos.centerX - spacing / 2, pos.centerY - spacing / 2);
        map[(pos.centerY - spacing / 2) / spacing][(pos.centerX - spacing/2) / spacing] = '_';
    remainingMarkers--;
    message("Marker collected!");
    fflush(stdout);
    fflush(stdout);
    if (remainingMarkers <= 0) {
        stopTraversal = 1;
    }            
}
    fflush(stdout);
}

int canMoveForward(int y, int x)
{
   
    // bounds safety
    if (x < 0 || y < 0 || x >= WIDTH / spacing || y >= HEIGHT / spacing) return 0;
    //check availability of next cell
    switch (direction) {
        case UP:
            if (y - 1 < 0) return 0;
            return map[y - 1][x] != '#';
        case DOWN:
            if (y + 1 >= HEIGHT / spacing) return 0;
            return map[y + 1][x] != '#';
        case LEFT:
            if (x - 1 < 0) return 0;
            return map[y][x - 1] != '#';
        case RIGHT:
            if (x + 1 >= WIDTH / spacing) return 0;
            return map[y][x + 1] != '#';
    }
    return 0;
}

void shuffleDirections() {
    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        int tempX = dirs2[i][0];
        int tempY = dirs2[i][1];
        dirs2[i][0] = dirs2[j][0];
        dirs2[i][1] = dirs2[j][1];
        dirs2[j][0] = tempX;
        dirs2[j][1] = tempY;
    }
}

void dfs(int y, int x)
{
    map[y][x] = '_';
    shuffleDirections();

    for(int i = 0; i < 4; i++)
    {
    int ny = y + dirs2[i][0] * 2;
    int nx = x + dirs2[i][1] * 2;
        if(nx > 0 && nx < (WIDTH/spacing)-1 && ny > 0 && ny < (HEIGHT/spacing)-1 && map[ny][nx] == '#')
        {
            map[y + dirs2[i][0]][x + dirs2[i][1]] = '_';
            dfs(ny, nx);
        }
    }
}




void dfsTraverse(int y, int x)
{
    if(stopTraversal) return;

    visited[y][x] = 1;

    for (int i = 0; i < 4 && !stopTraversal; ++i) {
        int ny = y + dirs[i][0];
        int nx = x + dirs[i][1];

        

        // skip already visited or wall cells
        if (visited[ny][nx] == 0 && map[ny][nx] != '#')
       {
        // face the direction we intend to move 
        int turn = (i - direction + 4) % 4;
        if(turn == 1)
        {
            left();
        }else if(turn == 2)
        {
            right();
            right();
        }else if(turn == 3)
        {
            right();
        }

        if (canMoveForward(y, x)) {
        
        //move physically to the neighbour 
        forward();

          if (stopTraversal) return;
        // recurse into the neighbour cell
        dfsTraverse(ny, nx);

        if (stopTraversal) return;
        direction = (i + 2) % 4;
        right();
        right();
       
    if (stopTraversal) return;  
        // face the original direction
        direction = i;
        right();
        right();
         forward();
        }
        }
    }
}

    

void placeMarkers(int count)
{
    for (int i = 0; i < count / 2; i++)
    {
        int x, y;
        do {
            x = rand() % (WIDTH / spacing);
            y = rand() % (HEIGHT / spacing);
        } while (map[y][x] != '_');  // must be open path

        map[y][x] = 'M';
        drawMarker(x * spacing, y * spacing);
    }
    remainingMarkers = count / 2;

     //find all dead-end spots on grid

        int deadEndCount = 0;
        int deadEnds[WIDTH * HEIGHT + 1][2];

        for(int t  = 1; t <=HEIGHT / spacing; t ++){
            for(int j = 1 ; j < WIDTH / spacing; j ++){
                if(map[t][j] == '_' && j != (pos.centerX - spacing / 2) / spacing && t != (pos.centerY - spacing/2 )/ spacing){
                    int path = 0;
                    for(int k = 0; k < 4 && path < 2; k++)
                        if(map[t + dirs[k][1]][j + dirs[k][0]] == '_' || map[t + dirs[k][1]][j + dirs[k][0]] == 'M')
                            path++;
                    if(path == 1)
                    {
                    deadEnds[deadEndCount][0] = j;
                    deadEnds[deadEndCount][1] = t;
                    deadEndCount++;
                    }
                }
            }
        }
        if(deadEndCount >= count / 2)
            remainingMarkers += count / 2;
        else remainingMarkers += deadEndCount;
        
        for(int i = 0; i < count / 2 && deadEndCount > 0; i ++)
        {
            int x, y, random;
            do{
                random = rand() % deadEndCount;
                x = deadEnds[random][0];
                y = deadEnds[random][1];
            }while(x == (pos.centerX -spacing/2) / spacing && y ==  (pos.centerY - spacing / 2)/ spacing);
            map[y][x] = 'M';
           drawMarker(x * spacing, y * spacing);
            deadEnds[random][0] = deadEnds[deadEndCount - 1][0];
            deadEnds[random][1] = deadEnds[deadEndCount - 1][1];
            deadEndCount--;
        }
}

#include <stdio.h>
#include "graphics.h"

#define WIDTH  1260
#define HEIGHT  660
#define spacing  60
const double SQRT_3 = 1.732;  
const double ONE_HALF = 0.5;
#define side 30
#define moveDistance 5

enum Dir{
    UP, LEFT, DOWN, RIGHT
};
enum Dir direction = UP;

int triangleRadius  = (int) side / SQRT_3;
int heightAboveCenter  = (int) (side / SQRT_3);
int heightBelowCenter  = (int) ((side * SQRT_3) / 6);


struct robot{
    int xCoords[3], yCoords[3];
    int centerX, centerY;
}pos;

void drawRobot()
{

    setColour(black);
    drawPolygon(3, pos.xCoords, pos.yCoords);
    fillPolygon(3, pos.xCoords, pos.yCoords);
    setColour(red);
    setLineWidth(5);
    drawLine(pos.xCoords[2], pos.yCoords[2], pos.xCoords[1], pos.yCoords[1]);
}


void faceUp(int centerX, int centerY)
{
    pos.xCoords[0] = centerX;
    pos.yCoords[0] = centerY - heightAboveCenter;
    pos.xCoords[1] = centerX - triangleRadius;
    pos.yCoords[1] = centerY + heightBelowCenter;
    pos.xCoords[2] = centerX + triangleRadius;
    pos.yCoords[2] = centerY + heightBelowCenter;
    drawRobot();
}

void faceDown(int centerX, int centerY)
{
    pos.xCoords[0] = centerX;
    pos.yCoords[0] = centerY + heightAboveCenter;
    pos.xCoords[1] = centerX + triangleRadius;
    pos.yCoords[1] = centerY - heightBelowCenter;
    pos.xCoords[2] = centerX - triangleRadius;
    pos.yCoords[2] = centerY - heightBelowCenter;
    drawRobot();
}

void faceRight(int centerX, int centerY)
{
    // Triangle is flipped to the right so the heightAboveCenter and heightBelowCenter now correspond to the x coordinates of the term's axis
    pos.xCoords[0] = centerX + heightAboveCenter;
    pos.yCoords[0] = centerY;
    pos.xCoords[1] = centerX - heightBelowCenter;
    pos.yCoords[1] = centerY - triangleRadius;
    pos.xCoords[2] = centerX - heightBelowCenter;
    pos.yCoords[2] = centerY + triangleRadius;
    drawRobot();
}

void faceLeft(int centerX, int centerY)
{
    // Triangle is flipped to the left so the heightAboveCenter and heightBelowCenter now correspond to the x coordinates of the term's axis
    pos.xCoords[0] = centerX - heightAboveCenter;
    pos.yCoords[0] = centerY;
    pos.xCoords[1] = centerX + heightBelowCenter;
    pos.yCoords[1] = centerY + triangleRadius;
    pos.xCoords[2] = centerX + heightBelowCenter;
    pos.yCoords[2] = centerY - triangleRadius;
    drawRobot();
}

void drawCurrentRobot()
{
    switch(direction)
    {
        case UP:
            faceUp(pos.centerX, pos.centerY);
            break;
        case DOWN:
            faceDown(pos.centerX, pos.centerY);
            break;
        case LEFT:
            faceLeft(pos.centerX, pos.centerY);
            break;
        case RIGHT:
            faceRight(pos.centerX, pos.centerY);
            break;
    }
}

void update()
{
    foreground();
    clear();
    drawCurrentRobot();
}
    
void drawObstacle(int x, int y)
{
    
    
    int offset = 5;
    setColour(black);
    fillRect(x + offset, y + offset, 50, 50);
    fflush(stdout);
}

void drawMarker(int x, int y)
{
    background();
    int offset = 20;
    setColour(gray);
    fillRect(x + offset, y + offset, 20, 20);
    fflush(stdout);
    foreground();
}
void clearMarker(int x, int y)
{
    background();
    int offset = 20;
    setColour(white);
    fillRect(x+ offset, y + offset, 20, 20);
    fflush(stdout);
    foreground();
}
void drawGrid()
{
    background();
    setColour(blue);
    setLineWidth(3);
    
    for (int i = spacing  ; i < WIDTH - spacing  ; i += spacing)
    {
        drawLine(i, spacing, i, HEIGHT - spacing );
    }

 
    for (int i = spacing ; i < HEIGHT - spacing ; i += spacing)
    {
        drawLine(spacing, i, WIDTH - spacing , i);
    }
    drawLine(WIDTH - spacing, HEIGHT - spacing, WIDTH - spacing, spacing);
    drawLine(spacing, HEIGHT - spacing, WIDTH - spacing, HEIGHT - spacing);

}




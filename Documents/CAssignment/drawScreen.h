#ifndef drawScreen
#define drawScreen
#define WIDTH 1260
#define HEIGHT 660
#define spacing 60
#define moveDistance 5
#define side 30
#define moveDistance 5
struct robotPos {
    int xCoords[3];
    int yCoords[3];
    int centerX;    
    int centerY;    
};
enum Dir{
    UP, LEFT, DOWN, RIGHT
};
extern enum Dir direction;
extern struct robotPos pos;
extern int heightAboveCenter, heightBelowCenter, triangleRadius;

extern void drawGrid(void);
extern void drawRobot(void);
extern void drawHit(void);
extern void update(void);
extern void faceUp(int, int);
extern void faceLeft(int, int);
extern void faceDown(int, int);
extern void faceRight(int, int);
extern void drawCurrentRobot();
extern void drawObstacle(int, int);
extern void drawMarker(int, int);
extern void clearMarker(int, int);
#endif
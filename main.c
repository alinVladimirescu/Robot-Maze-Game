#include "drawScreen.h"
#include "controller.h"

int main(int argc, char ** argv)
{

    int initialX = 0;
    int initialY = 0;
    char *initialDirection = "north";

    if(argc == 4)
    {
    initialX = atoi(argv[1]); 
    initialY = atoi(argv[2]); 
    initialDirection = argv[3];
    }
    else if(argc == 3)
    {
        initialX = atoi(argv[1]);
        initialY = atoi(argv[2]);
    }
    else {
        // in case number of arguments is not right, start from (1, 1)
        initialX = 1;
        initialY = 1;
    }
    if (initialX > 19 || initialX < 1 || initialY < 1 || initialY > 9)
    {
        // ensure robot does not start off screen
        printf("Input a valid position for robot to start");
        return 0;
    }
    srand(time(NULL)); 

    for(int i = 0; i <= HEIGHT/spacing; i ++)
        for(int j = 0; j <= WIDTH/spacing; j++)
           map[i][j] = '#';

    // set start position as S so no marker is placed there
    map[initialY][initialX] = 'S';
    
    setWindowSize(WIDTH, HEIGHT);
    drawGrid();
    dfs(initialY, initialX);
   
    pos.centerX = initialX * spacing + spacing / 2;
    pos.centerY = initialY * spacing + spacing/2;

    for(int i = 0; i <= HEIGHT/ spacing; i++)
    {
       for(int j = 0; j <= WIDTH/spacing; j++)
       {
           if(map[i][j] == '#')
               drawObstacle(j * spacing, i * spacing);
        }
    }
    foreground();

    for(int i = 0; i <= HEIGHT/ spacing; i++)
    {
        for(int j = 0; j <= WIDTH/spacing; j++)
        {
            if(map[i][j] == '#')
                drawObstacle(j * spacing, i * spacing);
        }
    }
    pos.centerX = initialX * spacing + spacing / 2;
    pos.centerY = initialY * spacing + spacing/2;
    placeMarkers(8);
    if(strcmp(initialDirection , "south") == 0)
    {
        direction = DOWN;
        faceDown(pos.centerX, pos.centerY);
    }else if(strcmp(initialDirection , "north") == 0)
    {
        direction = UP;
        faceUp(pos.centerX, pos.centerY);

    }
    else if(strcmp(initialDirection, "east") == 0)
    {
        direction = RIGHT;
        faceRight(pos.centerX, pos.centerY);
    }
    else if(strcmp(initialDirection, "west") == 0)
    {
        direction = LEFT;
        faceLeft(pos.centerX, pos.centerY);
    }   
        fflush(stdout);
        dfsTraverse(initialY, initialX);
        
        // win screen after dfs ends
        clear();
        background();
        clear();
        foreground();
        setColour(blue);
        setStringTextSize(50);
        displayImage("./win.png", 0, 0);
        drawString("CONGRATS, ALL MARKERS FOUND!", 250, 500);
        sleep(200000);
        
        return 0;
}
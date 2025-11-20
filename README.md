================================================================================
                            ROBOT MAZE GAME
================================================================================

================================================================================
OVERVIEW
================================================================================

A C-based program that generates a random, unique maze and places markers all throughout it. A triangle robot autonomously navigates all cells of the maze using DFS, collecting all markers until completion.

================================================================================
FEATURES
================================================================================

* Random Maze Generation: Uses recursive DFS to create unique mazes every run
* Recursive Robot Navigation: Robot uses DFS traversal with relative turning (left/right only)
* Strategic Marker Placement: Half of the markers are spawned in open paths and the other half in dead ends, ensuring    the robot has to traverse a significant part of the maze.
* Visual Component: Real-time animation of robot movement and marker collection
* Customizable Start: Specify robot's initial position and direction using command-line arguments
* Win Screen: Displays congratulatory message after collecting all markers

================================================================================
TECHNICAL DETAILS
================================================================================

Robot Movement
--------------
* Direction System: Enum-based (UP, LEFT, DOWN, RIGHT)
* Turning: Only uses left() and right() functions for relative rotation
* Movement: Smooth animation in 5-pixel increments across 60-pixel grid spacing

Maze Generation
---------------
* Algorithm: Randomized DFS with wall carving
* Grid Size: 21x11 cells (1260x660 pixels)
* Cell Spacing: 60 pixels

Marker Placement
----------------
* Total Markers: 8 (4 random + up to 4 in dead-ends)
* Avoidance: Never spawns at robot's starting position
* Strategy: Prioritizes dead-ends to increase difficulty

================================================================================
REQUIREMENTS
================================================================================

* GCC compiler
* Java Runtime Environment (for graphics rendering)
* drawapp-4.5.jar (graphics display application)
* win.png (victory screen image)

================================================================================
COMPILATION & EXECUTION
================================================================================

Compile
-------
gcc graphics.c main.c drawScreen.c controller.c -o main

Run
---
./main | java -jar drawapp-4.5.jar

Command-Line Arguments
----------------------

Default (no arguments):
    ./main | java -jar drawapp-4.5.jar
    - Starts at position (1, 1) facing north

With position:
    ./main <x> <y> | java -jar drawapp-4.5.jar
    - Example: ./main 5 3 | java -jar drawapp-4.5.jar

With position and direction:
    ./main <x> <y> <direction> | java -jar drawapp-4.5.jar
    - Example: ./main 10 5 east | java -jar drawapp-4.5.jar
    - Directions: north, south, east, west
    - Valid x: 1-19, Valid y: 1-9
* Program checks if data entered is valid and acts accordingly
================================================================================
FILE STRUCTURE
================================================================================

Robot-Maze-Game/
├── main.c              # Robot initialization, game loop and victory screen
├── controller.c        # Robot movement functions, random maze generation
├── controller.h        # Controller function declarations
├── drawScreen.c        # Graphics and drawing functions
├── drawScreen.h        # Graphics function declarations
├── graphics.c          
├── graphics.h          
├── drawapp-4.5.jar     
└── win.png             # Victory image

================================================================================
HOW IT WORKS
================================================================================

1. Initialization
   - Parses command-line arguments for initial direction and position in maze
   - Initializes all map cells as walls(#), before "carving" open paths by calling dfs
   - Marks starting position as S, to ensure marker can't be placed there

2. Maze Generation
   - Uses recursive DFS with randomized direction shuffling to make maze unique each run
   - Carves paths through the grid creating a perfect maze

3. Marker Placement
   - Places 4 random markers in open paths
   - Identifies dead-ends (cells with only one exit)
   - Places up to 4 additional markers in dead-ends

4. Robot Navigation
   - Starts at specified position and direction
   - Uses DFS traversal to explore all reachable cells
   - Turns using only left() and right() functions
   - Collects markers on contact
   - Backtracks when necessary

5. Victory
   - Game ends when all markers collected
   - Displays victory screen with congratulatory message

================================================================================
KEY ALGORITHMS
================================================================================

DFS Maze Generation
-------------------
void dfs(int y, int x)
- Recursively carves paths by visiting unvisited neighbors
- Shuffles directions for randomization

DFS Traversal
-------------
void dfsTraverse(int y, int x)
- Explores maze using depth-first search
- Calculates relative turns needed each function call: (target - current + 4) % 4
- Backtracks by turning 180° and returning to initial cell

Marker Detection
----------------
- Checks robot's grid position against 'M' character
- Automatically clears marker visually and decrements counter

================================================================================
TURNING LOGIC
================================================================================

The robot uses only two functions for navigation:

left()  - Turns counterclockwise (UP -> LEFT -> DOWN -> RIGHT)
right() - Turns clockwise (UP -> RIGHT -> DOWN -> LEFT)

Turn calculation:
    int turn = (targetDirection - currentDirection + 4) % 4;
    if (turn == 1) left();
    else if (turn == 2) { right(); right(); }  // 180 degrees
    else if (turn == 3) right();
* This calculation is being done taking into account the declaration of direction Enum: up, left, down, right

================================================================================
KNOWN LIMITATIONS
================================================================================

* Robot may revisit cells, which is needed to traverse the whole maze 
* No manual control - fully autonomous
* Fixed maze size (21x11 cells)
* Requires external graphics application

================================================================================
CODE ORGANIZATION
================================================================================

controller.c/h
--------------
- Robot movement functions (left, right, forward)
- DFS maze generation algorithm
- DFS maze traversal algorithm
- Marker placement logic

drawScreen.c/h
--------------
- Robot animations and rendering 
- Directional facing animation (faceUp, faceDown, faceLeft, faceRight)
- Grid drawing
- Obstacle rendering
- Marker drawing and clearing
- Screen update logic

main.c
------
- Command-line argument parsing
- Game initialization
- Maze generation
- Victory screen display
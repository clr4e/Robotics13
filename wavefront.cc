/*
 * NAME:        Chelsea Rath
 * INSTRUCTOR:  Dr. Cen LI
 * PROJECT:     Project 3 
 * DUE:         Thursday, 4/16/2013
 * DESSCRIPTON: Given a start x and y, and a goal x and y,
 *              creates a wavefront map and calculates the
 *              shortest path from start to goal.
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <queue>
#include <stack>
#include <iomanip>
using namespace std;

#define DEBUG 0
#define HEIGHT 8
#define WIDTH 16

typedef struct {
    int x;
    int y;
    int value;
} point;

void readData(std::string, int [][HEIGHT]);
void waveFront(int [][HEIGHT], point&, point&);
void findPath(int [][HEIGHT], point, point);

int main(int argc, char* argv[]) {
    int world[WIDTH][HEIGHT];
    point start,
          goal;
    
    std::string filename = argv[1];

    if (argc == 2) {            // only filename
        cout << "Please enter a start coordinate: ";
        cin >> start.x >> start.y;
        cout << "Please enter a goal coordinate: ";
        cin >> goal.x >> goal.y;
    }
    if (argc == 4) {            // filename and start
        start.x = atoi(argv[2]);
        start.y = atoi(argv[3]);
        cout << "Please enter a goal coordinate: ";
        cin >> goal.x >> goal.y;
    }
    if (argc == 6) {            // filename, start and goal
        start.x = atoi(argv[2]);
        start.y = atoi(argv[3]);
        goal.x = atoi(argv[4]);
        goal.y = atoi(argv[5]);
    }
    start.value = 2;            // start value == 2
    goal.value = -1;            // goal value == -1
    readData(filename,world);
    waveFront(world,start,goal);
    findPath(world,start,goal);

    return 0;
}

/*
 * FUNCTION:    readData
 * PARAMETERS:  filename, int 2D array to store world
 * RETURN:      null
 * PURPOSE:     to read in the values from file and store
 */
void readData(std::string filename, int world[][HEIGHT]) {
    ifstream inData;
    inData.open(filename.c_str());

    if (DEBUG == 1) cout << "Original world:\n";
    for (int c = 0; c < HEIGHT; c++) {
        for (int r = 0; r < WIDTH; r++) {
            inData >> world[r][c];
            if (DEBUG == 1) cout << setw(2) << world[r][c] << " ";
        }
        if (DEBUG == 1) cout << endl;
    }

    inData.close();
}

/*
 * FUNCTION:    waveFront
 * PARAMETERS:  int 2D array to store world, start and goal points
 * RETURN:      null
 * PURPOSE:     to generate the wavefront map and check start and 
 *              goal locations are valid.
 */
void waveFront(int w[][HEIGHT], point& s, point& g) {
    while (w[s.x][s.y] == 1 ||
           s.x > WIDTH-1 || s.y > HEIGHT-1) {
        cout << "Invalid start location, try again.\n";
        cin >> s.x >> s.y;
    }
    w[s.x][s.y] = s.value;
    while (w[g.x][g.y] == 1 ||
           g.x > WIDTH-1 || g.y > HEIGHT-1 ||
           (g.x == s.x && g.y == s.y)) {
        cout << "Invalid goal location, try again.\n";
        cin >> g.x >> g.y;
    }
    w[g.x][g.y] = g.value;

    point temp;
    queue<point> working;
    working.push(s);        // queue starts off with start location only
    while (working.size() > 0) {
        point cur = working.front();
        working.pop();
        
        // check NORTH
        if (cur.y > 0) {
            if (w[cur.x][cur.y-1] == 0) {
                w[cur.x][cur.y-1] = cur.value + 1;
                temp.x = cur.x; temp.y = cur.y-1;
                temp.value = cur.value + 1;
                working.push(temp);
            }
        }
        // check EAST
        if (cur.x < WIDTH-1) {
            if (w[cur.x+1][cur.y] == 0) {
                w[cur.x+1][cur.y] = cur.value + 1;
                temp.x = cur.x+1; temp.y = cur.y;
                temp.value = cur.value + 1;
                working.push(temp);
            }
        }
        // check SOUTH
        if (cur.y < HEIGHT-1) {
            if (w[cur.x][cur.y+1] == 0) {
                w[cur.x][cur.y+1] = cur.value + 1;
                temp.x = cur.x; temp.y = cur.y+1;
                temp.value = cur.value + 1;
                working.push(temp);
            }
        }
        // check WEST
        if (cur.x > 0) {
            if (w[cur.x-1][cur.y] == 0) {
                w[cur.x-1][cur.y] = cur.value + 1;
                temp.x = cur.x-1; temp.y = cur.y;
                temp.value = cur.value + 1;
                working.push(temp);
            }
        }
    }


    if (DEBUG == 1) {
        cout << "After adding values:\n";
        for (int c = 0; c < HEIGHT; c++) {
            for (int r = 0; r < WIDTH; r++) {
                cout << setw(2) << w[r][c] << " ";
            }
            cout << endl;
        }
    }
}

/*
 * FUNCTION:    findPath
 * PARAMETERS:  int 2D array to store world, start and goal points
 * RETURN:      null
 * PURPOSE:     determines the shortest path from start to goal 
 *              and displays the results.
 */
void findPath(int w[][HEIGHT], point s, point g) {
    point cur;
    cur.x = g.x; cur.y = g.y;
    cur.value = g.value;

    stack<point> path;
    path.push(cur);

    point smallest;
    smallest.x = cur.x; smallest.y = cur.y;
    smallest.value = 999;
    while (cur.value != s.value) {
        // check NORTH
        if (cur.y > 0) {
            if (w[cur.x][cur.y-1] < smallest.value && 
                w[cur.x][cur.y-1] > 1) {
                smallest.x = cur.x; smallest.y = cur.y-1;
                smallest.value = w[cur.x][cur.y-1];
            }
        }
        // check EAST
        if (cur.x < WIDTH-1) {
            if (w[cur.x+1][cur.y] < smallest.value &&
                w[cur.x+1][cur.y] > 1) {
                smallest.x = cur.x+1; smallest.y = cur.y;
                smallest.value = w[cur.x+1][cur.y];
            }
        }
        // check SOUTH
        if (cur.y < HEIGHT-1) {
            if (w[cur.x][cur.y+1] < smallest.value &&
                w[cur.x][cur.y+1] > 1) {
                smallest.x = cur.x; smallest.y = cur.y+1;
                smallest.value = w[cur.x][cur.y+1];
            }
        }
        // check WEST
        if (cur.x > 0) {
            if (w[cur.x-1][cur.y] < smallest.value &&
                w[cur.x-1][cur.y] > 1) {
                smallest.x = cur.x-1; smallest.y = cur.y;
                smallest.value = w[cur.x-1][cur.y];
            }
        }
        
        path.push(smallest);
        cur.x = smallest.x; cur.y = smallest.y;
        cur.value = smallest.value;
    }

    point temp;
    printf("The number of steps from (%i, %i) to (%i, %i) is %i\n",
            s.x, s.y, g.x, g.y, path.size());
    printf("The path is: (%i, %i)", s.x, s.y);
    path.pop();
    while (path.size() > 0) {
        temp = path.top();
        path.pop();
        printf(",(%i, %i)",temp.x,temp.y);
    }
    cout << endl;
}

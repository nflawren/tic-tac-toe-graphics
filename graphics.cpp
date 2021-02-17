#include "graphics.h"
#include "Button.cpp"
#include <vector>

using namespace std;

GLdouble width, height;
int wd;
vector<Button> grid;
enum screen {startScreen, play, endScreen};
screen currentScreen = startScreen;
string endMessage;

bool threeInARow(){
    for (int i=0; i<9; i+=3) {
        if (grid[i].getValue() == grid[i + 1].getValue() and grid[i + 1].getValue() == grid[i + 2].getValue() and grid[i + 2].getValue() != 0) {
            if (grid[i].getValue() =='x') {
                endMessage = "X wins!";
            } else {
                endMessage = "O wins!";
            }
            return true;
        }
    }
    for (int i=0; i<3; ++i){
        if (grid[i].getValue()==grid[i+3].getValue() and grid[i].getValue()==grid[i+6].getValue() and grid[i].getValue()!=0){
            if (grid[i].getValue() =='x') {
                endMessage = "X wins!";
            } else {
                endMessage = "O wins!";
            }
            return true;
        }
    }
    if (grid[0].getValue() == grid[4].getValue() and grid[4].getValue()==grid[8].getValue() and grid[0].getValue()!=0){
        if (grid[0].getValue() =='x') {
            endMessage = "X wins!";
        } else {
            endMessage = "O wins!";
        }
        return true;
    }
    if (grid[2].getValue() == grid[4].getValue() and grid[4].getValue()==grid[6].getValue() and grid[2].getValue()!=0){
        if (grid[2].getValue() =='x') {
            endMessage = "X wins!";
        } else {
            endMessage = "O wins!";
        }
        return true;
    }
    bool flag = true;
    for (Button &b: grid){
        if (b.getValue() == 0){
            cout<<b.getValue();
            flag = false;
        }
    }
    if (flag){
        endMessage = "It's a tie!";
        return true;
    }
    return false;
}

void initGrid() {
    grid.clear();
    grid.push_back(Button(skyBlue, {150,350}, 100,100,""));
    grid.push_back(Button(skyBlue, {250,350}, 100,100,""));
    grid.push_back(Button(skyBlue, {350,350}, 100,100,""));
    grid.push_back(Button(skyBlue, {150,250}, 100,100,""));
    grid.push_back(Button(skyBlue, {250,250}, 100,100,""));
    grid.push_back(Button(skyBlue, {350,250}, 100,100,""));
    grid.push_back(Button(skyBlue, {150,150}, 100,100,""));
    grid.push_back(Button(skyBlue, {250,150}, 100,100,""));
    grid.push_back(Button(skyBlue, {350,150}, 100,100,""));
}

void init() {
    width = 500;
    height = 500;
    initGrid();
}

void initGL() {
    glClearColor(skyBlue.red, skyBlue.green, skyBlue.blue, 1.0f);
}

void display() {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (currentScreen == startScreen){
        string label = "Press 's' to Play Tic Tac Toe";
        glColor3f(1, 1, 1);
        glRasterPos2i(200, 250);
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }

    if (currentScreen == play) {
        for (Button &b : grid) {
            b.draw();
        }
        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2i(200, 400);
        glVertex2i(200, 100);

        glVertex2i(300, 400);
        glVertex2i(300, 100);

        glVertex2i(100, 300);
        glVertex2i(400, 300);

        glVertex2i(100, 200);
        glVertex2i(400, 200);
        glEnd();


    }

    if (currentScreen == endScreen){
        glColor3f(1, 1, 1);
        glRasterPos2i(200, 250);
        for (const char &letter : endMessage) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        string message = "Press (r) to play again";
        glRasterPos2i(140, 275);
        for (const char &letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }
    glFlush();
}

void kbd(unsigned char key, int x, int y) {
    if (key=='s'){
        if (currentScreen==startScreen) {
            currentScreen = play;
        }
    }
    if (key=='r'){
        if (currentScreen==endScreen){
            initGrid();
            currentScreen = play;
        }
    }
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:

            break;
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_UP:

            break;
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {
    for (Button &g : grid){
        if (g.isOverlapping(x,y)) {
            g.hover();
        } else {
            g.release();
        }
    }
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if (currentScreen==play){
        for (Button &g : grid) {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && g.isOverlapping(x, y)) {
                g.pressDown();
                if (threeInARow()) {
                    currentScreen = endScreen;
                }
            } else {
                g.release();
            }
        }
    }

    glutPostRedisplay();
}

void timer(int dummy) {

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Tic-Tac-Toe" /* title */ );



   // glFlush();  // Render now
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
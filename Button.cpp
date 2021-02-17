#include "Button.h"
#include "graphics.h"
#include "circle.cpp"
using namespace std;

bool xturn = true;
color skyBlue{77/255.0, 213/255.0, 240/255.0};
Button::Button(color fill, point center, unsigned int width, unsigned int height, std::string label) : Quad(fill, center, width, height) {
    this->label = label;
    originalFill = fill;
    hoverFill = {fill.red + 0.5, fill.green + 0.5, fill.blue + 0.5};
    pressFill = {fill.red - 0.5, fill.green - 0.5, fill.blue - 0.5};
}

void Button::draw() const {
    Quad::draw();
    glColor3f(0, 0, 0);
    glRasterPos2i(center.x - (4 * label.length()), center.y + 7);
    for (const char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
    if((flagx or setx) and !seto) {
        if (setx) {
            glColor3f(0, 0, 0);
        } else {
            glColor3f(0.5, 0.5, 0.5);
        }
        glBegin(GL_LINES);
        glVertex2i(this->getLeftX()+10,this->getBottomY()-10);
        glVertex2i(this->getLeftX()+90,this->getBottomY()-90);
        glVertex2i(this->getLeftX()+10,this->getBottomY()-90);
        glVertex2i(this->getLeftX()+90,this->getBottomY()-10);

        glEnd();
    } else if((flago or seto) and !setx){
        if (seto){
            glColor3f(0,0,0);
        } else {
            glColor3f(0.5,0.5,0.5);
        }
        Circle outerO;
        if (seto) {
            outerO.setColor(0, 0, 0, 0);
        } else {
            outerO.setColor(0.5,0.5,0.5,0);
        }
        outerO.setCenter(this->getCenterX(), this->getCenterY());
        outerO.setRadius(45);
        outerO.draw();
        Circle innerO;
        innerO.setColor(skyBlue);
        innerO.setRadius(43.5);
        innerO.setCenter(this->getCenterX(),this->getCenterY());
        innerO.draw();
    }
}

/* Returns true if the coordinate is inside the box */
bool Button::isOverlapping(int x, int y) const {
    if(x<this->getRightX() && x>this->getLeftX() && y<this->getBottomY() && y>this->getTopY()){
        return true;
    }
    return false; // Placeholder for compilation
}

/* Change color of the box when the user is hovering over it */
void Button::hover() {
    //draw x
    if(xturn) {
        flagx = true;
        //setColor(hoverFill);
    } else {
        flago = true;
    }
}

/* Change color of the box when the user is clicking on it */
void Button::pressDown() {
    if(xturn){
        this->setx = true;
        xturn = false;
    } else {
        this->seto = true;
        xturn = true;
    }
}

/* Change the color back when the user is not clicking/hovering */
void Button::release() {
    flagx=false;
    flago=false;
    setColor(originalFill);
}

char Button::getValue() {
    if (setx){
        return 'x';
    } else if (seto){
        return 'o';
    } else {
        return 0;
    }
}
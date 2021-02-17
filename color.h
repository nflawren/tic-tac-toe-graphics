#ifndef GRAPHICS_STARTER_COLOR_H
#define GRAPHICS_STARTER_COLOR_H

struct color {
    double red;
    double green;
    double blue;
    double alpha; // Opacity (0 is transparent, 1 is solid)

    /* Constructors */
    color();
    color(double r, double g, double b);
    color(double r, double g, double b, double a);

};

#endif //GRAPHICS_STARTER_COLOR_H

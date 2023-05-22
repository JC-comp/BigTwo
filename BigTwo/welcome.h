#ifndef WELCOME_H
#define WELCOME_H

#include "screen.h"

class Welcome: public Screen
{
    using Screen::Screen;
public:
    void show(QGraphicsScene * scene);
};

#endif // WELCOME_H

#ifndef DESIGN_H
#define DESIGN_H

#include <QString>

class QPushButton;

class Design
{
public:
    Design();
    static void setButton(QPushButton * btn, int w, int h, QString location);
};

#endif // DESIGN_H

#include "design.h"
#include <QPixmap>
#include <QIcon>
#include <QPushButton>

Design::Design()
{

}

void Design::setButton(QPushButton * btn, int w, int h, QString location)
{
    QPixmap pm(location);
    QIcon editButtonIcon(pm);
    btn->setFlat(true);
    btn->setAutoFillBackground(true);
    btn->setIcon(editButtonIcon);
    btn->setIconSize(pm.rect().size());
    btn->setFixedSize(w,h);
}

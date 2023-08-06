#include "platform.h"
Platform::Platform(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap("://Platform2.png").scaled(QSize(200, 100)));
    setPos(300, -1500);
}

void Platform::deletePlatform() {
    if ((this->y() - doodlerY) > 1000) delete this; // delete platforms when too high
}

void Platform::advance(int phase) {
    deletePlatform();
}

qreal Platform::doodlerY = 0;

qreal& Platform::getY() {
    return doodlerY;
}

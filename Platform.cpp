#include "platform.h"
Platform::Platform(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap("://Platform2.png").scaled(QSize(200, 100)));
    setPos(300, -1500);

    // Create rand spring or rocket
    platformItem = new Spring();
    platformItem->show();
}

void Platform::deletePlatform() {
    if ((this->y() - doodlerY) > 1000) {
        if (platformItem) {
            delete platformItem;
            platformItem = nullptr; // protection for Platform::advance func
        }
        delete this; // delete platforms when too high
    }
}

void Platform::advance(int phase) {
    deletePlatform();
    if (platformItem) platformItem->setPos(this->x() + 50, this->y()+30); // add item to platform
}

qreal Platform::doodlerY = 0;

void Platform::getDoodlerY(qreal y) {
    doodlerY = y;
}

QGraphicsPixmapItem* Platform::getPlatformItem() {
    return platformItem;
}

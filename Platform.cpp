#include "platform.h"
Platform::Platform(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap("://images/Platform2.png").scaled(QSize(200, 100)));
    setPos(300, -1500);

    // Create rand spring or rocket
    int x = rand() % 3;
    switch (rand() % 3) {
        case 1:
            platformItem = new Spring();
            break;
        case 2:
            platformItem = new Rocket();
            break;
    }
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
    if (platformItem && (dynamic_cast<Spring*>(platformItem))) platformItem->setPos(this->x() + 50, this->y() + 30); // add item to platform
    if (platformItem && (dynamic_cast<Rocket*>(platformItem))) platformItem->setPos(this->x() + 50, this->y() - 20); // add item to platform
}

qreal Platform::doodlerY = 0;

void Platform::getDoodlerY(qreal y) {
    doodlerY = y;
}

QGraphicsPixmapItem* Platform::getPlatformItem() {
    return platformItem;
}

#ifndef PLATFORM_H
#define PLATFORM_H

#include <platformitems.h>
#include <stdlib.h>
#include <typeinfo>

class Platform : public QGraphicsPixmapItem {
public:
    Platform(QGraphicsItem* parent = nullptr);
public:
    void deletePlatform();
public slots:
    virtual void advance(int phase);
    static void getDoodlerY(qreal y);
    QGraphicsPixmapItem* getPlatformItem();
private:
    static qreal doodlerY;
    QGraphicsPixmapItem* platformItem = nullptr;
};

#endif // PLATFORM_H

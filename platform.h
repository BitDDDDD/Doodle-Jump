#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsPixmapItem>
class Platform : public QGraphicsPixmapItem {
public:
    Platform(QGraphicsItem* parent = nullptr);
public:
    void deletePlatform();
public slots:
    virtual void advance(int phase);
    static qreal& getY();
private:
    static qreal doodlerY;
};

#endif // PLATFORM_H

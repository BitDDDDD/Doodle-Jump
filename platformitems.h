#ifndef PLATFORMITEMS_H
#define PLATFORMITEMS_H

#include <QGraphicsPixmapItem>

class Spring : public QGraphicsPixmapItem {
public:
    Spring(QGraphicsItem* parent = nullptr);
};

class Rocket : public QGraphicsPixmapItem {
public:
    Rocket(QGraphicsItem* parent = nullptr);
};

class Bonker : public QGraphicsPixmapItem {
public:
     Bonker(QgraphicsItem* parent = nullptr);
};

#endif // PLATFORMITEMS_H

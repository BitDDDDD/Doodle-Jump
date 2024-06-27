#include "platformitems.h"

Spring::Spring(QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap("://images/Spring3.png").scaled(QSize(50, 25)));
}

Rocket::Rocket(QGraphicsItem *parent)
{
    setPixmap(QPixmap("://images/Rocket2.png").scaled((QSize(50,90))));
}
Bonker::Bonker(QgraphicsItem *parent)
     setPixmap(QPixmap("://images/Bonker.png").scaled((QSize(50,100)));
}

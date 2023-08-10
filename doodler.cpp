#include "doodler.h"

Doodler::Doodler() {
    setPixmap(QPixmap("://Doodler2.png").scaled(QSize(100, 100)));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Doodler::advance(int phase) {
    foreach(QGraphicsItem* item, collidingItems()) {
        if (typeid(*item) == typeid(Platform) && (yspeed > 0)) { // yspeed > 0 means doodler fall
            yspeed = maxUpSpeed; // do jump
        }
        if (typeid(*item) == typeid(Spring) && (yspeed > 0)) { // yspeed > 0 means doodler fall
            yspeed = springSpeed; // do jump
        }
    }

    jump();
    fall();

}

void Doodler::jump() {
    if (state == noSpeed) return;
    if (yspeed < 0) {
        moveBy(xspeed, yspeed);
        yspeed+= 0.0008;
        if ((yspeed + 0.0008) > 0) yspeed = 0.2; // for more smooth fall
    }
}

void Doodler::fall() {
    if (state == noSpeed) return;
    if (yspeed < maxDownSpeed) {
        yspeed+= 0.0008;
        moveBy(xspeed, yspeed);
    }
    else {
        yspeed = maxDownSpeed;
        moveBy(xspeed, yspeed);
    }
}

void Doodler::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Right:
            xspeed = 0.5;
            break;
        case Qt::Key_Left:
            xspeed = -0.5;
            break;
        default:
            break;
    }
}

void Doodler::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Right:
            xspeed = 0;
        case Qt::Key_Left:
            xspeed = 0;
        default:
            break;
    }
}
void Doodler::outOfBoundaries() {
    if ((1500 - this->x())  < 400) this->setPos(this->x() - 20400, this->y()); // right
    if ((this->x() + 1200)  < 400) this->setPos(this->x() + 1850, this->y()); // left
}

void Doodler::stop() {
    state = noSpeed;
}

void Doodler::cont() {
    state = normalSpeed;
}



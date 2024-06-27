#ifndef DOODLER_H
#define DOODLER_H

#include <QTimer>
#include <QKeyEvent>
#include <QMediaPlayer>
#include "platform.h"

class Doodler : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Doodler();
    void jump();
    void fall();
    void outOfBoundaries();
    void stop();
    void cont();

public slots:
    virtual void advance(int phase);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    qreal maxUpSpeed          = -1;
    qreal maxDownSpeed        = 1;
    qreal springSpeed         = -2;
    qreal rocketSpeed         = -4;
    qreal bonkerSpeed         = -8;
    qreal xspeed              = 0;
    qreal yspeed              = maxDownSpeed;
    QMediaPlayer* jumpSound   = nullptr;
    QMediaPlayer* springSound = nullptr;
    QMediaPlayer* rocketSound = nullptr;
    QMediaPlayer* bonkerSound = nullptr;
    enum condition {noSpeed = 0, normalSpeed = 1};
    condition state = normalSpeed;
    bool doodlerUseRocket = false;
};

#endif // DOODLER_H

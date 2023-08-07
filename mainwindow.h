#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "doodler.h"
#include <QLabel>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void sceneMove();
    void platformGenerator(qreal doodlerPos);
    void menuGame();
    void startGame();
    void restartGame();
    void connectFun();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene        = nullptr;
    Doodler* doodler             = nullptr;
    qreal maxHighPlatfrom        = 0;
    int maxScore                 = 0;
    qreal startPosY              = -1500;
    QLabel* score                = nullptr;
    QPushButton* pause           = nullptr;
    QPushButton* continueGameBut = nullptr;
    QPushButton* startGameBut    = nullptr;
    QPushButton* restartGameBut  = nullptr;
    QPushButton* exitGameBut     = nullptr;
    QPushButton* menuBut         = nullptr;
    QTimer* Timer                = nullptr;
};

#endif // MAINWINDOW_H

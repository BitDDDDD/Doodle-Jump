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
    void createMenuGame();
    void startGame();
    void restartGame();
    void connectFun();
    void showMenu();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene        = nullptr;
    bool firtStart               = true;
    Doodler* doodler             = nullptr;
    qreal maxHighPlatfrom        = -2500;
    int maxScore                 = 0;
    qreal startPosY              = -1500;
    int recordInt                = 0;
    QLabel* score                = nullptr;
    QLabel* recordLab            = nullptr;
    QPushButton* pause           = nullptr;
    QPushButton* continueGameBut = nullptr;
    QPushButton* startGameBut    = nullptr;
    QPushButton* restartGameBut  = nullptr;
    QPushButton* exitGameBut     = nullptr;
    QPushButton* menuBut         = nullptr;
    QTimer* Timer                = nullptr;
};

#endif // MAINWINDOW_H

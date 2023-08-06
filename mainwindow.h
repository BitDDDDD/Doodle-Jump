#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "doodler.h"
#include <QLabel>
#include <QPushButton>
#include <vector>

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
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene = nullptr;
    Doodler* doodler = nullptr;
    qreal maxHighPlatfrom = 0;
    int maxScore = 0;
    qreal startPos = -1500;
    QLabel* score = nullptr;
    QPushButton* pause = nullptr;
    QPushButton* unPause = nullptr;
    std::vector<Platform*> platformVec;
};

#endif // MAINWINDOW_H

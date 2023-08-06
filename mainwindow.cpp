#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(0, 0, 0, 0, this);
    ui->graphicsView->setScene(scene);

    QWidget::showMaximized(); // max size window

    // Set background
    this->setStyleSheet("background-image: url(://Checkered sheet.jpg);");

    // hide scrollbar
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Doodler
    doodler = new Doodler;
    doodler->setPos(300, -1500); //-1500
    scene->addItem(doodler);

    // Platforms
    Platform* platform = new Platform;
    Platform* platform2 = new Platform;
    Platform* platform3 = new Platform;
    platform2->setPos(100, -2000);
    platform3->setPos(-200, -2500);
    scene->addItem(platform);
    scene->addItem(platform2);
    scene->addItem(platform3);

    // Score
    score = new QLabel(this);
    score->show();
    score->move(20, 25);
    score->setStyleSheet("QLabel{font-size: 18pt;}");
    scene->addWidget(score);

    // Buttons
    pause = new QPushButton(this);
    scene->addWidget(pause);
    pause->setText("Pause");
    pause->setStyleSheet("background-color: black;");
    pause->show();
    pause->setGeometry(1808, 23, 100, 30);
    unPause = new QPushButton(this);

    scene->setStickyFocus(true);

    QTimer* Timer = new QTimer(this);
    Timer->start(2);
    connect(Timer, QTimer::timeout, scene, QGraphicsScene::advance);
    connect(Timer, QTimer::timeout, this, [=]{ scene->setSceneRect(0, -maxScore+startPos + 100, 400, 400); }); // scene at level of dooler's max score + 100
    //connect(Timer, QTimer::timeout, this, [=]{ Platform::getY() = doodler->y(); }); // platforms know where is doodler at Y. For deleting platforms
    connect(Timer, QTimer::timeout, this, [this]{ doodler->outOfBoundaries(); } ); // teleport Doodler if out of boundaries
    connect(Timer, QTimer::timeout, this, [this]{ platformGenerator(doodler->y()); }); // platform generator
    connect(Timer, QTimer::timeout, this, [this]{
        if (-doodler->y() > maxScore - startPos) {
            maxScore = -doodler->y() + startPos;
            score->setText(QString::number(int((-doodler->y() + startPos) / 4)));
        }
    });
    connect(pause, &QPushButton::clicked, this, [this]{ doodler->stop(); });
}
void MainWindow::platformGenerator(qreal doodlerPos) {
    static qreal y = -2500;

    if ((doodlerPos - y) < 900 && (doodlerPos - y) > 400) {
        y-=500;
        Platform* newPlatform = new Platform();
        platformVec.push_back(newPlatform);
        int x = rand() % 1300 - 500;
        newPlatform->setPos(x, y);
        newPlatform->setZValue(-1);
        maxHighPlatfrom = y;
        scene->addItem(newPlatform);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

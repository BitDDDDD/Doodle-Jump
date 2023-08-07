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

    menuGame(); // call menu of game
}
void MainWindow::connectFun() {
    Timer = new QTimer(this);
    Timer->start(2);
    connect(Timer, QTimer::timeout, scene, QGraphicsScene::advance);
    connect(Timer, QTimer::timeout, this, [=]{ scene->setSceneRect(0, -maxScore+startPosY + 100, 400, 400); }); // scene at level of dooler's max score + 100
    connect(Timer, QTimer::timeout, this, [=]{ Platform::getY() = doodler->y(); }); // platforms know where is doodler at Y. For deleting platforms
    connect(Timer, QTimer::timeout, this, [this]{ doodler->outOfBoundaries(); } ); // teleport Doodler if out of boundaries
    connect(Timer, QTimer::timeout, this, [this]{ platformGenerator(doodler->y()); }); // platform generator
    connect(Timer, QTimer::timeout, this, [this]{ // chaneg score
        if (-doodler->y() > maxScore - startPosY) {
            maxScore = -doodler->y() + startPosY;
            score->setText(QString::number(int(maxScore/4)));
        }
    });
    connect(pause, &QPushButton::clicked, this, [this] { // pause pressed
        doodler->stop();
        continueGameBut->show();
        restartGameBut->show();
    });
    connect(continueGameBut, &QPushButton::clicked, this, [this] { // continue pressed
        doodler->cont();
        continueGameBut->hide();
        restartGameBut->hide();
    });
    connect(Timer, QTimer::timeout, this, [this] { // doolder die
        if ((maxScore - (-doodler->y())) > 520) { restartGameBut->show(); }}
    );
    connect(restartGameBut, &QPushButton::clicked, this, [this] {
       restartGame();
    });
}

void MainWindow::platformGenerator(qreal doodlerPos) {
    static qreal y = -2500;

    if ((doodlerPos - y) < 900 && (doodlerPos - y) > 400) {
        y-=500;
        Platform* newPlatform = new Platform();
        int x = rand() % 1300 - 500;
        newPlatform->setPos(x, y);
        newPlatform->setZValue(-1);
        maxHighPlatfrom = y;
        scene->addItem(newPlatform);
    }
}

void MainWindow::startGame() {
    // Doodler
    doodler = new Doodler;
    doodler->setPos(300, -1500); //-1500
    scene->addItem(doodler);

    // Platforms
    Platform* platform  = new Platform;
    Platform* platform2 = new Platform;
    Platform* platform3 = new Platform;
    platform2->setPos(100, -2000);
    platform3->setPos(-200, -2500);
    platform2->setZValue(-1);
    platform3->setZValue(-1);
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

    continueGameBut = new QPushButton(this);
    scene->addWidget(continueGameBut);
    continueGameBut->setText("Continue");
    continueGameBut->setStyleSheet("background-color: black;");
    continueGameBut->setGeometry(880, 450, 200, 60);

    restartGameBut = new QPushButton(this);
    scene->addWidget(restartGameBut);
    restartGameBut->setText("Restart");
    restartGameBut->setStyleSheet("background-color: black;");
    restartGameBut->setGeometry(880, 520, 200, 60);


    scene->setStickyFocus(true);

    connectFun();
}

void MainWindow::restartGame() {
    delete doodler;
    doodler = new Doodler;
    doodler->setPos(300, -1550);
    scene->addItem(doodler);

    maxScore = 0;

    Platform* platform  = new Platform;
    Platform* platform2 = new Platform;
    Platform* platform3 = new Platform;
    platform2->setPos(100, -2000);
    platform3->setPos(-200, -2500);
    platform2->setZValue(-1);
    platform3->setZValue(-1);
    scene->addItem(platform);
    scene->addItem(platform2);
    scene->addItem(platform3);

    continueGameBut->hide();
    restartGameBut->hide();
}

void MainWindow::menuGame() {
    startGameBut = new QPushButton(this);
    scene->addWidget(startGameBut);
    startGameBut->setText("Start");
    startGameBut->setGeometry(880, 400, 200, 60);
    startGameBut->show();

//    exitGameBut = new QPushButton(this);

    connect(startGameBut, &QPushButton::clicked, this, [this] {
        startGame();
        startGameBut->hide();
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

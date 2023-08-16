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

    createMenuGame(); // call menu of game
}

void MainWindow::connectFun() {
    Timer = new QTimer(this);
    Timer->start(2);
    connect(Timer, QTimer::timeout, scene, QGraphicsScene::advance);
    connect(Timer, QTimer::timeout, this, [=]{ scene->setSceneRect(0, -maxScore+startPosY + 100, 400, 400); }); // scene at level of dooler's max score + 100
    connect(Timer, QTimer::timeout, this, [=]{ Platform::getDoodlerY(doodler->y()); }); // platforms know where is doodler at Y. For deleting platforms
    connect(Timer, QTimer::timeout, this, [this]{ doodler->outOfBoundaries(); } ); // teleport Doodler if out of boundaries
    connect(Timer, QTimer::timeout, this, [this]{ platformGenerator(doodler->y()); }); // platform generator
    connect(Timer, QTimer::timeout, this, [this]{ // chaneg score
        if (-doodler->y() > maxScore - startPosY) {
            maxScore = -doodler->y() + startPosY;
            score->setText(QString::number(int(maxScore/4)));

            if (maxScore > recordInt) {
                recordInt = maxScore;
                recordLab->setText("Record = " +  QString::number(recordInt/4));
            }
        }
    });
    connect(pauseBut, &QPushButton::clicked, this, [this] { // pause pressed
        doodler->stop();
        continueGameBut->show();
        restartGameBut->show();
        menuBut->show();
    });
    connect(continueGameBut, &QPushButton::clicked, this, [this] { // continue pressed
        doodler->cont();
        continueGameBut->hide();
        restartGameBut->hide();
        menuBut->hide();
    });
    connect(Timer, QTimer::timeout, this, [this] { // doolder die
        if ((maxScore - (-doodler->y())) > 520) {

            restartGameBut->setGeometry(880, 400, 200, 60);
            exitGameBut->setGeometry(880, 470, 200, 60);

            restartGameBut->show();
            exitGameBut->show();
        }}
    );
    connect(restartGameBut, &QPushButton::clicked, this, [this] { // put restart button
       restartGame();
    });
    connect(menuBut, &QPushButton::clicked, this, [this] { showMenu(); });
}

void MainWindow::showMenu() {
    continueGameBut->hide();
    restartGameBut->hide();
    menuBut->hide();

    startGameBut->show();
    exitGameBut->show();
    recordLab->show();
}

void MainWindow::platformGenerator(qreal doodlerPos) {
    if ((doodlerPos - maxHighPlatfrom) < 900 && (doodlerPos - maxHighPlatfrom) > 400) {
        maxHighPlatfrom -= 500;
        Platform* newPlatform = new Platform();
        newPlatform->setPos(rand() % 1300 - 500, maxHighPlatfrom);
        newPlatform->setZValue(-1);
        scene->addItem(newPlatform);
        if (newPlatform->getPlatformItem()) {
            scene->addItem(newPlatform->getPlatformItem());
            newPlatform->getPlatformItem()->setZValue(-1);
        }
    }
}

void MainWindow::startGame() {
    // First run
    if (!firtStart) {
        restartGame();
        return;
    }

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
    pauseBut = new QPushButton(this);
    scene->addWidget(pauseBut);
    pauseBut->setText("Pause");
    pauseBut->setStyleSheet("background-color: black;");
    pauseBut->show();
    pauseBut->setGeometry(1808, 23, 100, 30);

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

    menuBut = new QPushButton(this);
    scene->addWidget(menuBut);
    menuBut->setText("Menu");
    menuBut->setStyleSheet("background-color: black;");
    menuBut->setGeometry(880, 590, 200, 60);

    scene->setStickyFocus(true);

    firtStart = false;

    connectFun();
}

void MainWindow::restartGame() {
    maxHighPlatfrom = -2500;

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
    exitGameBut->hide();
    menuBut->hide();

    // return buttons to priv pos
    restartGameBut->setGeometry(880, 520, 200, 60);
    exitGameBut->setGeometry(880, 470, 200, 60);
}

void MainWindow::createMenuGame() {
    startGameBut = new QPushButton(this);
    scene->addWidget(startGameBut);
    startGameBut->setText("Start");
    startGameBut->setGeometry(880, 400, 200, 60);
    startGameBut->setStyleSheet("background-color: black;");
    startGameBut->show();

    exitGameBut = new QPushButton(this);
    scene->addWidget(exitGameBut);
    exitGameBut->setText("Exit");
    exitGameBut->setGeometry(880, 470, 200, 60);
    exitGameBut->setStyleSheet("background-color: black;");
    exitGameBut->show();

    // Record
    recordLab = new QLabel(this);
    recordLab->show();
    recordLab->setGeometry(920, 200, 300, 50);
    recordLab->setStyleSheet("QLabel{font-size: 18pt;}");
    scene->addWidget(recordLab);
    recordLab->setText("Record = 0");
    recordLab->show();

    connect(startGameBut, &QPushButton::clicked, this, [this] {
        startGame();
        startGameBut->hide();
        exitGameBut->hide();
        recordLab->hide();
    });
    connect(exitGameBut, &QPushButton::clicked, this, [this] {
        exit(0);
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

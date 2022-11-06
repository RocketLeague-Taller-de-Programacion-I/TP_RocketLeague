#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Button.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Seteo un Objeto QGraphicsScene para manejar la escena del juego
    ui->view->setScene(&this->scene);
    ui->view->setStyleSheet("border-image: url(/home/roby/Documents/FIUBA/EnCurso/Taller de Programacion I/TP3/TP_RocketLeague/images/rocketLig.jpg);");
}

void MainWindow::start() {
    // clear the screen
    this->scene.clear();

    //set menu background
    ui->view->setStyleSheet("border-image: url(/home/roby/Documents/FIUBA/EnCurso/Taller de Programacion I/TP3/TP_RocketLeague/images/menu.png);");

    drawGUI();
}

void MainWindow::drawGUI() {
    drawTitle();
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Welcome "));
    QFont titleFont("comic sans",32);
    titleText->setFont(titleFont);
    int txPos = width() / 2 - titleText->boundingRect().width() / 2;
    int tyPos = 120;
    titleText->setPos(txPos,tyPos);
    scene.addItem(titleText);

    drawCreateButton();
    drawJoinButton();
    drawBackButton();
}

void MainWindow::drawCreateButton() {
    // create the create game button
    Button* createGameButton = new Button(QString("Create Game"));
    int bxPos = width() / 2 - createGameButton->boundingRect().width() / 2;
    int byPos = 300;
    createGameButton->setPos(bxPos,byPos);
    connect(createGameButton,SIGNAL(clicked()),this,SLOT(createGame()));
    scene.addItem(createGameButton);
}

void MainWindow::drawTitle() {
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Rocket League"));
    QFont titleFont("comic sans",60);
    titleText->setFont(titleFont);
    int txPos = width() / 2 - titleText->boundingRect().width() / 2;
    int tyPos = 0;
    titleText->setPos(txPos,tyPos);
    scene.addItem(titleText);
}

void MainWindow::displayMainMenu() {
    // create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = 1250 - playButton->boundingRect().width()/2;
    int byPos = 600;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    this->scene.addItem(playButton);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawJoinButton() {
    // create the join game button
    Button* joinGameButton = new Button(QString("Join Game"));
    int bxPos = width() / 2 - joinGameButton->boundingRect().width() / 2;
    int byPos = 400;
    joinGameButton->setPos(bxPos,byPos);
    connect(joinGameButton,SIGNAL(clicked()),this,SLOT(joinGame()));
    scene.addItem(joinGameButton);
}

void MainWindow::drawBackButton() {
    // create the back button
    Button* backButton = new Button(QString("Back"));
    int bxPos = width() / 2 - backButton->boundingRect().width() / 2;
    int byPos = 500;
    backButton->setPos(bxPos,byPos);
    connect(backButton,SIGNAL(clicked()),this,SLOT(back()));
    scene.addItem(backButton);
}


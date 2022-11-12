#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Button.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent, BlockingQueue<std::string> &updatesQueue)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , updatesQueue(updatesQueue)
{
    ui->setupUi(this);
    // Seteo un Objeto QGraphicsScene para manejar la escena del juego
    ui->view->setScene(&this->scene);
    ui->view->setStyleSheet("border-image: url(/home/roby/Documents/FIUBA/EnCurso/Taller de Programacion I/TP3/TP_RocketLeague/images/rocketLig.jpg);");
    this->lineEdit = findChild<QLineEdit*>("lineEditName");
    this->cantPlayers = findChild<QSpinBox*>("cantPlayers");
    this->label = findChild<QLabel*>("label");
}

void MainWindow::start() {
    // clear the screen
    this->scene.clear();
    this->lineEdit->hide();
    this->cantPlayers->hide();
    this->label->hide();

    //set menu background
    ui->view->setStyleSheet("border-image: url(/home/roby/Documents/FIUBA/EnCurso/Taller de Programacion I/TP3/TP_RocketLeague/images/menu.png);");

    drawGUI();
}

void MainWindow::createGame() {
    // clear the screen
    this->scene.clear();
    // draw create game menu
    drawCreateGameMenu();
}

void MainWindow::joinGame() {
    // clear the screen
    this->scene.clear();

    drawTitle("Join Game");
    //list all the games
    //draw a button for each game
    std::map<std::string, std::string> games;
    games["game1"] = "1/2";
    games["game2"] = "2/2";
    games["game3"] = "1/3";
    int i = 200;
    foreach(auto game, games) {
        QString roomName = QString::fromStdString(game.first);
        QString players = QString::fromStdString(game.second);
        Button* button = new Button( QString("%1 %2").arg(roomName,players));
        connect(button,SIGNAL(clicked()),this,SLOT(joinParticularGame()));
        this->scene.addItem(button);
        button->setPos(width() / 2 - button->boundingRect().width() / 2, i);
        i += 100;
    }
    //crear evento de listar juegos
    drawBackButton();
}

void MainWindow::joinParticularGame() {
    // clear the screen
    this->scene.clear();

    // crear evento de join ()
    std::string action = "join";
    // agregar a la cola de eventos
    this->updatesQueue.push(action);
    //exit qt
    close();
}

void MainWindow::back() {
    // clear the screen
    this->scene.clear();
    this->lineEdit->clear();
    this->lineEdit->setPlaceholderText("Enter your name");
    this->lineEdit->setGeometry(1150, 530, 301, 71);
    this->cantPlayers->setValue(0);

    displayMainMenu();
}

void MainWindow::drawGUI() {
    drawTitle("Rocket League");

    if(this->lineEdit != nullptr and std::equal(this->userName.begin(), this->userName.end(), "stranger")) {
        std::cout << this->lineEdit->text().toStdString() << std::endl;
        userName = this->lineEdit->text();
        this->lineEdit->hide();
    }
    QString name = userName;
    QString greetings = QString("Welcome %1").arg(name);

    QGraphicsTextItem* titleText = new QGraphicsTextItem(greetings);
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

void MainWindow::displayMainMenu() {
    //set menu background
    ui->view->setStyleSheet("border-image: url(/home/roby/Documents/FIUBA/EnCurso/Taller de Programacion I/TP3/TP_RocketLeague/images/rocketLig.jpg);");
    this->lineEdit->show();
    this->cantPlayers->hide();
    this->label->hide();

    drawPlayButton();
}

void MainWindow::drawCreateGameMenu() {
    // draw title
    drawTitle("Create Game");

    // draw room name line edit
    this->lineEdit->setGeometry(width() / 2 - 110 , 200 , 301, 71);
    this->lineEdit->clear();
    this->lineEdit->show();
    this->lineEdit->setPlaceholderText("Room Name");
    this->cantPlayers->show();
    this->label->show();

    // draw save and start button
    drawPlayButton();
    // draw back button
    drawBackButton();
}

void MainWindow::drawTitle(std::string title) {
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString(title.c_str()));
    QFont titleFont("comic sans",60);
    titleText->setFont(titleFont);
    int txPos = width() / 2 - titleText->boundingRect().width() / 2;
    int tyPos = 0;
    titleText->setPos(txPos,tyPos);
    scene.addItem(titleText);
}

void MainWindow::drawPlayButton() {// create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = 1250 - playButton->boundingRect().width()/2;
    int byPos = 600;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene.addItem(playButton);
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
    int bxPos = width() / 5 - backButton->boundingRect().width() / 2;
    int byPos = 600;
    backButton->setPos(bxPos,byPos);
    connect(backButton,SIGNAL(clicked()),this,SLOT(back()));
    scene.addItem(backButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}


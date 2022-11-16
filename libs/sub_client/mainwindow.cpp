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
    ui->view->setStyleSheet("border-image: url(/home/roby/Documents/FIUBA/EnCurso/Taller de Programacion I/TP3/TP_RocketLeague/images/menu.png);");

    // place player 1 text
    QGraphicsTextItem* p1 = new QGraphicsTextItem("Player 1's Cards: ");
    p1->setPos(25,0);
    this->scene.addItem(p1);
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


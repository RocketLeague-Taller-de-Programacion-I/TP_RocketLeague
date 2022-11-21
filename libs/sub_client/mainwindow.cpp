#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sub_common/ActionUpdate.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent, BlockingQueue<Action *> &updates, BlockingQueue<Action *> &actions)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , updatesQueue(updates)
    , actionsQueue(actions)
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

void MainWindow::drawCreateGameMenu() {
    // clear the screen
    this->scene.clear();
    // draw create game menu
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
    drawSaveAndStartButton();
    // draw back button
    drawBackButton();
}

void MainWindow::drawJoinGameMenu() {
    // clear the screen
    this->scene.clear();

    drawTitle("Join Game");
    //list all the games
    //draw a button for each game
    uint8_t id = 0;
    Action* actionList = new ActionList(id);
    this->actionsQueue.push(actionList);

    auto update = this->updatesQueue.pop();

    std::vector<std::string> games = parseList(update->getGameName());

    int i = 200;
    foreach(auto game, games) {
        QString item = QString::fromStdString(game);
        Button* button = new Button( QString("%1").arg(item));
        connect(button, SIGNAL(clicked(QString)), this, SLOT(joinParticularGame(QString)));
        this->scene.addItem(button);
        button->setPos(width() / 2 - button->boundingRect().width() / 2, i);
        i += 100;
    }
    //crear evento de listar juegos
    drawBackButton();
}

void MainWindow::createRoom() {
    std::string roomName = this->lineEdit->text().toStdString();
    uint8_t players = this->cantPlayers->value();
    uint8_t id = 0;
//    std::shared_ptr<Action> action(new ActionCreate(id,players,roomName));
//    this->actionsQueue.push(reinterpret_cast<Action *&>(action));
    Action* actionCreate = new ActionCreate(id, players, roomName);
    this->actionsQueue.push(actionCreate);

    std::cout << "Waiting for Update" << std::endl;
//    auto update = dynamic_cast<ActionUpdate *>(this->updatesQueue.pop());
//    std::cout << "Update received" << std::endl;
//
//    if (update->getIdCreatorGame()) {
//        std::cout << "Game created with id: " << (int)(update->getIdCreatorGame()) << std::endl;
//        this->lineEdit->hide();
//        this->cantPlayers->hide();
//        this->label->hide();
//        drawTitle("Waiting for players");
//    }
//    close();
    // draw waiting for players screen
    drawLoadingScreen();
}

void MainWindow::joinParticularGame(QString roomName) {
    // clear the screen
    this->scene.clear();

    // crear evento de join ()
    std::string room = roomName.toStdString();
    uint8_t id = 0;
    Action *actionJoin = new ActionJoin(id, room);
    this->actionsQueue.push(actionJoin);

    ActionUpdate *update = dynamic_cast<ActionUpdate *>(this->updatesQueue.pop());
    if (update->getIdCreatorGame()) {
        std::cout << "Game joined with id: " << (int)(update->getIdCreatorGame()) << std::endl;
        drawTitle("Waiting for players");
    }
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
    if(this->lineEdit != nullptr
        and this->lineEdit->text() != ""
        and std::equal(this->userName.begin(), this->userName.end(), "stranger"))
    {
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
    connect(createGameButton,SIGNAL(clicked()),this,SLOT(drawCreateGameMenu()));
    scene.addItem(createGameButton);
}

void MainWindow::drawJoinButton() {
    // create the join game button
    Button* joinGameButton = new Button(QString("Join Game"));
    int bxPos = width() / 2 - joinGameButton->boundingRect().width() / 2;
    int byPos = 400;
    joinGameButton->setPos(bxPos,byPos);
    connect(joinGameButton,SIGNAL(clicked()),this,SLOT(drawJoinGameMenu()));
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

void MainWindow::drawSaveAndStartButton() {
    // create the save and start button
    Button* saveAndStartButton = new Button(QString("Save and Start"));
    int bxPos = width() / 2 - saveAndStartButton->boundingRect().width() / 2;
    int byPos = 600;
    saveAndStartButton->setPos(bxPos,byPos);
    connect(saveAndStartButton,SIGNAL(clicked()),this,SLOT(createRoom()));
    scene.addItem(saveAndStartButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::vector<std::string> MainWindow::parseList(std::string basicString) {
    return std::vector<std::string>();
}

void MainWindow::drawLoadingScreen() {
    // clear the screen
    this->scene.clear();
    this->lineEdit->hide();
    this->cantPlayers->hide();
    this->label->hide();

    ui->view->setStyleSheet("border-image: url(/home/roby/Documents/FIUBA/EnCurso/Taller de Programacion I/TP3/TP_RocketLeague/images/loadingScreen.jpeg);");

    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Waiting for more players to join"));
    QFont titleFont("comic sans",40);
    titleText->setFont(titleFont);
    int txPos = width() / 2 - titleText->boundingRect().width() / 4;
    int tyPos = height() / 2;
    titleText->setPos(txPos,tyPos);
    scene.addItem(titleText);

    auto update = dynamic_cast<ActionUpdate *>(this->updatesQueue.pop());
    std::cout << "Update received" << std::endl;
    std::cout << "Game created with id: " << (int)(update->getIdCreatorGame()) << std::endl;

}


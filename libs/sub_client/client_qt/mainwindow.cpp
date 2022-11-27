
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <regex>

MainWindow::MainWindow(QWidget *parent, ProtectedQueue<ClientUpdate*> &updates, BlockingQueue<ClientAction *> &actions)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , updatesQueue(updates)
    , actionsQueue(actions)
{
    ui->setupUi(this);
    // Seteo un Objeto QGraphicsScene para manejar la escena del juego
    this->scene.setSceneRect(0,0,1500,750);

    ui->view->setScene(&scene);
    ui->view->setStyleSheet("border-image: url(../images/rocketLig.jpg);");
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
    ui->view->setStyleSheet("border-image: url(../images/menu.png);");

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
    ClientAction* action = new ActionListRooms();
    this->actionsQueue.push(action);
    //list all the games
    ClientUpdate* update;
    while (!updatesQueue.tryPop(update)) {
        //  wait for updates
    }
    //draw a button for each game
    if(update->getReturnCode() != OK){
        QLabel* label = new QLabel("No games available");
        label->setGeometry(width() / 2 - 110 , 200 , 301, 71);
        label->setStyleSheet("font: 20pt; color: white;");
        this->scene.addWidget(label);

    } else {
        std::map<std::string,std::string> games = dynamic_cast<ClientListACK*>(update)->getList();
        int i = 200;
                foreach(auto game, games) {
                QString name = QString::fromStdString(game.first);
                QString online_vs_max = QString::fromStdString(game.second);
                Button* button = new Button( QString("%1 %2").arg(name).arg(online_vs_max));
                connect(button, SIGNAL(clicked(QString)), this, SLOT(joinParticularGame(QString)));
                this->scene.addItem(button);
                button->setPos(width() / 2 - button->boundingRect().width() / 2, i);
                i += 100;
            }
    }

    //crear evento de listar juegos
    drawBackButton();
}

void MainWindow::createRoom() {

    this->scene.clear();

    std::string roomName = this->lineEdit->text().toStdString();
    uint8_t players = this->cantPlayers->value();
//    Action* actionCreate = new ActionCreate(id, players, roomName);
    ClientAction* actionCreate = new ActionCreateRoom(players, roomName);
    this->actionsQueue.push(actionCreate);
    popFirstUpdate();
//    exit(1); // TODO: usar exit para salir del juego
    close();
}

void MainWindow::joinParticularGame(QString roomName) {
    // clear the screen
    this->scene.clear();

    // crear evento de join ()
    std::string room = retrieveGameName(roomName.toStdString());
    std::cout << "Joining to " << room << std::endl;
    ClientAction *actionJoin = new ActionJoinRoom(room);
    this->actionsQueue.push(actionJoin);
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
    ui->view->setStyleSheet("border-image: url(../images/rocketLig.jpg);");
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

void MainWindow::drawLoadingScreen() {
    // clear the screen
    this->scene.clear();
    this->lineEdit->hide();
    this->cantPlayers->hide();
    this->label->hide();

    ui->view->setStyleSheet("border-image: url(../images/loadingScreen.jpeg);");

    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Waiting for more players to join"));
    QFont titleFont("comic sans",40);
    titleText->setFont(titleFont);
    int txPos = width() / 2 - titleText->boundingRect().width() / 4;
    int tyPos = height() / 2;
    titleText->setPos(txPos,tyPos);
    scene.addItem(titleText);
    popFirstUpdate();
    close();
}

void MainWindow::popFirstUpdate() {
    ClientUpdate* update;
    bool popping = true;
    while (popping) {
        //  wait for updates
        if(updatesQueue.tryPop(update) and update) {
            popping = false;
        }
    }
    std::cout << "Update received" << std::endl;
    std::cout << "Game created with id: " << (int)(update->getId()) << std::endl;
    std::cout << "Game created with returnmesage: " << (int)update->getReturnCode() << std::endl;

    if(update->getReturnCode()) {
        // error partida exisistia
        // error partida full
        // volver a home game
        drawGUI();
    }
    delete update;
}

std::string MainWindow::retrieveGameName(std::string basicString) {
    // create regex to match any substring until first number
    std::regex re(".+?(?=[0-9])");
    std::smatch match;

    std::regex_search(basicString, match, re);

//    std::string name = match.str().empty() ? "no name" : match.str();
    //std::string name = data.substr(0, data.find(match.str()));
    // result.insert(result.end(), name.begin(), name.end());
    std::string name = match.str().empty() ? "no name" : match.str();
    std::string stripped = name.substr(0, name.find_last_of(' '));
    return stripped;
}


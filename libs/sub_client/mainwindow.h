#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QString>
#include <QAction>

#include "gamescene.h"
#include "GameLoop.h"

#include "ActionCreateRoom.h"
#include "ActionJoinRoom.h"
#include "ActionListRooms.h"
#include "GameUpdate.h"

#include "Button.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QWidget *parent, ProtectedQueue<GameUpdate*> &updates, BlockingQueue<ClientAction *> &actions);
    ~MainWindow();

    void displayMainMenu();

public slots:
    void start();
    void back();
    void drawCreateGameMenu();
    void drawJoinGameMenu();
    void joinParticularGame(QString roomName);
    void createRoom();

private:
    Ui::MainWindow *ui;
    GameScene scene;
    ProtectedQueue<GameUpdate*> &updatesQueue;
    BlockingQueue<ClientAction*> &actionsQueue;

    void drawGUI();

    void drawTitle(std::string title);

    void drawCreateButton();

    void drawJoinButton();

    void drawBackButton();

    void drawPlayButton();

    void drawSaveAndStartButton();

    QLineEdit* lineEdit;
    QSpinBox* cantPlayers;
    QLabel *label;
    QString userName = QString("stranger");

    std::vector<std::string> parseList(std::string &basicString);

    void drawLoadingScreen();

    void popFirstUpdate();

    std::string retrieveGamaeName(std::string basicString);
};
#endif // MAINWINDOW_H

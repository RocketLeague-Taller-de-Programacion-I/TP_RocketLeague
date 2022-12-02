#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QString>
#include <QAction>
#include <QGraphicsScene>

#include "sub_client/client_sdl/GameLoop.h"

#include "sub_client/client_actions/ActionCreateRoom.h"
#include "sub_client/client_actions/ActionJoinRoom.h"
#include "sub_client/client_actions/ActionListRooms.h"

#include "sub_client/client_updates/ClientCreateACK.h"
#include "sub_client/client_updates/ClientJoinACK.h"
#include "sub_client/client_updates/ClientListACK.h"
#include "sub_client/client_updates/ClientStartedGameACK.h"

#include "Button.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(uint8_t &id, QWidget *parent, ProtectedQueue<std::shared_ptr<ClientUpdate>> &updates,
               BlockingQueue<std::optional<std::shared_ptr<ClientAction>>> &actions);
    ~MainWindow();

    void displayMainMenu();

public slots:
    void start();
    void back();
    void drawCreateGameMenu();
    void drawJoinGameMenu();
    void joinParticularGame(QString roomName);
    void createRoom();
    void clearScene() { this->scene.clear(); };

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    ProtectedQueue<std::shared_ptr<ClientUpdate>> &updatesQueue;
    BlockingQueue<std::optional<std::shared_ptr<ClientAction>>> &actionsQueue;

    uint8_t &id;

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

    void drawLoadingScreen();

    void popFirstUpdate();

    std::string retrieveGameName(const std::string& basicString);
};
#endif // MAINWINDOW_H

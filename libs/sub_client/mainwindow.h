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
#include "sub_common/ActionCreate.h"
#include "sub_common/ActionUpdate.h"
#include "sub_common/ActionJoin.h"
#include "sub_common/ActionList.h"

#include "Button.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QWidget *parent, BlockingQueue<Action *> &updates, BlockingQueue<Action *> &actions);
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
    BlockingQueue<Action*> &updatesQueue;
    BlockingQueue<Action*> &actionsQueue;

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

    std::vector<std::string> parseList(std::string basicString);

    void drawLoadingScreen();
};
#endif // MAINWINDOW_H

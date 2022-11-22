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

#include "Button.h"
#include "sub_common/sub_action/ActionUpdate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(QWidget *parent, ProtectedQueue<Action *> &updates, BlockingQueue<Action *> &actions);
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
    ProtectedQueue<Action*> &updatesQueue;
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

    void popFirstUpdate();

    std::string retrieveGamaeName(std::string basicString);
};
#endif // MAINWINDOW_H

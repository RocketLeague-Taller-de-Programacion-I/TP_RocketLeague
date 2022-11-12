#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QString>

#include "gamescene.h"
#include "sub_common/BlockingQueue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QWidget *parent, BlockingQueue<std::string> &updates);
    ~MainWindow();

    void displayMainMenu();

public slots:
    void start();
    void back();
    void createGame();
    void joinGame();
    void joinParticularGame();
private:
    Ui::MainWindow *ui;
    GameScene scene;
    BlockingQueue<std::string> &updatesQueue;

    void drawGUI();

    void drawTitle(std::string title);

    void drawCreateButton();

    void drawJoinButton();

    void drawBackButton();

    void drawPlayButton();

    void drawCreateGameMenu();

    QLineEdit* lineEdit;
    QSpinBox* cantPlayers;
    QLabel *label;
    QString userName = QString("stranger");
};
#endif // MAINWINDOW_H

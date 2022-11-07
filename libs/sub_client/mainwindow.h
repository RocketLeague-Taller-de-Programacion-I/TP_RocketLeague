#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>

#include "gamescene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void displayMainMenu();

public slots:
    void start();
    void back();
    void createGame();
    void joinGame();
private:
    Ui::MainWindow *ui;

    GameScene scene;

    void drawGUI();

    void drawTitle(std::string title);

    void drawCreateButton();

    void drawJoinButton();

    void drawBackButton();

    void drawPlayButton();

    void drawCreateGameMenu();

    QLineEdit* lineEdit;
    QSpinBox* cantPlayers;
};
#endif // MAINWINDOW_H

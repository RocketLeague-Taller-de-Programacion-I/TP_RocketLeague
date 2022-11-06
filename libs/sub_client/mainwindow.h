#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    GameScene scene;

    void drawGUI();

    void drawTitle();

    void drawCreateButton();

    void drawJoinButton();

    void drawBackButton();
};
#endif // MAINWINDOW_H

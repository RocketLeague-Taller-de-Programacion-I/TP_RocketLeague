//
// Created by franco on 02/11/22.
//

#ifndef ROCKETLEAGUE_MAINWINDOW_H
#define ROCKETLEAGUE_MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);

    ~mainwindow() override;

private:
    Ui::mainwindow *ui;
};


#endif //ROCKETLEAGUE_MAINWINDOW_H

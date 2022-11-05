#ifndef GREETER_H
#define GREETER_H

#include <QWidget>

class MainWindow : public QWidget {
public:
    explicit MainWindow(QWidget *parent = 0);
private:
    void updateGreetings();
    void connectEvents();
};

#endif // GREETER_H

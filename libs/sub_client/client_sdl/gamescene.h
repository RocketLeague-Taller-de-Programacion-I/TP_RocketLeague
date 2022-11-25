#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
//#include "worm.h"



class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene();
    virtual ~GameScene() = default;

private slots:
	// Método polimorfico definido por QWidget. Por default no hace nada
	// pero yo quiero procesar eventos del teclado para mover a mi personaje
    void keyPressEvent(QKeyEvent *event) override;
    void start();
private:
//    Worm worm;

    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
};

#endif // GAMESCENE_H

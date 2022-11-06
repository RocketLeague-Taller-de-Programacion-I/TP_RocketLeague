#include "gamescene.h"
#include "Button.h"

GameScene::GameScene()
{
    setSceneRect(0,0,1500,750);
}
void GameScene::start() {

    // clear the screen
    clear();

    // place player 1 text
    QGraphicsTextItem* p1 = new QGraphicsTextItem("Player 1's Cards: ");
    p1->setPos(25,0);
    this->addItem(p1);
}


void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_D:
//            worm.moveRight();
            break;
        case Qt::Key_A:
//            worm.moveLeft();
            break;
        default:
            break;
    }
}

void GameScene::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    // draws a panel at the specified location with the specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    addItem(panel);
}
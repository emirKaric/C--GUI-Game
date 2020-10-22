#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Game.h"

class StartScreen: public QGraphicsView{
public:
    StartScreen(QWidget * parent=0);

    QGraphicsScene * scene;
    Game * game;


};

#endif // STARTSCREEN_H

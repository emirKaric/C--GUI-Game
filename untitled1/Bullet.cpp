#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Enemy.h"
#include "Game.h"

extern Game * game; // there is an external global object called game

Bullet::Bullet(int jedinicaPomijeranjaY, int brojRotacija, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    // draw graphics
    setPixmap(QPixmap(":/img/bullet.png"));


    // make/connect a timer to move() the bullet every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(50);
    this->jedinicaPomijeranjaY = jedinicaPomijeranjaY;
    this->brojRotacija = brojRotacija;
}

void Bullet::move(){
    // get a list of all the items currently colliding with this bullet
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // if one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Enemy)){
            // increase the score
            game->score->increase();

            // remove them from the scene (still on the heap)
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            // delete them from the heap to save memory
            delete colliding_items[i];
            delete this;

            // return (all code below refers to a non existint bullet)
            return;
        }
    }

    // if there was no collision with an Enemy, move the bullet forward
    switch (brojRotacija % 8) {
//        case 0: setPos(x(),y() - jedinicaPomijeranjaY); break;
//        case 1: setPos(x() - 10, y() - jedinicaPomijeranjaY); break;
//        case 2: setPos(x() - jedinicaPomijeranjaY, y()); break;
//        case 3: setPos(x() + 10, y() - jedinicaPomijeranjaY); break;
//        case 4: setPos(x(), y() + jedinicaPomijeranjaY); break;
//        case 5: setPos(x() + 10, y()  + jedinicaPomijeranjaY); break;
        case 6: setPos(x(), y() + jedinicaPomijeranjaY); break;
        case 7: setPos(x() - 10, y()  + jedinicaPomijeranjaY); break;
    }

    // if the bullet is off the screen, destroy it
    if (pos().y() < 0){
        scene()->removeItem(this);
        delete this;
    }else if (pos().y() > 600){
        scene()->removeItem(this);
        delete this;
    }
}

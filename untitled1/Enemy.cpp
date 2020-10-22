#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "Game.h"
#include "Player.h"
extern Game * game;

Enemy::Enemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    //set random x position
    int random_number = rand() % 600;
    setPos(random_number,0);

    // drew the rect
    setPixmap(QPixmap(":/img/enemy.png"));
    setTransformOriginPoint(50,50);
    setRotation(180);

    // make/connect a timer to move() the enemy every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(50);
    jedinicaPomijeranja = 5;
	
    //Explosion sound
    explosion= new QMediaPlayer();
    explosion->setMedia(QUrl("qrc:/sound/Explosion.mp3"));
}

void Enemy::move(){
    // get a list of all the items currently colliding with this bullet
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // if one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Player)){
            
	    // decreasing health
            game->health->decrease();
		
	    if(game->health->getHealth() <= 0)
                game->gameOver();
		
	    //play explosion sound
            if (explosion->state() == QMediaPlayer::PlayingState){
                explosion->setPosition(0);
            }
            else if (explosion->state() == QMediaPlayer::StoppedState){
                explosion->play();
            }

            // remove them from the scene (still on the heap)
            scene()->removeItem(this);

            // delete them from the heap to save memory
            delete this;

            // return (all code below refers to a non existint bullet)
            return;
        }
    }
    // move enemy down
    setPos(x(),y()+jedinicaPomijeranja);

    // destroy enemy when it goes out of the screen
    if (pos().y() > 600){
        //decrease the health
        jedinicaPomijeranja = -5;
    }
    else  if (pos().y() == 0){
        //decrease the health
        jedinicaPomijeranja = 5;
    }
}

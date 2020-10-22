#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Bullet.h"
#include "Enemy.h"
#include <QtMath>

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    // set bullet sound
    bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl("qrc:/sound/bullets.mp3"));

    // set graphic
    setPixmap(QPixmap(":/img/player.png"));
    this->brojRotacija = 0;
}

void Player::keyPressEvent(QKeyEvent *event){
    // move the player left and right
    if (event->key() == Qt::Key_Left){
        QTransform t = this->transform();

        t.translate(this->pixmap().width()/2, this->pixmap().height()/2);
        t.rotate(-45);
        t.translate(-this->pixmap().width()/2, -this->pixmap().height()/2);

        this->setTransform(t);
        brojRotacija--;
    }
    else if (event->key() == Qt::Key_Right){
        QTransform t = this->transform();

        t.translate(this->pixmap().width()/2, this->pixmap().height()/2);
        t.rotate(45);
        t.translate(-this->pixmap().width()/2, -this->pixmap().height()/2);

        this->setTransform(t);
        brojRotacija++;
    }
     // shoot with the keys up and down
    else if (event->key() == Qt::Key_Up){
        // create a bullet
        Bullet * bullet = new Bullet(10, brojRotacija);
        bullet->setPos(x()+45,y());
        QTransform t = bullet->transform();

        t.translate(bullet->pixmap().width()/2, bullet->pixmap().height()/2);
        t.rotate(brojRotacija * 45);
        t.translate(-bullet->pixmap().width()/2, -bullet->pixmap().height()/2);

        bullet->setTransform(t);
        scene()->addItem(bullet);

        // play bulletsound
        if (bulletsound->state() == QMediaPlayer::PlayingState){
            bulletsound->setPosition(0);
        }
        else if (bulletsound->state() == QMediaPlayer::StoppedState){
            bulletsound->play();
        }

    }else if (event->key() == Qt::Key_Down){
        // create a bullet
        Bullet * bullet = new Bullet(-10, brojRotacija);
        bullet->setPos(x()+45,y());
        QTransform t = bullet->transform();

        t.translate(bullet->pixmap().width()/2, bullet->pixmap().height()/2);
        t.rotate(brojRotacija * 45);
        t.translate(-bullet->pixmap().width()/2, -bullet->pixmap().height()/2);

        bullet->setTransform(t);
        scene()->addItem(bullet);

        // play bulletsound
        if (bulletsound->state() == QMediaPlayer::PlayingState){
            bulletsound->setPosition(0);
        }
        else if (bulletsound->state() == QMediaPlayer::StoppedState){
            bulletsound->play();
        }

    }
}

void Player::spawn(){
    // create an enemy
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
}

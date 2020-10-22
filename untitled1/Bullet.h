#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QMediaPlayer>

class Bullet: public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
    int jedinicaPomijeranjaY;
    int brojRotacija;
public:
    Bullet(int, int, QGraphicsItem * parent=0);
public slots:
    void move();
private:
    QMediaPlayer * explosion;
};

#endif // BULLET_H

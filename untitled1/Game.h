#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Player.h"
#include "Score.h"
#include "Health.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>

class Game: public QGraphicsView{
private:
    Q_OBJECT
public:
    Game(QWidget * parent=NULL);

    QSqlDatabase db;
    QGraphicsScene * scene;
    Player * player;
    Score * score;
    Health * health;
    QString nameOfPlayer;

    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void displayMainMenu();
    void gameOver(QString = "Game Over");
    void savePlayerToDatabase();
public slots:
    void start();
    void enterName();
    void printScores();
    void deleteAllScores();
    void deleteScores();
    void restartGame();
    void exit();
    void slotDisplayMenu();
    void saveAndBackToMenu();
};

#endif // GAME_H

#include "Game.h"
#include "Button.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "Enemy.h"
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>
#include <QDebug>
#include <QGraphicsSimpleTextItem>
#include "dialog.h"

Game::Game(QWidget *parent){
     setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,600);

    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,600); // make the scene 1024x600
    setBackgroundBrush(QBrush(QImage(":/img/bg.png")));
    setScene(scene);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Amina/Desktop/op-projektni/spaceship/database.sqlite");//treba promijeniti path kada se prebaci na drugi racunar
}

void Game::displayMainMenu(){
    // create the title text
        QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Star Wars"));
        QFont titleFont("comic sans",50);
        titleText->setFont(titleFont);
        int txPos = this->width()/2 - titleText->boundingRect().width()/2;
        int tyPos = 75;
        titleText->setPos(txPos,tyPos);
        scene->addItem(titleText);

        // create the play button
        Button* playButton = new Button(QString("Play"));
        int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
        int byPos = 200;
        playButton->setPos(bxPos,byPos);
        connect(playButton,SIGNAL(clicked()),this, SLOT(enterName()));
        scene->addItem(playButton);

        // create the list of scores button
        Button* scoresButton = new Button(QString("List of all scores"));
        int sxPos = this->width()/2 - scoresButton->boundingRect().width()/2;
        int syPos = 275;
        scoresButton->setPos(sxPos,syPos);
        connect(scoresButton,SIGNAL(clicked()),this,SLOT(printScores()));
        scene->addItem(scoresButton);

        // create the delete all scores button
        Button* dscoresButton = new Button(QString("Delete all scores"));
        int dsxPos = this->width()/2 - dscoresButton->boundingRect().width()/2;
        int dsyPos = 350;
        dscoresButton->setPos(dsxPos,dsyPos);
        connect(dscoresButton,SIGNAL(clicked()),this,SLOT(deleteAllScores()));
        scene->addItem(dscoresButton);

        // create the delete  score button
        Button* deletescoreButton = new Button(QString("Delete score"));
        int deletesxPos = this->width()/2 - deletescoreButton->boundingRect().width()/2;
        int deletesyPos = 425;
        deletescoreButton->setPos(deletesxPos,deletesyPos);
        connect(deletescoreButton,SIGNAL(clicked()),this,SLOT(deleteScores()));
        scene->addItem(deletescoreButton);

        // create the quit button
        Button* quitButton = new Button(QString("Quit"));
        int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
        int qyPos = 500;
        quitButton->setPos(qxPos,qyPos);
        connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
        scene->addItem(quitButton);
}

void Game::enterName(){
    Dialog dialog("Name:");
    dialog.exec();
    nameOfPlayer =  dialog.name == "" ? "Null" : dialog.name;
    start();
}

void Game::start(){
    // create the player
    scene->clear();
    player = new Player();
    player->setPos(width()*0.4,height()*0.5); //generalize to always be in the middle of screen

    // make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // add the player to the scene
    scene->addItem(player);

    // create the score/health
    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);

    QGraphicsTextItem* titleText = new QGraphicsTextItem("Player: " + nameOfPlayer);
    QFont titleFont("comic sans", 16);
    titleText->setFont(titleFont);
    titleText->setPos(titleText->x(),titleText->y() + 50);
    scene->addItem(titleText);

    // spawn enemies
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(2000);

    // play background music
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sound/bgsound.mp3"));
    music->play();
}

void Game::restartGame()
{
       scene->clear();
       start();
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity){

    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void Game::gameOver(QString textToDisplay){
    // disable all scene items
        for (size_t i = 0, n = scene->items().size(); i < n; i++){
            scene->items()[i]->setEnabled(false);
        }

        // pop up semi transparent panel
        drawPanel(0,0,1024,768,Qt::black,0.65);

        // draw panel
        drawPanel(312,184,400,400,Qt::lightGray,0.75);

        // create playAgain button
        Button* playAgain = new Button(QString("Play Again"));
        playAgain->setPos(410,300);
        scene->addItem(playAgain);
        connect(playAgain,SIGNAL(clicked()),this,SLOT(restartGame()));

        // create quit button
        Button* backToMainMenu = new Button(QString("Back to main menu"));
        backToMainMenu->setPos(410,375);
        scene->addItem(backToMainMenu);
        connect(backToMainMenu,SIGNAL(clicked()),this,SLOT(saveAndBackToMenu()));

        // create quit button
        Button* quit = new Button(QString("Quit"));
        quit->setPos(410,450);
        scene->addItem(quit);
        connect(quit,SIGNAL(clicked()),this,SLOT(exit()));

        QGraphicsTextItem* overText = new QGraphicsTextItem(textToDisplay);
        overText->setPos(460,225);
        scene->addItem(overText);
}

void Game::saveAndBackToMenu(){
    savePlayerToDatabase();
    scene->clear();
    displayMainMenu();
}

void Game::exit(){
    savePlayerToDatabase();
    close();
}
void Game::savePlayerToDatabase(){
    db.open();
    QSqlQuery q;
    q.prepare("INSERT INTO Player ("
           "Username,"
           "Score)"
           "VALUES (?,?);");


    q.addBindValue(nameOfPlayer);
    q.addBindValue(score->getScore());

    if(!q.exec())
        qDebug() << "Nije dodalo";

    q.clear();
    db.close();
}
void Game::printScores()
{
    // clear a scene
    scene->clear();
    // create back button
    Button* back = new Button(QString("Back"));
    back->setPos(0,0);
    scene->addItem(back);
    connect(back,SIGNAL(clicked()),this,SLOT(slotDisplayMenu()));
    db.open();
    QString data = "";
    QSqlQuery q;
    q.exec("SELECT * FROM Player");

    while(q.next()){
        data += q.value(0).toString() + ". ";
        data += q.value(1).toString() + "  ";
        data += q.value(2).toString() + "\n";

    }

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Scores\n"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 50;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    QGraphicsTextItem* titleText1 = new QGraphicsTextItem(data);
    QFont titleFont1("comic sans", 20);
    titleText1->setFont(titleFont1);
    int txPos1 = this->width()/2 - titleText1->boundingRect().width()/2;
    int tyPos1 = 150;
    titleText1->setPos(txPos1,tyPos1);
    scene->addItem(titleText1);


    q.clear();
    db.close();
}
void Game::slotDisplayMenu(){
    scene->clear();
    displayMainMenu();
}
void Game::deleteAllScores()
{
    db.open();
    QSqlQuery q;
    q.exec("DELETE FROM Player");
    q.clear();
    db.close();
}
void Game::deleteScores()
{
    db.open();
    Dialog dialog("Index za brisanje: ");
    dialog.exec();
    nameOfPlayer =  dialog.name == "" ? "-1" : dialog.name;
    QSqlQuery q;
    q.exec("DELETE FROM Player WHERE ID=" + nameOfPlayer);
    q.clear();
    db.close();
}

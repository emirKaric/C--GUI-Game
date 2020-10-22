#include "dialog.h"
#include "ui_dialog.h"
#include "Game.h"

extern Game* game;

Dialog::Dialog(QString name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label->setText(name);

    connect(ui->ok,SIGNAL(clicked()),this,SLOT(pohrani()));
    connect(ui->close,SIGNAL(clicked()),this ,SLOT(close()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::pohrani(){
    name = ui->lineEdit->text();
    ui->close->clicked();
}

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QString,QWidget *parent = nullptr);
    ~Dialog();
    QString name;
public slots:
    void pohrani();
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H

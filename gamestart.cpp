#include "gamestart.h"
#include "ui_gamestart.h"
#include "mainwindow.h"
#include <QPushButton>
GameStart::GameStart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameStart)
{
    ui->setupUi(this);
    setWindowTitle("Defense Tower Game");
    setFixedSize(1040, 640);
    QPushButton* b;
    b=new QPushButton(this);
    b->setText("Level 1");
    b->setFixedSize(100,60);
    b->move(210,320);
    connect(b,&QPushButton::clicked,[=]()
    {
        MainWindow *mainwindow = new MainWindow();
        mainwindow->show();
    });
}

GameStart::~GameStart()
{
    delete ui;
}

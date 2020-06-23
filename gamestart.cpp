#include "gamestart.h"
#include "ui_gamestart.h"
#include "mainwindow.h"
#include <QPushButton>
GameStart::GameStart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameStart)
{
    ui->setupUi(this);
    //设置主页信息
    setWindowTitle("Defense Tower Game");
    setFixedSize(1040, 640);
    //设置按钮
    QPushButton* b1;
    QPushButton* b2;
    b1=new QPushButton(this);
    b1->setText("Level 1");
    b1->setFixedSize(100,60);
    b1->move(210,320);
    b2=new QPushButton(this);
    b2->setText("Level 2");
    b2->setFixedSize(100,60);
    b2->move(730,320);
    //转到槽
    connect(b1,&QPushButton::clicked,[=]()
    {
        MainWindow *mainwindow = new MainWindow(1);
        mainwindow->SetLabel();
        mainwindow->show();
    });
    connect(b2,&QPushButton::clicked,[=]()
    {
        MainWindow *mainwindow = new MainWindow(2);
        mainwindow->show();
    });
}




GameStart::~GameStart()
{
    delete ui;
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>
#include "enemy.h"
#include "towerposition.h"
#include "towerbase.h"
#include "optionbutton.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int level);
    void InsertEnemy(QPoint**, int, QPoint*,int typenumber);//向敌人数组中插入敌人
    void DrawEnemy(QPainter&); //绘制敌人
    void DrawMap(QPainter&);//绘制地图
    void DrawOptionButton(QPainter&);
    void DrawTower(QPainter&);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    ~MainWindow();
 private:
    int Level;//关卡数
    int money=500;//初始金钱数设为500，用于购买塔
    int life=10;//初始生命值为10，生命值降为0游戏结束
    QPoint* homepoint = new QPoint(0,0);//家坐标 用于判断敌人抵达
    QVector<Enemy*> EnemyVec;//存敌人的数组
    QVector<TowerPosition*> TowerPositionVec;//存放可放置塔的位置数组
    QVector<TowerBase*> TowerBaseVec; //存塔的数组
    OptionButton* buttons[2]={new OptionButton(":/image/BuyFireBottle.png"),new OptionButton(":/image/BuyGreenBottle.png")};
};

#endif // MAINWINDOW_H

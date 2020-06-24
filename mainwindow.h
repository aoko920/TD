#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QTimer>
#include "enemy.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int level);
    void InsertEnemy(QPoint**, int, QPoint*,int typenumber);//向敌人数组中插入敌人
    /*void Enemywayplan(QPoint**, QPoint**, int*);//地图1设置一条路径方案 参数依次为：路径拐点数组 起点坐标数组 拐点数
    void Enemywayplan(QPoint**, QPoint**, QPoint**, int*);//重载函数 地图2设置两条路径方案 参数依次为：路径拐点数组1 路径拐点数组2 起点坐标数组 拐点数数组*/
    void DrawEnemy(QPainter&);            //画出怪物
    void SetLabel();//绘制金钱和生命值标签
    void DrawMap(QPainter&);//绘制地图
    void paintEvent(QPaintEvent *);
    ~MainWindow();
 private:
    int Level;//关卡数
    int money=500;//初始金钱数设为500，用于购买塔
    int life=10;//初始生命值为10，生命值降为0游戏结束
    QPoint* homepoint = new QPoint(0,0);//家坐标 用于判断敌人抵达
    QVector<Enemy*> EnemyVec;//存敌人的数组
};

#endif // MAINWINDOW_H

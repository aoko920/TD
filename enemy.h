#ifndef ENEMY_H
#define ENEMY_H

#include <QVector>
#include <QString>
#include <QPoint>

class Enemy
{
public:
    //参数：存放路径点的数组，路径点个数，敌人初始坐标，敌人编号
    Enemy(QPoint **WayPoints, int pointsum, int startx, int starty, int typenum);
    bool Move();//敌人移动转弯，判断到达终点扣减生命值
    int GetX() const;
    int GetY() const;
    QString LoadImage();//载入图片
    int GetLife();
    void SetLife(int);
    int GetWorth();
private:
    QVector<QPoint*> EnemyWay;//敌人路径数组
    int EnemyX, EnemyY;//敌人坐标
    int type;//敌人种类
    QString Image;//图片
    int life;
    int worth;

};

#endif // ENEMY_H

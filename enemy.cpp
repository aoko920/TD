#include "enemy.h"

Enemy::Enemy(QPoint **WayPoints, int pointsum, int startx, int starty, int typenum)
{
    //存路线坐标
    for(int i = 0; i < pointsum; i++)
    {
        EnemyWay.push_back(WayPoints[i]);
    }
    //设置敌人基础信息
    EnemyX = startx;
    EnemyY = starty;
    type = typenum;
    switch (typenum)
    {
    case 1:
        Image = ":/image/monster1.png";
        break;
    case 2:
        Image = ":/image/Shark.png";
        break;
    default:
        break;
    }
}

bool Enemy::Move()
{
    //通过判断敌人现处坐标和路径拐点坐标比较 加减现处坐标来实现敌人移动
    if(EnemyWay.at(0)->y() > EnemyY)
    {//下移
        EnemyY += 10;
        return false;
    }
    if(EnemyWay.at(0)->y() < EnemyY)
    {//上移
        EnemyY -= 10;
        return false;
    }
    if(EnemyWay.at(0)->x() < EnemyX)
    {//左移
        EnemyX -= 10;
        return false;
    }
    if(EnemyWay.at(0)->x() > EnemyX)
    {//右移
        EnemyX += 10;
        return false;
    }
    //每到达一个拐点就删除它
    if(EnemyWay.at(0)->x() == EnemyX && EnemyWay.at(0)->y() == EnemyY)
    {
        delete EnemyWay.begin();
        EnemyWay.erase(EnemyWay.begin());
    }
    //等所有路径点都被删除 则说明已到达家位置 返回抵达信号
    if(EnemyWay.empty())
    {
        return true;
    }
    return false;
}

int Enemy::GetX() const
{
    return EnemyX;
}

int Enemy::GetY() const
{
    return EnemyY;
}

QString Enemy::LoadImage()
{
    return Image;
}

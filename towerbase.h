#ifndef TOWERBASE_H
#define TOWERBASE_H

#include <QString>
#include "enemy.h"
#include "bullet.h"

class TowerBase
{
public:
    int GetX();
    int GetY();
    int GetcpX();
    int GetcpY();
    QString GetImage();
    bool show = true;
    bool hasaim = false;//判断有无目标
    void SetTarget(Enemy*);
    Enemy* GetTarget();
    int GetAttackRange();
    int GetRotation();
    void SetRotation(int);
    QVector<Bullet*> BulletVec;
    void InterBullet();
    void BulletMove();
    QVector<Bullet*>& GetBulletVec();
protected:
    int TowerX;//将图片调整到合适位置的坐标
    int TowerY;
    int cpx;//中心点坐标
    int cpy;
    int attackrange;
    int rotation = 0;
    QString Image;
    Enemy* target = NULL;//敌人目标
    int startpos = 0;

};

#endif // TOWERBASE_H

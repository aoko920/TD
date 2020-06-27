#ifndef TOWERBASE_H
#define TOWERBASE_H

#include <QString>
#include "enemy.h"

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
protected:
    int TowerX;//将图片调整到合适位置的坐标
    int TowerY;
    int cpx;//中心点坐标
    int cpy;
    int attackrange;
    int rotation = 0;
    QString Image;
    Enemy* target = NULL;//敌人目标

};

#endif // TOWERBASE_H

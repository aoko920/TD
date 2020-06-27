#ifndef FIRETOWER_H
#define FIRETOWER_H

#include "towerbase.h"
//花钱多 威力大 攻击范围小
class FireTower:public TowerBase
{
public:
    FireTower(int x,int y,int _cpx,int _cpy);
};

#endif // FIRETOWER_H

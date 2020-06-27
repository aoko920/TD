#ifndef WOODTOWER_H
#define WOODTOWER_H

#include "towerbase.h"
//花钱少 威力小 攻击范围广
class WoodTower:public TowerBase
{
public:
    WoodTower(int x,int y,int _cpx,int _cpy);
};

#endif // WOODTOWER_H

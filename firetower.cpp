#include "firetower.h"

FireTower::FireTower(int x,int y,int _cpx,int _cpy)
{
    TowerX = x;
    TowerY = y;
    cpx = _cpx;
    cpy = _cpy;
    Image = QString(":/image/FireBottle.png");
    attackrange = 150;
}

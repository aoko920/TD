#include "towerbase.h"

int TowerBase::GetX()
{
    return TowerX;
}

int TowerBase::GetY()
{
    return TowerY;
}

int TowerBase::GetcpX()
{
    return cpx;
}

int TowerBase::GetcpY()
{
    return cpy;
}

QString TowerBase::GetImage()
{
    return Image;
}

Enemy* TowerBase::GetTarget()
{
    return target;
}

void TowerBase::SetTarget(Enemy* _target)
{
    target = _target;
}

int TowerBase::GetAttackRange()
{
    return attackrange;
}

int TowerBase::GetRotation()
{
    return rotation;
}

void TowerBase::SetRotation(int _rotation)
{
    rotation = _rotation;
}

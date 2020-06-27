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

void TowerBase::InterBullet()
{

    if(hasaim)
    {
        if(target->GetX() < cpx)//向左发射子弹
        {
            BulletVec.push_back(new Bullet(cpx,cpy,-1));
        }
        else//向右发射子弹
        {
            BulletVec.push_back(new Bullet(cpx,cpy,1));
        }
    }
}

void TowerBase::BulletMove()
{
    for(auto bullet : BulletVec)
    {
        if(bullet->GetLD() == -1 && cpx!=target->GetX())
        {
            bullet->SetX(bullet->GetX()-22);
            bullet->SetY((target->GetY()-cpy)/(target->GetX()-cpx)*bullet->GetX()+target->GetY()-(target->GetY()-cpy)/(target->GetX()-cpx)*target->GetX());
        }
        if(bullet->GetLD() == 1 && cpx!=target->GetX())
        {
            bullet->SetX(bullet->GetX()+22);
            bullet->SetY((target->GetY()-cpy)/(target->GetX()-cpx)*bullet->GetX()+target->GetY()-(target->GetY()-cpy)/(target->GetX()-cpx)*target->GetX());
        }
    }
    for(auto bullet = BulletVec.begin(); bullet != BulletVec.end(); bullet++)
    {//如果子弹超过了攻击范围 就删除它
        if((*bullet)->GetX() > cpx+attackrange || (*bullet)->GetX() < cpx-attackrange || (*bullet)->GetY() > cpy+attackrange || (*bullet)->GetY() < cpy-attackrange)
        {
            BulletVec.erase(bullet);
            break;
        }
    }
}

QVector<Bullet*>& TowerBase::GetBulletVec()
{
    return BulletVec;
}

int TowerBase::GetAttackPower()
{
    return attackpower;
}


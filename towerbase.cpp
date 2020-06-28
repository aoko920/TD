#include "towerbase.h"

int TowerBase::GetX() const
{
    return TowerX;
}

int TowerBase::GetY() const
{
    return TowerY;
}

int TowerBase::GetcpX() const
{
    return cpx;
}

int TowerBase::GetcpY() const
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
    startpos++;
    if(startpos<=5||!hasaim)
    {
        return;
    }
    Bullet* bull = new Bullet(cpx,cpy);
    if(cpx == target->GetX())
    {
        delete bull;
        startpos = 0;
        return ;
    }


            if(target->GetX() < cpx)//向左发射子弹
            {
                bull->SetLD(-1);
                bull->k=(target->GetY()-cpy)/(target->GetX()-cpx);
                bull->b=target->GetY()-bull->k*target->GetX();
                BulletVec.push_back(bull);
            }
            else//向右发射子弹
            {
                bull->SetLD(1);
                bull->k=(target->GetY()-cpy)/(target->GetX()-cpx);
                bull->b=target->GetY()-bull->k*target->GetX();
                BulletVec.push_back(bull);
            }
            startpos=0;
}

void TowerBase::BulletMove()
{
    if(hasaim)
    {
        for(auto bullet : BulletVec)
        {
            if(bullet->GetLD() == -1 )
            {
                bullet->SetX(bullet->GetX()-24);
                bullet->SetY(bullet->k*bullet->GetX()+bullet->b);
            }
            if(bullet->GetLD() == 1 )
            {
                bullet->SetX(bullet->GetX()+24);
                bullet->SetY(bullet->k*bullet->GetX()+bullet->b);
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
    else
    {
        return ;
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

int TowerBase::GetCost()
{
    return cost;
}

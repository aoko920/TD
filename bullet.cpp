#include "bullet.h"

Bullet::Bullet(int _x,int _y/*,int _ld,int _k,int _b*/)
{
    x = _x;
    y = _y;
    /*ld = _ld;
    k=_k;
    b=_b;*/
}

int Bullet::GetX()
{
    return x;
}

int Bullet::GetY()
{
    return y;
}

void Bullet::SetX(int _x)
{
    x = _x;
}

void Bullet::SetY(int _y)
{
    y = _y;
}

QString Bullet::GetImage()
{
    return Image;
}

void Bullet::SetLD(int _ld)
{
    ld=_ld;
}
int Bullet::GetLD()
{
    return ld;
}

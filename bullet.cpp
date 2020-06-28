#include "bullet.h"

Bullet::Bullet(int _x,int _y)
{
    x = _x;
    y = _y;
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

#include "bullet.h"

Bullet::Bullet(int _x,int _y,int _ld)
{
    x = _x;
    y = _y;
    ld = _ld;
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

int Bullet::GetLD()
{
    return ld;
}

#ifndef BULLET_H
#define BULLET_H

#include<QString>

class Bullet
{
public:
    Bullet(int _x,int _y,int _ld);
    int GetX();
    int GetY();
    void SetX(int);
    void SetY(int);
    int GetLD();
    QString GetImage();
private:
    int x;
    int y;
    int ld;//Lauching Direction -1为左 1为右
    QString Image = QString(":/image/Shells1.png");
};

#endif // BULLET_H

#ifndef TOWERBASE_H
#define TOWERBASE_H

#include <QString>

class TowerBase
{
public:
    int GetX();
    int GetY();
    int GetcpX();
    int GetcpY();
    QString GetImage();
    bool show = true;
protected:
    int TowerX;//将图片调整到合适位置的坐标
    int TowerY;
    int cpx;//中心点坐标
    int cpy;
    QString Image;

};

#endif // TOWERBASE_H

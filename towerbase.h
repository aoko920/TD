#ifndef TOWERBASE_H
#define TOWERBASE_H

#include <QString>

class TowerBase
{
public:
    TowerBase();
    int GetX();
    int GetY();
    QString GetImage();
protected:
    int TowerX;
    int TowerY;
    QString Image;

};

#endif // TOWERBASE_H

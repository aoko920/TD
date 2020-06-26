#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

//用来存储所有可放置塔的位置
class TowerPosition
{
public:
    TowerPosition(int _x, int _y);
    int GetX();
    int GetY();
private:
    int x;
    int y;
};

#endif // TOWERPOSITION_H

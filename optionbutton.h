#ifndef OPTIONBUTTON_H
#define OPTIONBUTTON_H

#include <QString>
class OptionButton
{
public://重载构造函数
    OptionButton(int _x,int _y);
    OptionButton(QString image);
    int GetX();
    int GetY();
    QString GetImage();
    int x;
    int y;
    QString Image;
    bool show = false;
};

#endif // OPTIONBUTTON_H

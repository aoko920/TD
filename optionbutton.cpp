#include "optionbutton.h"

OptionButton::OptionButton(int _x,int _y)
{
    x=_x;
    y=_y;
}

OptionButton::OptionButton(QString image)
{
    Image=image;
}

int OptionButton::GetX()
{
    return x;
}

int OptionButton::GetY()
{
    return y;
}

QString OptionButton::GetImage()
{
    return Image;
}

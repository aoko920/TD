#ifndef GAMESTART_H
#define GAMESTART_H

#include <QWidget>

namespace Ui {
class GameStart;
}

class GameStart : public QWidget
{
    Q_OBJECT

public:
    explicit GameStart(QWidget *parent = nullptr);
    ~GameStart();

private:
    Ui::GameStart *ui;
};

#endif // GAMESTART_H

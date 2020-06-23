#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QLabel>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int level);
    void SetLabel();//绘制金钱和生命值标签
    void DrawMap(QPainter&);//绘制地图
    void paintEvent(QPaintEvent *);
    ~MainWindow();
 private:
    int Level;//关卡数
    int money=500;//初始金钱数设为500，用于购买塔
    int life=10;//初始生命值为10，生命值降为0游戏结束
};

#endif // MAINWINDOW_H

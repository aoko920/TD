#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void paintEvent(QPaintEvent *);
    void DrawMap(QPainter&);
    explicit MainWindow(int level);
    ~MainWindow();
 private:
    int Level;
};

#endif // MAINWINDOW_H

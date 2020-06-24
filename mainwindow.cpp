#include "mainwindow.h"
#include <QDebug>
//插入怪物  路径点数组名、怪物初始坐标、怪物编号

MainWindow::MainWindow(int level)
{
    //储存关卡
    Level=level;
    //设置窗口信息
    setFixedSize(1040, 640);
    setWindowTitle("Game Start");
    //插入敌人的定时器
    QTimer* timer = new QTimer(this);
    timer->start(2000);//设置每2秒更新一次
    connect(timer,&QTimer::timeout,[=]()
        {

            switch (Level)
            {
            case 1:
            {
                //路径拐点数组
                QPoint* Waypoints1[6] = {new QPoint(280 , 200), new QPoint(280 , 320), new QPoint(520 , 320), new QPoint(520 , 160), new QPoint(720 , 160), new QPoint(homepoint->x(),homepoint->y())};
                //起始点数组
                QPoint* startpoints = new QPoint(-40, 200);
                //拐点个数数组
                int sum = 6;
                //路径数组 拐点总数 开始点 类型
                InsertEnemy( Waypoints1,sum,startpoints, 1);
                update();
                break;
            }
            case 2:
            {
                //路径拐点数组
                QPoint* Waypoints1[] = {new QPoint(120 , 280), new QPoint(760 , 280), new QPoint(760 , 480), new QPoint(200 , 480), new QPoint(homepoint->x(),homepoint->y())};
                //起始点数组
                QPoint* startpoints = new QPoint(120 , -40);
                //拐点个数数组
                int sum = 5;
                //路线1，路线2，开始点数组，拐点数
                InsertEnemy( Waypoints1,sum,startpoints, 2);
                update();
                break;
            }
            }
        });
    QTimer* timer2 = new QTimer(this);
    timer2->start(120);
    connect(timer2,&QTimer::timeout,[=]()
    {
        for (auto Moni = EnemyVec.begin(); Moni != EnemyVec.end(); Moni++)
            if((*Moni)->Move()) //怪物走到终点
            {
                delete *Moni;
                EnemyVec.erase(Moni);         //怪物走到终点则删除这个怪物

                life--;                         //我们的生命数量-1


                if (life <= 0) this->close();   //生命值为0时关闭该窗口

                break;
            };
        update();
    });
}

void MainWindow::InsertEnemy(QPoint** Waypoints1, int sum, QPoint* startpoints,int typenumber)
{
    EnemyVec.push_back(new Enemy(Waypoints1,sum,startpoints->x(),startpoints->y(),typenumber));
}



void MainWindow::DrawEnemy(QPainter& painter)
{
    for (auto moni : EnemyVec)//画出怪物
        painter.drawPixmap(moni->GetX(), moni->GetY(), 64, 64, QPixmap(moni->LoadImage()));
}


//标签
void MainWindow::SetLabel()
{
    //绘制金钱
    QLabel *Money = new QLabel(this);
    Money->move(20,20);
    Money->resize(160,40);
    Money->setFont(QFont("Times",12,QFont::Black));
    Money->setText(QString("Money：%1").arg(money));
    //绘制生命值
    QLabel *Life = new QLabel(this);
    Life->move(20,60);
    Life->resize(160,40);
    Life->setFont(QFont("Times",12,QFont::Black));
    Life->setText(QString("Life：%1").arg(life));
}

//地图
void MainWindow::DrawMap(QPainter& painter)
{
    //level 1
    int Map_1[16][26] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 3, 6, 0, 1, 1, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 3, 6, 1, 1, 0, 0, 6, 6, 0, 1, 1, 0, 6, 6, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 0, 0, 3, 6, 0, 0, 0, 0, 1, 1, 3, 6, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 6, 6, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
    };
    //level 2
    int Map_2[16][26] =
    {
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 3, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 6, 6, 1, 1, 0, 0, 3, 6, 0, 0, 0, 0, 0, 3, 6, 0, 0, 3, 6, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 0, 0, 6, 6, 0, 0, 0, 0, 0, 6, 6, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 6, 0, 0, 0, 0, 3, 6, 0, 0, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 6, 6, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 5, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    int Map[16][26];
    if(Level==1)
    {
        memcpy(Map, Map_1, sizeof(Map));
    }
    else {
        memcpy(Map, Map_2, sizeof(Map));
    }
    for (int j = 0; j < 16; j++)
        for (int i = 0; i < 26; i++)
        {
            //根据地图对应坐标值放置图片
            switch (Map[j][i])
            {
            case 0:
                painter.drawPixmap(i * 40, j * 40, 40, 40, QPixmap(":/image/GrassBlock.png"));
                break;
            case 1:
                painter.drawPixmap(i * 40, j * 40, 40, 40, QPixmap(":/image/GroundBlock.png"));
                break;
            case 3:
                painter.drawPixmap(i * 40, j * 40, 80, 80, QPixmap(":/image/StoneBrick.png"));
                break;
            case 5:
                painter.drawPixmap(i * 40, j * 40, 40, 40, QPixmap(":/image/GroundBlock.png"));
                homepoint->setX( i * 40 );
                homepoint->setY( j * 40 );//放置家图片时储存家坐标
                break;
            }
        }
    painter.drawPixmap(homepoint->x(),homepoint->y(), 80, 80, QPixmap(":/image/home.png"));
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    DrawMap(painter);
    DrawEnemy(painter);
}

MainWindow::~MainWindow()
{
}

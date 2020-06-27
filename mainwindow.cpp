#include "mainwindow.h"
#include "firetower.h"
#include "woodtower.h"
#include <QDebug>
#include <cmath>
//插入怪物  路径点数组名、怪物初始坐标、怪物编号

MainWindow::MainWindow(int level)
{
    //储存关卡
    Level=level;
    //设置窗口信息
    setFixedSize(1040, 640);
    setWindowTitle("Game Start");


    //设置标签
    //绘制金钱
    Money->move(860,20);
    Money->resize(160,40);
    Money->setFont(QFont("Times",12,QFont::Black));
    Money->setText(QString("Money：%1").arg(money));
    //绘制生命值
    Life->move(860,60);
    Life->resize(160,40);
    Life->setFont(QFont("Times",12,QFont::Black));
    Life->setText(QString("Life：%1").arg(life));


    //插入敌人的定时器
    QTimer* subtimer = new QTimer(this);
    subtimer->start(2000);//设置每2秒更新一次
    connect(subtimer,&QTimer::timeout,[=]()
        {

            switch (Level)
            {
            case 1:
            {
                //路径拐点数组
                QPoint* Waypoints1[6] = {new QPoint(240 , 200), new QPoint(240 , 320), new QPoint(520 , 320), new QPoint(520 , 160), new QPoint(720 , 160), new QPoint(homepoint->x(),homepoint->y())};
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
    QTimer* maintimer = new QTimer(this);
    maintimer->start(120);
    connect(maintimer,&QTimer::timeout,[=]()
    {
        //到家后删除敌人 生命值减1 刷新标签 生命值为0时关闭窗口
        for (auto Moni = EnemyVec.begin(); Moni != EnemyVec.end(); Moni++)
        {
            if((*Moni)->Move()) //到达家的时候该函数return true
            {
                delete *Moni;
                EnemyVec.erase(Moni);
                life--;
                Life->setText(QString("Life：%1").arg(life));
                if (life <= 0) this->close();
                break;
            };
        }

        //塔获得目标
        for (auto tower : TowerBaseVec)
        {
            if(!tower->hasaim)
            {//从最新插入的敌人开始判断是否在攻击范围之内 在就设为目标
                for(int i = EnemyVec.size()-1;i >= 0;i--)
                {
                    if(sqrt((tower->GetcpX()-EnemyVec.at(i)->GetX()-32)*(tower->GetcpX()-EnemyVec.at(i)->GetX()-32)+(tower->GetcpY()-EnemyVec.at(i)->GetY()-32)*(tower->GetcpY()-EnemyVec.at(i)->GetY()-32)) <= tower->GetAttackRange())
                    {
                        tower->SetTarget(EnemyVec.at(i));
                        tower->hasaim = true;
                        break;
                    }
                }
            }
            else
            {//有目标就设置旋转角度 达到炮塔随目标旋转的效果
                if(sqrt((tower->GetcpX()-tower->GetTarget()->GetX()-32)*(tower->GetcpX()-tower->GetTarget()->GetX()-32)+(tower->GetcpY()-tower->GetTarget()->GetY()-32)*(tower->GetcpY()-tower->GetTarget()->GetY()-32)) <= tower->GetAttackRange())
                {//用反三角函数求旋转角
                    tower->SetRotation(atan2(tower->GetTarget()->GetY()-tower->GetcpY(),tower->GetTarget()->GetX()-tower->GetcpX())*180/3.1415);
                    tower->InterBullet();
                }
            }

            if(tower->hasaim)
            {//当现有目标超出攻击范围 就删除它
                if(sqrt((tower->GetcpX()-tower->GetTarget()->GetX()-32)*(tower->GetcpX()-tower->GetTarget()->GetX()-32)+(tower->GetcpY()-tower->GetTarget()->GetY()-32)*(tower->GetcpY()-tower->GetTarget()->GetY()-32)) > tower->GetAttackRange())
                {
                    tower->SetTarget(NULL);
                    tower->hasaim = false;
                }
            }
        }

        for(auto tower : TowerBaseVec)
        {
            tower->BulletMove();
        }

        update();
    });
}


void MainWindow::InsertEnemy(QPoint** Waypoints1, int sum, QPoint* startpoints,int typenumber)
{
    EnemyVec.push_back(new Enemy(Waypoints1,sum,startpoints->x(),startpoints->y(),typenumber));
}


void MainWindow::DrawEnemy(QPainter& painter)
{
    for (auto moni : EnemyVec)
        painter.drawPixmap(moni->GetX(), moni->GetY(), 64, 64, QPixmap(moni->LoadImage()));
}


void MainWindow::DrawOptionButton(QPainter & painter)
{
    if(buttons[0]->show&&buttons[1]->show)//确认显示选择键
    for(int i = 0;i <= 1;i ++)
    {
        painter.drawPixmap(buttons[i]->GetX(),buttons[i]->GetY(),56,56,QPixmap(buttons[i]->GetImage()));
    }
}

void MainWindow::DrawTower(QPainter & painter)
{
    for(auto tower : TowerBaseVec)
    {
        if(tower->show == true)
        {
            for (auto bullet : tower->GetBulletVec())
            {
                painter.drawPixmap(bullet->GetX(),bullet->GetY(), 20, 20,QPixmap(bullet->GetImage()));
            }
            painter.translate(tower->GetcpX(),tower->GetcpY());
            painter.rotate(tower->GetRotation());
            painter.translate(-tower->GetcpX(),-tower->GetcpY());
            painter.drawPixmap(tower->GetX(),tower->GetY(),72,46,QPixmap(tower->GetImage()));
            painter.resetTransform();
        }
    }
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
                TowerPositionVec.push_back(new TowerPosition(i * 40,j * 40));//顺便存入可放塔的坐标数组
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
    DrawOptionButton(painter);
    DrawTower(painter);

}


void MainWindow::mousePressEvent(QMouseEvent *click)
{
    //点击左键 放置塔的位置 显示两个塔选择键
    if(click->button() == Qt::LeftButton)
    {
        for(auto p : TowerPositionVec)
        {
            if(click->x() >= p->GetX() && click->x() <= p->GetX()+80 && click->y() >= p->GetY() && click->y() <= p->GetY()+80)//判断点击点落在可放塔的区域内
            {
                buttons[0]->show = true;
                buttons[1]->show = true;
                buttons[0]->x = p->GetX()-56;
                buttons[0]->y = p->GetY()-28;
                buttons[1]->x = p->GetX()-56;
                buttons[1]->y = p->GetY()+52;
                update();

            }


        }

        //点击选择键 放塔
        for(int i = 0;i <= 1;i ++)
        {
            //隐藏选择键
            if(click->x() >= buttons[i]->GetX() && click->x() <= buttons[i]->GetX()+56 && click->y() >= buttons[i]->GetY() && click->y() <= buttons[i]->GetY()+56)//判断点击点落在选择键内
            {
                if(i == 0)
                {
                    if(EnoughMoney(160))
                    {
                        buttons[i]->show = false;
                        TowerBaseVec.push_back(new FireTower(buttons[i]->x+76,buttons[i]->y+48,buttons[i]->GetX()+96,buttons[i]->GetY()+68));
                    }
                }
                else
                {
                    if(EnoughMoney(100))
                    {
                        buttons[i]->show = false;
                        TowerBaseVec.push_back(new WoodTower(buttons[i]->x+76,buttons[i]->y-32,buttons[i]->GetX()+96,buttons[i]->GetY()-12));
                    }
                }
                update();

            }
        }
    }
    //点击右键 删除塔
    if(click->button() == Qt::RightButton)
    {
        for(auto &t : TowerBaseVec)
        {
            if(click->x() >= t->GetX()-40 && click->x() <= t->GetX()+40 && click->y() >= t->GetY()-40 && click->y() <= t->GetY()+40)
            {
               // t->show = false;
                TowerBaseVec.erase(&t);
            }
        }
    }


    update();
}


//判断钱是否够买塔
bool MainWindow::EnoughMoney(int cost)
{
    if(money >= cost)
    {
        money = money - cost;
        Money->setText(QString("Money：%1").arg(money));
        return true;
    }
    else
    {
        return false;
    }
}


MainWindow::~MainWindow()
{
}

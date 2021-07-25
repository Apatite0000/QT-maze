#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(960,640);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setWindowIcon(QIcon("title.png"));
    this->setWindowTitle("老鼠找粮仓");
    srand(_getpid());
    for(int i=0;i<=20;i++)
    {
        for(int j=0; j!=20; j++)
                    maze.all_to_0();
    }

    win_flag = false;

    game_mode = 0;

    is_find_way_painted = false;

    set_win_time = 120;
    win_time = set_win_time;


    QFont font_1( "汉仪铸字木头人W", 25, 60);
    QFont font_2( "黑体", 10, 10);
    //font.setPointSize("汉仪铸字木头人w",20,75);

    title = new QLabel(this);
    title->setFocusPolicy(Qt::NoFocus);
    title->setGeometry(810,50,200,40);
    title->setText("老鼠找粮仓");
    title->setFont(font_1);


    state = new QLabel(this);
    state->setFocusPolicy(Qt::NoFocus);
    state->setGeometry(810,100,200,20);
    state->setText("当前状态：暂停");
    state->setFont(font_2);

    time_log = new QLCDNumber(this);
    time_log->setFocusPolicy(Qt::NoFocus);
    time_log->setGeometry(810,140,100,40);
    time_log->setDigitCount(5);
    time_log->display("00:00");

    begin = new QPushButton(this);
    begin->setFocusPolicy(Qt::NoFocus);
    begin->setGeometry(810,200,100,20);
    begin->setText("开始新游戏");
    begin->setFont(font_2);

    alter = new QPushButton(this);
    alter->setFocusPolicy(Qt::NoFocus);
    alter->setGeometry(810,225,100,20);
    alter->setText("修改模式");
    alter->setFont(font_2);

    alter_road_to_wall = new QPushButton(this);
    alter_road_to_wall->setFocusPolicy(Qt::NoFocus);
    alter_road_to_wall->setGeometry(860,250,80,20);
    alter_road_to_wall->setText("改为墙");
    alter_road_to_wall->setFont(font_2);
    alter_road_to_wall->setVisible(false);

    alter_wall_to_road = new QPushButton(this);
    alter_wall_to_road->setFocusPolicy(Qt::NoFocus);
    alter_wall_to_road->setGeometry(860,275,80,20);
    alter_wall_to_road->setText("改为路");
    alter_wall_to_road->setFont(font_2);
    alter_wall_to_road->setVisible(false);

    import_maze = new QPushButton(this);
    import_maze->setFocusPolicy(Qt::NoFocus);
    import_maze->setGeometry(860,300,80,20);
    import_maze->setText("导入地图");
    import_maze->setFont(font_2);
    import_maze->setVisible(false);

    outport_maze = new QPushButton(this);
    outport_maze->setFocusPolicy(Qt::NoFocus);
    outport_maze->setGeometry(860,325,80,20);
    outport_maze->setText("导出地图");
    outport_maze->setFont(font_2);
    outport_maze->setVisible(false);

    alter_exit = new QPushButton(this);
    alter_exit->setFocusPolicy(Qt::NoFocus);
    alter_exit->setGeometry(860,350,80,20);
    alter_exit->setText("结束修改");
    alter_exit->setFont(font_2);
    alter_exit->setVisible(false);

    find_way = new QPushButton(this);
    find_way->setFocusPolicy(Qt::NoFocus);
    find_way->setGeometry(810,375,100,20);
    find_way->setText("自动寻路");
    find_way->setFont(font_2);

    config = new QPushButton(this);
    config->setFocusPolicy(Qt::NoFocus);
    config->setGeometry(810,400,100,20);
    config->setText("游戏设置");
    config->setFont(font_2);

    caption = new QPushButton(this);
    caption->setFocusPolicy(Qt::NoFocus);
    caption->setGeometry(810,425,100,20);
    caption->setText("操作说明");
    caption->setFont(font_2);

    about = new QPushButton(this);
    about->setFocusPolicy(Qt::NoFocus);
    about->setGeometry(810,450,100,20);
    about->setText("关于");
    about->setFont(font_2);

    info = new QLabel(this);
    info->setFocusPolicy(Qt::NoFocus);
    info->setGeometry(275,300,400,40);
    info->setText("Press space to continue,");
    info->setFont(font_1);
    info->setVisible(false);


    player_x = 9;
    player_y = 8;
    mark_x = 9;
    mark_y = 8;

    game_time = new QTimer;
    game_time->setInterval(1000);

    //窗口会显示链接不成功原因
    connect(begin,
            SIGNAL(clicked()),
            this,
            SLOT(on_begin_clicked()));

    connect(alter,
            SIGNAL(clicked()),
            this,
            SLOT(on_alter_clicked()));

    connect(alter_exit,
            SIGNAL(clicked()),
            this,
            SLOT(on_alter_exit_clicked()));

    connect(alter_road_to_wall,
            SIGNAL(clicked()),
            this,
            SLOT(on_alter_road_to_wall_clicked()));

    connect(alter_wall_to_road,
            SIGNAL(clicked()),
            this,
            SLOT(on_alter_wall_to_road_clicked()));

    connect(import_maze,
            SIGNAL(clicked()),
            this,
            SLOT(on_import_maze_clicked()));

    connect(outport_maze,
            SIGNAL(clicked()),
            this,
            SLOT(on_outport_maze_clicked()));

    connect(game_time,
            SIGNAL(timeout()),
            this,
            SLOT(game_time_out()));
    connect(find_way,
            SIGNAL(clicked()),
            this,
            SLOT(on_find_way_clicked()));
    connect(config,
            SIGNAL(clicked()),
            this,
            SLOT(on_config_clicked()));
    connect(caption,
            SIGNAL(clicked()),
            this,
            SLOT(on_caption_clicked()));
    connect(find_way,
            SIGNAL(clicked()),
            this,
            SLOT(on_find_way_clicked()));
    connect(about,
            SIGNAL(clicked()),
            this,
            SLOT(on_about_clicked()));
}

Widget::~Widget()
{

}

void Widget::keyPressEvent(QKeyEvent  *event)
{
    if(game_mode == 1)
    {
        if(event->key() == Qt::Key_Up)
        {
            if(!is_out(player_x,player_y-1))
                player_y--;
                player_toward = 3;
        }
        else if(event->key() == Qt::Key_Down)
        {
            if(!is_out(player_x,player_y+1))
                player_y++;
            player_toward = 1;

        }
        else if(event->key() == Qt::Key_Left)
        {
            if(!is_out(player_x-1,player_y))
                player_x--;
            else if(player_x == 20 && player_y == 18 ||
               player_x == 21 && player_y == 18 ||
               player_x == 22 && player_y == 18
               )
                player_x--;
            player_toward = 4;

        }
        else if(event->key() == Qt::Key_Right)
        {
            if(!is_out(player_x+1,player_y))
                player_x++;
            else if(player_x == 19 && player_y == 18 ||
               player_x == 20 && player_y == 18 ||
               player_x == 21 && player_y == 18
               )
                player_x++;
            player_toward = 2;
        }
        else if(event->key() == Qt::Key_Space)
        {
            /*game_mode = 0;
            state->setText("当前状态：暂停");
            info->setVisible(true);*/
            mode_to_0();
        }
        update();
        if(player_x == 22 && player_y == 18)
            fun_win();

    }
    else if(game_mode == 2)
    {
        if(event->key() == Qt::Key_Up)
        {
            if(mark_x>=0&&mark_x<=19&&mark_y-1>=0&&mark_y-1<=19)
                mark_y--;
        }
        else if(event->key() == Qt::Key_Down)
        {
            if(mark_x>=0&&mark_x<=19&&mark_y+1>=0&&mark_y+1<=19)
                mark_y++;
        }
        else if(event->key() == Qt::Key_Left)
        {
            if(mark_x-1>=0&&mark_x-1<=19&&mark_y>=0&&mark_y<=19)
                mark_x--;
        }
        else if(event->key() == Qt::Key_Right)
        {
            if(mark_x+1>=0&&mark_x+1<=19&&mark_y>=0&&mark_y<=19)
                mark_x++;
        }
    }
    else if(game_mode == 0)
    {
        if(event->key() == Qt::Key_Space)
        {
            /*game_mode = 1;
            state->setText("当前状态：游戏中");
            info->setVisible(false);*/
            mode_to_1();
        }
    }
    update();
}

void Widget::paintEvent(QPaintEvent *)
{
    if(game_mode == 0)
        return;
    QPainter painter(this);
    QPixmap pix;
    /*
    0.草   皮
    1.石   板
    2.装饰品1
    3.装饰品2
    */
    painter.translate(0, 0);
    pix.load("0.png");
    QPixmap pix_n1,pix_n2;
    pix_n1.load("tree.png");
    pix_n2.load("stump.png");
    for(int i=0;i!=800;i+=32)//初始化草皮
        for(int j=0;j!=640;j+=32)
        {
            painter.drawPixmap(i, j, 32, 32, pix);
            if(i>640||j>640) continue;
            if(maze.get_value(i/32,j/32)==-1) painter.drawPixmap(i, j, 32, 32, pix_n1);
            if(maze.get_value(i/32,j/32)==-2) painter.drawPixmap(i, j, 32, 32, pix_n2);
        }
    pix.load("barn.png");
    painter.drawPixmap(640, 0, 160, 640, pix);//绘制粮仓
    pix.load("1.png");
    for(int i=0;i!=20;i++)//绘制道路
        for(int j=0;j!=20;j++)
            if(maze.get_value(i,j)==1)painter.drawPixmap(i*32, j*32, 32, 32, pix);

    //绘制玩家
    if( game_mode == 1|| game_mode == 0 )
    {
        switch(player_toward)
        {
            case 1:
                pix.load("mouse_1.png");
                break;
            case 2:
                pix.load("mouse_2.png");
                break;
            case 3:
                pix.load("mouse_3.png");
                break;
            case 4:
                pix.load("mouse_4.png");
                break;
        }
        painter.drawPixmap(player_x*32, player_y*32, 32, 32, pix);
    }


    //绘制修改标识
    if(game_mode == 2)
    {
        pix.load("mark.png");
        //pix.load("mouse.png");
        painter.drawPixmap(mark_x*32, mark_y*32, 32, 32, pix);
    }

    if(is_find_way_painted)//需要绘制自动寻路路径时 先绘制全部路径 再绘制特殊路径
    {

        QPen pen1,pen2;
        pen1.setColor(Qt::black);
        pen1.setWidth(2);
        pen1.setJoinStyle(Qt::RoundJoin);
        pen2.setColor(Qt::red);
        pen2.setWidth(2);
        pen2.setJoinStyle(Qt::RoundJoin);
        painter.setPen(pen1);
        for(int i=0;i<=path_log.size()-1;i++)
        {

            for(int j=1;j<=path_log[i].size()-1;j++)
            {
                painter.drawLine(path_log[i][j-1].x*32+16,path_log[i][j-1].y*32+16,path_log[i][j].x*32+16,path_log[i][j].y*32+16);
            }

        }
        painter.setPen(pen2);
        for(int i=1;i<=min_path.size()-1;i++)
        {
            painter.drawLine(min_path[i-1].x*32+16,min_path[i-1].y*32+16,min_path[i].x*32+16,min_path[i].y*32+16);
            //qDebug() << min_path[i].x << ' ' << min_path[i].y;
        }
        painter.drawLine(19*32+16,18*32+16,22*32+16,18*32+16);
    }

}

void Widget::on_begin_clicked()
{
    if(QMessageBox::Yes != QMessageBox::question(this,"提示","是否开始新游戏？",QMessageBox::Yes|QMessageBox::No))
    {
        return;
    }
    player_x = 9;
    player_y = 8;
    win_time = set_win_time;
    is_find_way_painted = false;
    for(int i=1;i<=19;i++)
        for(int j=0;j<=19;j++)
        {
            could_visit[i][j] = false;
        }
    maze.all_to_0();
    for(int i=1;i<=19;i+=2)
        for(int j=0;j<=19;j+=2)
        {
            could_visit[i][j] = true;
            maze.set_to_1(i,j);
        }
    player_toward = 1;
    create_path.push_back(point(9,8));
    dfs_create();
    mode_to_1();
}

void Widget::on_alter_clicked()
{

    mode_to_2();
    is_find_way_painted = false;
    update();
}

void Widget::on_alter_exit_clicked()
{
    mode_to_0();

    mark_x = 9;
    mark_y = 8;
    player_x = 9;
    player_y = 8;
    win_flag = false;
    win_time = set_win_time;
    player_toward = 1;
    update();
}

void Widget::on_alter_road_to_wall_clicked()
{
    if(maze.get_value(mark_x,mark_y)!=1) return;

    if(mark_x==9&&mark_y==8)
    {
        QMessageBox::information(this,"提示","起点无法更改",QMessageBox::Yes);
        return;
    }
    int n1 = rand()%10;

    if(n1 == 1) maze.set_to_n1(mark_x,mark_y);
    else if(n1 == 2) maze.set_to_n2(mark_x,mark_y);
    else maze.set_to_0(mark_x,mark_y);

    update();
}


void Widget::on_alter_wall_to_road_clicked()
{
    //if(maze.get_value(mark_x,mark_y)!=1) return;
    maze.set_to_1(mark_x,mark_y);

    update();
}

void Widget::on_import_maze_clicked()
{
    QString path= QFileDialog::getOpenFileName(NULL,"输出路径选择","C:/Users/Alan/Desktop/LEARN/code/DataStrcture","*.maze");
    std::ifstream in(path.toStdString());
    if(in.is_open())
    {
        for(int i=0;i!=20;i++)
            for(int j=0;j!=20;j++)
            {
                int t;
                in >> t;
                if(t==1) maze.set_to_1(i,j);
                if(t==-1) maze.set_to_n1(i,j);
                if(t==-2) maze.set_to_n2(i,j);
                if(t==0) maze.set_to_0(i,j);
            }
        in.close();
        QMessageBox::information(this,"提示","导入成功",QMessageBox::Yes);
        mark_x = 10;
        mark_y = 10;
        update();
    }
    else
        QMessageBox::question(this,"提示","导入失败",QMessageBox::Yes);

}

void Widget::on_outport_maze_clicked()
{
    QTime now_time;
    QFileDialog log(this);
    log.setFileMode(QFileDialog::Directory);
    QString path = log.getExistingDirectory(NULL,"储存路径选择","C:/Users/Alan/Desktop/LEARN/code/DataStrcture");
    path = path + '/' + now_time.currentTime().toString("hh_mm_sss") + ".maze";
    std::ofstream out(path.toStdString());
    if(out.is_open())
    {
        for(int i=0;i!=20;i++)
        {
            for(int j=0;j!=20;j++)
            {
                out << maze.get_value(i,j);
                out << ' ';
            }
            out << '\n';
        }
        out << '\n';
        out.close();
        QMessageBox::information(this,"提示","导出成功",QMessageBox::Yes);
    }
    else
        QMessageBox::question(this,"提示","导出失败",QMessageBox::Yes);
}

void Widget::on_find_way_clicked()
{
    if(is_find_way_painted) return;
    if(game_mode!=1)    return;
    path_num = 0;
    for(int i=0;i!=20;i++)
        for(int j=0;j!=20;j++)
            is_visited[i][j] = 0;
    v.clear();
    path_log.clear();
    min_path.clear();
    v.push_back(point(player_x,player_y));
    dfs();
    if(path_log.empty())
    {
        QMessageBox::critical(this,"提示","没有可行路径",QMessageBox::Yes);
        return;
    }
    int minpath = path_log[0].size(),minpos = 0;
    for(int i=1;i < path_log.size()-1;i++)
    {
        if(path_log[i].size() < minpath)
        {
            minpath = path_log[i].size();
            minpos = i;
        }
    }

    is_find_way_painted = true;
    min_path = path_log[minpos];

    update();
    QMessageBox::information(this,"提示","共找到 "+QString::number(path_log.size())+" 条通路，\n"+
    "最短路径长为 "+QString::number(min_path.size())+" 格。",QMessageBox::Yes);
}

bool Widget::is_out(int x,int y)
{
    return (x>=0&&x<=19&&y>=0&&y<=19&&maze.get_value(x,y)>0)?false:true;
}

void Widget::mode_to_0()
{
    game_mode = 0;
    state->setText("当前状态：暂停");
    info->setVisible(true);
    begin->setVisible(true);
    time_log->setVisible(true);
    alter->setVisible(true);
    alter_road_to_wall->setVisible(false);
    alter_wall_to_road->setVisible(false);
    outport_maze->setVisible(false);
    import_maze->setVisible(false);
    alter_exit->setVisible(false);
    config->setVisible(true);
    find_way->setVisible(true);

    game_time->stop();
}

void Widget::mode_to_1()
{
    game_mode = 1;
    state->setText("当前状态：游戏中");
    begin->setVisible(true);
    time_log->setVisible(true);
    alter->setVisible(true);
    alter_road_to_wall->setVisible(false);
    alter_wall_to_road->setVisible(false);
    outport_maze->setVisible(false);
    import_maze->setVisible(false);
    alter_exit->setVisible(false);
    config->setVisible(true);
    find_way->setVisible(true);

    info->setVisible(false);


    game_time->start();
}

void Widget::mode_to_2()
{
    game_mode = 2;
    state->setText("当前状态：修改中");
    info->setVisible(false);
    begin->setVisible(false);
    time_log->setVisible(false);
    alter->setVisible(false);
    alter_road_to_wall->setVisible(true);
    alter_wall_to_road->setVisible(true);
    outport_maze->setVisible(true);
    import_maze->setVisible(true);
    alter_exit->setVisible(true);
    config->setVisible(false);
    find_way->setVisible(false);


    game_time->stop();
}

void Widget::fun_win()
{

    game_time->stop();
    QMessageBox::information(this,"祝贺","到达了终点！",QMessageBox::Yes);
    game_mode = 3;
    state->setText("老鼠吃上大米啦");
}

void Widget::fun_lose()
{
    game_time->stop();
    QMessageBox::information(this,"啊这","没时间了",QMessageBox::Yes);
    game_mode = 3;
    state->setText("老鼠吃不到米啦");

}

QString Widget::int_to_time(int t)
{
    int mm = t/60;
    int ss = t%60;
    QString mms = QString::number(mm);
    QString sss = QString::number(ss);
    while(mms.size() < 2) mms = "0" + mms;
    while(sss.size() < 2) sss = "0" + sss;
    return mms + ':' + sss;
}

void Widget::game_time_out()
{
    if(win_time==0)
    {
        fun_lose();
        return;
    }
    win_time --;
    time_log->display(int_to_time(win_time));
}

void Widget::dfs()
{

    int x,y;
    if(v.empty()) return;
    x = v[v.size()-1].x;
    y = v[v.size()-1].y;

    is_visited[x][y] = true;
    if(x==19 && y==18)
    {
        path_num++;
        path_log.push_back(v);
    }
    else
    {
        if(!is_out(x+1,y)&&!is_visited[x+1][y]) {v.push_back(point(x+1,y));dfs();};

        if(!is_out(x,y+1)&&!is_visited[x][y+1]) {v.push_back(point(x,y+1));dfs();};

        if(!is_out(x-1,y)&&!is_visited[x-1][y]) {v.push_back(point(x-1,y));dfs();};

        if(!is_out(x,y-1)&&!is_visited[x][y-1]) {v.push_back(point(x,y-1));dfs();};
    }

    is_visited[x][y] = false;
    v.pop_back();
}

void Widget::dfs_create()
{
    if(create_path.empty())	return;
    int x = create_path[create_path.size()-1].x;
    int y = create_path[create_path.size()-1].y;
    could_visit[x][y] = false;

    if(create_path.size()>=2)
    {
        maze.set_to_1((create_path[create_path.size()-1].x+create_path[create_path.size()-2].x)/2,
                    (create_path[create_path.size()-1].y+create_path[create_path.size()-2].y)/2);
    }
        while(x+2<20&&could_visit[x+2][y]||
           x-2>0 &&could_visit[x-2][y]||
           y+2<19&&could_visit[x][y+2]||
           y-2>=0 &&could_visit[x][y-2]
        )
        {
            int st = rand()%4;
            switch(st)
            {
                case 0:
                    if(x+2<20&& could_visit[x+2][y]){create_path.push_back(point(x+2,y));dfs_create();};
                    break;
                case 1:
                    if(x-2>0 && could_visit[x-2][y]){create_path.push_back(point(x-2,y));dfs_create();};
                    break;
                case 2:
                    if(y+2<19&& could_visit[x][y+2]){create_path.push_back(point(x,y+2));dfs_create();};
                    break;
                case 3:
                    if(y-2>=0&& could_visit[x][y-2]){create_path.push_back(point(x,y-2));dfs_create();};
                    break;
            }
        }
    create_path.pop_back();
}
void Widget::on_config_clicked()
{
    int id = QMessageBox::information(NULL, "提示","选择时间",
    QString("120s"), QString("60s"),QString("20s"));
    switch (id) {
            case 0:
            {
                set_win_time = 120;
            }
                break;
            case 1:
            {
                set_win_time = 60;

            }
                break;
            case 2:
            {
                set_win_time = 20;
            }
                break;
            default:
                break;
        }
    QMessageBox::information(NULL, "提示","时间已经设置为 "+QString::number(set_win_time) + "s,下回合开始生效",
         QMessageBox::Yes);
}

void Widget::on_caption_clicked()
{
    QMessageBox::information(this,"操作说明","老鼠找粮仓\n在规定时间内控制老鼠到粮仓\n上下左右键 控制移动\n空格键 继续/暂停");
}

void Widget::on_about_clicked()
{
    QMessageBox::information(this,"关于","老鼠找粮仓 ver 0.1\n powerd by Alan at Linhai Zhejiang");
}

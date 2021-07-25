#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QPushButton>
#include <QWidget>
#include <QLCDNumber>
#include <QLabel>

#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QTime>
#include <QPen>
#include <QVector>
#include <QLine>

#include <fstream>
#include <vector>
#include <process.h>
#include "map.h"
#include <stdlib.h>


class point
{
public:
    int x;int y;
    point(){};
    point(int xx,int yy){x = xx ; y = yy;}
    void set_point(int xx,int yy){x = xx ; y = yy;};
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent  *event);
    bool is_out(int x,int y);
    void mode_to_0();
    void mode_to_1();
    void mode_to_2();
    void map_create();//随机生成地图
    void fun_win();
    void fun_lose();
    QString int_to_time(int t);
    void dfs();
    void dfs_create();
private:
    map maze;
    bool is_visited[20][20];
    int game_mode;// 0-暂停 1-正常游戏 2-修改地图 3-已赢
    int player_x;
    int player_y;
    int player_toward;
    /*
    3
   4 2
    1
    */
    int mark_x;
    int mark_y;

    bool win_flag;
    bool is_find_way_painted;

    int win_time;
    int set_win_time;

    QVector<point> path;
    QVector<QVector<point>> path_log;
    QVector<point> min_path;

    QLabel* title;
    QLabel* state;

    QPushButton* begin;
    QLCDNumber* time_log;

    QPushButton* alter;
    QPushButton* alter_road_to_wall;
    QPushButton* alter_wall_to_road;
    QPushButton* import_maze;
    QPushButton* outport_maze;
    QPushButton* alter_exit;

    QPushButton* find_way;

    QPushButton* config;

    QPushButton* caption;

    QPushButton* about;

    QLabel* info;

    QTimer* g_time;
    QTimer* game_time;

    QVector<point> v;
    int path_num;

    int could_visit[20][20];
    QVector<point> create_path;
public slots:
    void on_begin_clicked();//开始游戏
    void on_alter_clicked();//进入修改模式
    void on_alter_road_to_wall_clicked();
    void on_alter_wall_to_road_clicked();
    void on_import_maze_clicked();
    void on_outport_maze_clicked();//储存格式.maze
    void on_alter_exit_clicked();//离开修改模式
    void on_find_way_clicked();
    void on_config_clicked();
    void on_caption_clicked();
    void on_about_clicked();



    void game_time_out();
};
#endif // WIDGET_H

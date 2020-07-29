#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QDebug>
#include <QMenuBar>
#include <QLabel>
#include <QFont>
#include <QPropertyAnimation>
#include <QSound>
#include "mypushbutton.h"
#include "mycoin.h"
#include "dataconfig.h"
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int index);
    //绘图事件画背景
    void paintEvent(QPaintEvent*);
    //记录当前的关卡数
    int levelIndex;
    //设置金币or银币的二维数组
    int gameArray[4][4];
    //定义防止金币的二维数组
    MyCoin* coinBtn[4][4];
    //定义游戏胜利标志
    bool isWin;
signals:
    //自定义信号实现跳转到选择界面
    void playSceneBack();

};

#endif // PLAYSCENE_H

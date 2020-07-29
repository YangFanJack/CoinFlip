#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QMenuBar>
#include <QTimer>
#include <QLabel>
#include <QSound>
#include "mypushbutton.h"
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    //绘图事件画背景
    void paintEvent(QPaintEvent*);
    //游戏场景的指针
    PlayScene* playScene;

signals:
    //自定义信号实现跳转到主界面
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H

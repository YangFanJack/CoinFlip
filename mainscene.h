#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <mypushbutton.h>
#include <QDebug>
#include <QTimer>
#include <QSound>
#include "chooselevelscene.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    //绘图事件画背景
    void paintEvent(QPaintEvent*);
    //选择场景界面的指针
    ChooseLevelScene* chooseScene;

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H

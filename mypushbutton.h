#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <QPropertyAnimation>
#include <QMouseEvent>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImg,QString pressImg = "");
    QString normalImgPath;
    QString pressImgPath;
    //向下跳跃
    void Zoom1();
    //向上跳跃
    void Zoom2();
    //鼠标按下的事件
    void mousePressEvent(QMouseEvent* e);
    //鼠标释放的事件
    void mouseReleaseEvent(QMouseEvent* e);
signals:

};

#endif // MYPUSHBUTTON_H

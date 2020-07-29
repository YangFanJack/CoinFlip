#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QDebug>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString coinImg);
    int posx;
    int posy;
    bool flag;//正反标志
    bool isWin;//是否胜利的标志

    void changeFlag();
    QTimer* timer1;
    QTimer* timer2;
    int min = 1;
    int max = 8;

    //是否正在执行动画的标志
    bool isAnimation;
    //鼠标按下的事件重写
    void mousePressEvent(QMouseEvent* e);
signals:

};

#endif // MYCOIN_H

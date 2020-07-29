#include "mycoin.h"

MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
{

}

MyCoin::MyCoin(QString coinImg){
    //初始化胜利的标志
    isWin = false;

    QPixmap pix;
    bool result = pix.load(coinImg);
    if(!result){
        QString str = QString("%1 图片加载失败").arg(coinImg);
        qDebug()<<str;
        return;
    }
    //设定按钮大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px}");
    //设置图片
    this->setIcon(pix);
    //设置图片大小
    this->setIconSize(QSize(pix.width(),pix.height()));
    //创建定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听金币翻银币计时器
    connect(timer1,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str = QString(":/res/Coin000%1.png").arg(this->min++);
       pix.load(str);
       //设定按钮大小
       this->setFixedSize(pix.width(),pix.height());
       //设置不规则图片样式
       this->setStyleSheet("QPushButton{border:0px}");
       //设置图片
       this->setIcon(pix);
       //设置图片大小
       this->setIconSize(QSize(pix.width(),pix.height()));
       if(this->min > this->max){
           this->min = 1;
           isAnimation = false;
           timer1->stop();
       }
    });

    isAnimation = false;
    //监听银币翻金币计时器
    connect(timer2,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str = QString(":/res/Coin000%1.png").arg(this->max--);
       pix.load(str);
       //设定按钮大小
       this->setFixedSize(pix.width(),pix.height());
       //设置不规则图片样式
       this->setStyleSheet("QPushButton{border:0px}");
       //设置图片
       this->setIcon(pix);
       //设置图片大小
       this->setIconSize(QSize(pix.width(),pix.height()));
       if(this->max < this->min){
           this->max = 8;
           isAnimation = false;
           timer2->stop();
       }
    });
}

void MyCoin::changeFlag(){
    if(this->flag){
        isAnimation = true;
        timer1->start(30);
        this->flag = false;
    }
    else{
        isAnimation = true;
        timer2->start(30);
        this->flag = true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent* e){
    if(isAnimation || isWin){
        //正在动画或者已经胜利，不做响应，直接return
        return;
    }
    else{
        //交给父类做默认处理
        QPushButton::mousePressEvent(e);
    }
}

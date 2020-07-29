#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{

}

MyPushButton::MyPushButton(QString normalImg,QString pressImg){
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;
    QPixmap pix;
    bool result = pix.load(this->normalImgPath);
    if(!result){
        QString str = QString("%1 图片加载失败").arg(this->normalImgPath);
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
}

void MyPushButton::Zoom1(){
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
    //设定时间间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyPushButton::Zoom2(){
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
    //设定时间间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

//鼠标按下的事件
void MyPushButton::mousePressEvent(QMouseEvent* e){
    if(this->pressImgPath != ""){
        QPixmap pix;
        bool result = pix.load(this->pressImgPath);
        if(!result){
            qDebug()<<"图片加载失败";
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
    }
    //其他事情交给父类处理
    QPushButton::mousePressEvent(e);
}
//鼠标释放的事件
void MyPushButton::mouseReleaseEvent(QMouseEvent* e){
    if(this->pressImgPath != ""){
        QPixmap pix;
        bool result = pix.load(this->normalImgPath);
        if(!result){
            qDebug()<<"图片加载失败";
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
    }
    QPushButton::mouseReleaseEvent(e);
}

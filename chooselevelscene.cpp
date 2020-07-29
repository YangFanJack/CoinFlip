#include "chooselevelscene.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);
    this->setWindowTitle("选择关卡");
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //用代码设置菜单栏
    QMenuBar* bar = menuBar();
    this->setMenuBar(bar);
    QMenu* startMenu = bar->addMenu("开始");
    QAction* quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
       this->close();
    });
    //选择关卡和返回按钮的音效
    QSound* chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    QSound* backSound = new QSound(":/res/BackButtonSound.wav",this);
    //返回按钮创建
    MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&QPushButton::clicked,this,[=](){
        //返回音效设置
        backSound->play();
        qDebug()<<"点击了返回按钮";
        emit this->chooseSceneBack();
    });

    //选择关卡按钮
    for(int i=0;i<20;i++){
        MyPushButton* menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4)*70,150+(i/4)*70);
        //设置按钮点击事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
            //点击音效
            chooseSound->play();
            QString str = QString("您选择的关卡是:%1").arg(i+1);
            qDebug()<<str;
            //隐藏自身
            this->hide();
            //进入游戏场景
            playScene = new PlayScene(i+1);
            playScene->setGeometry(this->geometry());
            playScene->show();
            //监听回跳事件
            connect(playScene,&PlayScene::playSceneBack,[=](){
                QTimer::singleShot(300,this,[=](){
                    this->setGeometry(playScene->geometry());
                    playScene->close();
                    delete playScene;
                    playScene = NULL;
                    this->show();
                });
            });
        });
        //设置按钮上的关卡数字
        QLabel* label = new QLabel(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25+(i%4)*70,150+(i/4)*70);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置鼠标穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }


}

void ChooseLevelScene::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    //绘制背景图
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //绘制标题图
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
